// Imports
#include <iostream>

#include "arvore.h"

/**
 * @brief Insere um nó na árvore Rubro-Negra gerada.
 * 
 * Ela cria um novo nó vermelho, insere ele na árvore seguindo
 * a regra da BST (Binary Search Tree) e corrige a árvore para manter as
 * propriedades Rubro-Negra (nenhum caminho tem dois
 * vermelhos consecutivos, raiz sempre preta, entre outras).
 * 
 * @param valor Valor a ser inserido (máximo de 100).
 */
void ArvoreRN::inserir(int valor) {
    if (valor > 100) {
        std::cout << "O valor do nó deve ser menor ou igual a 100!\n";
        return;
    }

    No* z = new No(valor);
    z->esq = z->dir = z->pai = NIL;
    z->cor = VERMELHO;

    No* y = NIL;
    No* x = raiz;

    while (x != NIL) {
        y = x;
        if (z->valor < x->valor) {
            x = x->esq;
        }

        else if (z->valor > x->valor) {
            x = x->dir;
        }

        else {
            delete z;
            return;
        }
    }

    z->pai = y;

    if (y == NIL) {
        raiz = z;
    }

    else if (z->valor < y->valor) {
        y->esq = z;
    }

    else {
        y->dir = z;
    }

    corrigirInsercao(z);
}