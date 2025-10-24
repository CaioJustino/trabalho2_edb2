#include "arvore.h"
#include <iostream>

// Função pública — chamada pelo usuário
bool ArvoreAVL::buscar(int valor) {
    return buscarRec(raiz, valor);
}

// Função auxiliar recursiva
bool ArvoreAVL::buscarRec(No* no, int valor) {
    if (no == nullptr)
        return false;
    if (valor == no->valor)
        return true;
    else if (valor < no->valor)
        return buscarRec(no->esq, valor);
    else
        return buscarRec(no->dir, valor);
}
