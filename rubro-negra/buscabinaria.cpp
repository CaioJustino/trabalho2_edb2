#include "arvore.h"
#include <iostream>

// Função pública — chamada externamente
bool ArvoreRN::buscar(int valor) {
    return buscarRec(raiz, valor);
}

// Função auxiliar recursiva
bool ArvoreRN::buscarRec(No* no, int valor) {
    // Como a árvore RN usa um nó NIL em vez de nullptr,
    // verificamos se o nó atual é o sentinel.
    if (no == NIL)
        return false;

    if (valor == no->valor)
        return true;
    else if (valor < no->valor)
        return buscarRec(no->esq, valor);
    else
        return buscarRec(no->dir, valor);
}
