#include "arvore.h"
#include <iostream>

using namespace std;

bool ArvoreRN::remover(int valor) {
    No* z = buscarNo(valor);
    if (z == NIL) return false;

    No* y = z;
    No* x;
    Cor corOriginalY = y->cor;

    if (z->esq == NIL) {
        x = z->dir;
        transplante(z, z->dir);
    } else if (z->dir == NIL) {
        x = z->esq;
        transplante(z, z->esq);
    } else {
        y = minimo(z->dir);
        corOriginalY = y->cor;
        x = y->dir;
        if (y->pai == z) {
            x->pai = y;
        } else {
            transplante(y, y->dir);
            y->dir = z->dir;
            y->dir->pai = y;
        }
        transplante(z, y);
        y->esq = z->esq;
        y->esq->pai = y;
        y->cor = z->cor;
    }
    delete z;
    if (corOriginalY == PRETO) {
        corrigirRemocao(x);
    }
    return true;
}