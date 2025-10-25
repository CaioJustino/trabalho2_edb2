// Imports
#include <algorithm>

#include "arvore.h"

using namespace std;

/**
 * @brief Remove um nó da árvore AVL.
 *
 * O método verifica se o valor existe e, se encontrado, chama o método recursivo
 * de remoção que garante o balanceamento da árvore após a exclusão.
 *
 * @param valor Valor do nó a ser removido.
 */
bool ArvoreAVL::remover(int valor) {
    if (!buscar(valor)) return false;
    raiz = removerRec(raiz, valor);
    return true;
}