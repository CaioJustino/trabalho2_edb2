// Imports
#include <iostream>
#include <functional>

#include "arvore.h"

/**
 * @brief Busca um valor na árvore Rubro-Negra.
 * 
 * A busca percorre a árvore recursivamente, comparando o valor procurado
 * com o valor armazenado em cada nó até encontrar o elemento ou atingir
 * o nó sentinel (NIL).
 * 
 * @param valor Valor a ser procurado.
 */
bool ArvoreRN::buscar(int valor) {
    std::function<bool(No*)> buscarRec = [&](No* no) -> bool {
        if (no == NIL)
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