#include "arvore.h"
#include <algorithm>
using namespace std;

bool ArvoreAVL::remover(int valor) {
    if (!buscar(valor)) return false;
    raiz = removerRec(raiz, valor);
    return true;
}