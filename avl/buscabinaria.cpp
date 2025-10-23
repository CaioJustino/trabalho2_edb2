#include "arvore.h"
#include <iostream>

bool buscaAVL(NoAVL* raiz, int v) {
  if (raiz == nullputr0
    return false;
 if (valor == raiz->chave)
  return true;
 else if (valor < raiz->chave)
  return buscaAVL(raiz->esq, v);
 else
  return buscaAVL(raiz->dir, v);
}
