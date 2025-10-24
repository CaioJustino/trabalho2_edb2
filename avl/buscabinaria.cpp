// Imports
#include <iostream>
#include <functional>

#include "arvore.h"

/**
 * @brief Busca um valor na árvore AVL.
 * 
 * A busca percorre a árvore recursivamente, comparando o valor procurado
 * com o valor armazenado em cada nó até encontrar o elemento ou atingir
 * uma folha nula.
 * 
 * @param valor Valor a ser procurado.
 */
bool ArvoreAVL::buscar(int valor) {
    std::function<bool(No*)> buscarRec = [&](No* no) -> bool {
        if (no == nullptr)
            return false;
        if (valor == no->valor)
            return true;
        else if (valor < no->valor)
            return buscarRec(no->esq);
        else
            return buscarRec(no->dir);
    };

    return buscarRec(raiz);
}