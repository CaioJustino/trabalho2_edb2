// Imports
#include <iostream>

#include "arvore.h"

/**
 * @brief Insere um nó na árvore rubro-negra gerada.
 * 
 * Ela cria um novo nó vermelho, insere ele na árvore seguindo
 * a ordem BST (Binary Search Tree) e corrige a árvore para manter as
 * propriedades rubro-negra (nenhum caminho tem dois
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
        } else if (z->valor > x->valor) {
            x = x->dir;
        } else {
            delete z;
            return;
        }
    }

    z->pai = y;

    if (y == NIL) {
        raiz = z;
    } else if (z->valor < y->valor) {
        y->esq = z;
    } else {
        y->dir = z;
    }

    corrigirInsercao(z);
}

/**
 * @brief Corrige a árvore após a inserção para manter as propriedades da árvore rubro-negra.
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
            } else {
                if (z == z->pai->dir) {
                    z = z->pai;
                    rotacaoEsquerda(z);
                }
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacaoDireita(z->pai->pai);
            }
        } else {
            No* y = z->pai->pai->esq;
            if (y->cor == VERMELHO) {
                z->pai->cor = PRETO;
                y->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;
            } else {
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