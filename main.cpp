// Imports
#include <iostream>
#include <memory>
#include <limits>

#include "arvore.h"
#include "avl/arvore.h"
#include "rubro-negra/arvore.h"

using namespace std;

/**
 * @brief Função principal do programa.
 * 
 * Ela retorna um "menu interativo" que permite:
 * - Gerar árvores AVL e Rubro-Negra aleatórias.
 * - Inserir nós nas árvores.
 * - Buscar valores nas árvores.
 * - Imprimir as árvores.
 */
int main() {
    unique_ptr<ArvoreAVL> avl = make_unique<ArvoreAVL>();
    unique_ptr<ArvoreRN> rb = make_unique<ArvoreRN>();
    bool avlGerada = false;
    bool rbGerada = false;

    while (true) {
        cout << R"( __  __                  
|  \/  | ___ _ __  _   _ 
| |\/| |/ _ \ '_ \| | | |
| |  | |  __/ | | | |_| |
|_|  |_|\___|_| |_|\__,_|)" << endl;

        cout << "\n1 - Gerar uma árvore AVL aleatória.\n";
        cout << "2 - Gerar uma árvore Rubro-Negra aleatória.\n";
        cout << "\n3 - Inserir um nó na árvore AVL gerada.\n";
        cout << "4 - Inserir um nó na árvore Rubro-Negra gerada.\n";
        cout << "\n5 - Buscar um valor na árvore AVL gerada.\n";
        cout << "6 - Buscar um valor na árvore Rubro-Negra gerada.\n";
        cout << "\n7 - Imprimir a árvore AVL gerada.\n";
        cout << "8 - Imprimir a árvore Rubro-Negra gerada.\n";
        cout << "0 - Encerrar a execução do programa.\n";

        int op;
        cout << "Opção: ";
        cin >> op;

        if (op == 0) {
            break;
        }

        if (op == 1) {
            avl->gerarArvoreAleatoria();
            avlGerada = true;
            cout << "\nÁrvore AVL gerada com sucesso!\n";
        }
        
        else if (op == 2) {
            rb->gerarArvoreAleatoria();
            rbGerada = true;
            cout << "\nÁrvore Rubro-Negra gerada com sucesso!\n";
        }
        
        else if (op == 3) {
            if (!avlGerada) {
                cout << "\nGere a árvore AVL primeiro (opção 1) antes de inserir qualquer nó!\n"; continue;
            }

            int v;
            cout << "Valor do nó a ser inserido na árvore AVL: ";
            cin >> v;

            if (v > 100) {
                cout << "\nValor inválido! Somente valores até 100 são permitidos.\n";
                continue;
            }

            avl->inserir(v);
            cout << "\nNó inserido com sucesso!\n";
        }

        else if (op == 4) {
            if(!rbGerada) {
                cout << "Gere a árvore Rubro-Negra primeiro (opção 2) antes de inserir qualquer nó!\n"; continue;
            }

            int v;
            cout << "Valor do nó a ser inserido na árvore Rubro-Negra: ";
            cin >> v;

            if (v > 100) {
                cout << "\nValor inválido! Somente valores até 100 são permitidos.\n";
                continue;
            }

            rb->inserir(v);
            cout << "\nNó inserido com sucesso!\n";
        }

        else if (op == 5) {
            if (!avlGerada) {
                cout << "\nGere a árvore AVL primeiro (opção 1)!\n"; continue;
            }

            int v;
            cout << "Valor a buscar na árvore AVL: ";
            cin >> v;

            if (avl->buscar(v))
                cout << "\nValor encontrado na árvore AVL!\n";
            else
                cout << "\nValor não encontrado na árvore AVL...\n";
        }

        else if (op == 6) {
            if (!rbGerada) {
                cout << "\nGere a árvore Rubro-Negra primeiro (opção 2)!\n"; continue;
            }

            int v;
            cout << "Valor a buscar na árvore Rubro-Negra: ";
            cin >> v;

            if (rb->buscar(v))
                cout << "\nValor encontrado na árvore Rubro-Negra!\n";
            else
                cout << "\nValor não encontrado na árvore Rubro-Negra...\n";
        }

        else if (op == 7) {
            cout << "\n---------- ÁRVORE AVL GERADA ----------\n";
            cout << avl->imprimir();
        }

        else if (op == 8) {
            cout << "\n---------- ÁRVORE RUBRO-NEGRA GERADA ----------\n";
            cout << rb->imprimir();
        }
        
        else {
            cout << "\nOpção inválida!\n";
        }
    }

    cout << "\nPrograma encerrado!\n";
    return 0;
}