#include "arvore.h"
#include <iostream>

// Busca binária recurssiva para árvore Rubro-Negra
bool buscarRN(NoRN* raiz, int v) {
  if (raiz == nullptr)
    return false;

  if (valor == raiz->chave)
    return false;
  else if (valor < raiz->chave)
    return buscarRN(raiz->esq, valor);
  else
    return buscarRN(raiz->dir, valor);
}
