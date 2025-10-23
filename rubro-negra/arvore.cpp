// Imports
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <queue>
#include <utility>
#include <set>

#include "arvore.h"

using namespace std;

/**
 * @brief Construtor da classe.
 * Inicializa o nó NIL e define a raiz como NIL.
 */
ArvoreRN::ArvoreRN() {
    NIL = new No(0);
    NIL->cor = PRETO;
    NIL->esq = NIL->dir = NIL->pai = NIL;
    raiz = NIL;
}

/**
 * @brief Calcula a altura total da subárvore a partir de um nó.
 * @param no Nó raiz da subárvore.
 * @return Altura da subárvore.
 */
int ArvoreRN::alturaTotal(No* no) {
    if (no == NIL) {
        return 0;
    }

    return 1 + max(alturaTotal(no->esq), alturaTotal(no->dir));
}

/**
 * @brief Realiza a rotação à esquerda em um nó.
 * @param x Nó a ser rotacionado.
 * @return Novo nó raiz da subárvore.
 */
void ArvoreRN::rotacaoEsquerda(No* x) {
    if (x == NIL) {
        return;
    }
    No* y = x->dir;
    
    if (y == NIL) {
        return;
    }
    x->dir = y->esq;
    
    if (y->esq != NIL) {
        y->esq->pai = x;
    }
    y->pai = x->pai;
    
    if (x->pai == NIL) {
        raiz = y;
    }

    if (x == x->pai->esq) {
        x->pai->esq = y;
    }

    else {
        x->pai->dir = y;
    }

    y->esq = x;
    x->pai = y;
}

/**
 * @brief Realiza a rotação à direita em um nó.
 * @param y Nó a ser rotacionado.
 * @return Novo nó raiz da subárvore.
 */
void ArvoreRN::rotacaoDireita(No* y) {
    if (y == NIL) {
        return;
    }
    No* x = y->esq;
    
    if (x == NIL) {
        return;
    }
    y->esq = x->dir;
    
    if (x->dir != NIL) {
        x->dir->pai = y;
    }
    x->pai = y->pai;
    
    if (y->pai == NIL) {
        raiz = x;
    }

    if (y == y->pai->dir) {
        y->pai->dir = x;
    }

    else {
        y->pai->esq = x;
    }

    x->dir = y;
    y->pai = x;
}

/**
 * @brief Gera uma árvore Rubro-Negra aleatória.
 * Insere entre 1 e 10 nós com valores de 0 a 100.
 */
void ArvoreRN::gerarArvoreAleatoria() {
    srand((unsigned)time(nullptr));

    int n = rand() % 10 + 1;

    set<int> usados;

    while ((int)usados.size() < n) {
        int v = rand() % 101;

        if (usados.insert(v).second) {
            inserir(v);
        }
    }
}

/**
 * @brief Corrige a árvore após inserção para manter as propriedades da árvore Rubro-Negra.
 * @param z Nó recém-inserido.
 */
void ArvoreRN::corrigirInsercao(No* z) {
    while (z->pai->cor == VERMELHO) {
        if (z->pai == z->pai->pai->esq) {
            No* y = z->pai->pai->dir;
            
            if (y->cor == VERMELHO) {
                z->pai->cor = PRETO;
                y->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;
            }
            
            else {
                if (z == z->pai->dir) {
                    z = z->pai;
                    rotacaoEsquerda(z);
                }
                
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacaoDireita(z->pai->pai);
            }
        }
        
        else {
            No* y = z->pai->pai->esq;
            if (y->cor == VERMELHO) {
                z->pai->cor = PRETO;
                y->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;
            }
            
            else {
                if (z == z->pai->esq) {
                    z = z->pai;
                    rotacaoDireita(z);
                }
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacaoEsquerda(z->pai->pai);
            }
        }
        if (z == raiz) {
            break;
        }
    }
    raiz->cor = PRETO;
}

/**
 * @brief Imprime a árvore gerada.
 * @return String formatada da árvore.
 */
std::string ArvoreRN::imprimir() {
    if (raiz == NIL) {
        return "Árvore vazia.\n";
    }

    std::ostringstream oss;
    std::queue<No*> fila;
    fila.push(raiz);

    int h = alturaTotal(raiz);
    int nivel = 0;
    int elementosNoNivel = 1;
    int proximoNivel = 0;
    int espaco = (1 << (h - 1)) * 4;

    if (espaco < 5) {
        espaco = 5;
    }

    while (!fila.empty() && nivel < h) {
        std::ostringstream linhaNos, linhaConexoes;
        bool temProximoNivel = false;

        for (int i = 0; i < elementosNoNivel; i++) {
            No* no = fila.front();
            fila.pop();

            if (no != NIL) {
                std::string texto = std::to_string(no->valor) + (no->cor == VERMELHO ? "(R)" : "(P)");
                linhaNos << std::setw(espaco) << texto;

                fila.push(no->esq);
                fila.push(no->dir);
                proximoNivel += 2;

                if (no->esq != NIL || no->dir != NIL) {
                    temProximoNivel = true;
                }

                linhaConexoes << std::setw(espaco - 3)
                              << (no->esq != NIL ? "/" : " ")
                              << "   "
                              << (no->dir != NIL ? "\\" : " ");
            }
            
            else {
                linhaNos << std::setw(espaco) << " ";
                fila.push(NIL);
                fila.push(NIL);
                proximoNivel += 2;
                linhaConexoes << std::setw(espaco) << " ";
            }
        }

        oss << linhaNos.str() << "\n";

        if (temProximoNivel) {
            oss << linhaConexoes.str() << "\n";
        }

        nivel++;

        if (!temProximoNivel) {
            break;
        }

        elementosNoNivel = proximoNivel;
        proximoNivel = 0;
        espaco = std::max(espaco / 2, 5);
    }

    return oss.str();
}