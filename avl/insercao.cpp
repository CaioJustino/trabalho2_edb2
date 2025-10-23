// Imports
#include <iostream> 
#include <functional>

#include "arvore.h"

/**
 * @brief Insere um nó na árvore AVL gerada.
 * 
 * Ela cria recursivamente um novo nó, posiciona ele na árvore
 * de acordo com a ordem BST (Binary Search Tree) e balanceia a árvore após
 * cada inserção para manter a propriedade da árvore AVL (módulo do fator de balanceamento <= 1).
 * 
 * @param valor Valor a ser inserido (máximo de 100).
 */
void ArvoreAVL::inserir(int valor) {
    /* 
        Função recursiva "inserirRec": chama a si mesma até encontrar a posição correta do nó a
        ser inserido na árvore.
    */
    std::function<No*(No*, int)> inserirRec = [&](No* no, int v) -> No* {
        if (!no) {
            return new No(v);
        }

        else if (v < no->valor) {
            no->esq = inserirRec(no->esq, v);
        }

        else if (v > no->valor) {
            no->dir = inserirRec(no->dir, v);
        }

        else {
            return no;
        }

        return balancear(no);
    };

    raiz = inserirRec(raiz, valor);
}