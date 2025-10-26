// Imports
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <queue>
#include <utility>

#include "arvore.h"

using namespace std;

/**
 * @brief Retorna a altura de um nó.
 * @param t Ponteiro para o nó.
 * @return Altura do nó.
 */
int ArvoreAVL::altura(No* t) {
    if (t) {
        return t->altura;
    }
    
    else {
        return 0;
    }
}

/**
 * @brief Atualiza a altura de um nó com base nos filhos.
 * @param t Ponteiro para o nó.
 */
void ArvoreAVL::atualizaAltura(No* t) {
    if (t) {
        t->altura = max(altura(t->esq), altura(t->dir)) + 1;
    }
}

/**
 * @brief Calcula a altura total da subárvore a partir de um nó.
 * @param no Nó raiz da subárvore.
 * @return Altura da subárvore.
 */
int ArvoreAVL::alturaTotal(No* no) {
    if (!no) {
        return 0;
    }
    
    else {
        return 1 + max(alturaTotal(no->esq), alturaTotal(no->dir));
    }
}

/**
 * @brief Calcula o fator de balanceamento de um nó.
 * @param t Ponteiro para o nó.
 * @return Diferença entre altura da subárvore esquerda e direita (fator de balanceamento).
 */
int ArvoreAVL::fatorBalanceamento(No* t) {
    if (t) {
        return altura(t->esq) - altura(t->dir);
    }
    
    else {
        return 0;
    }
}

/**
 * @brief Executa a rotação à esquerda em nó.
 * @param x Nó a ser rotacionado.
 * @return Novo nó raiz da subárvore.
 */
ArvoreAVL::No* ArvoreAVL::rotacaoEsquerda(No* x) {
    No* y = x->dir;
    No* T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    atualizaAltura(x);
    atualizaAltura(y);

    return y;
}

/**
 * @brief Executa a rotação à direita em um nó.
 * @param y Nó a ser rotacionado.
 * @return Novo nó raiz da subárvore.
 */
ArvoreAVL::No* ArvoreAVL::rotacaoDireita(No* y) {
    No* x = y->esq;
    No* T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    atualizaAltura(y);
    atualizaAltura(x);

    return x;
}

/**
 * @brief Balanceia uma subárvore a partir de um nó.
 * @param no Nó raiz da subárvore.
 * @return Novo nó raiz após balanceamento.
 */
ArvoreAVL::No* ArvoreAVL::balancear(No* no) {
    atualizaAltura(no);
    int fb = fatorBalanceamento(no);

    if (fb > 1 && fatorBalanceamento(no->esq) >= 0){
        return rotacaoDireita(no);
    }

    else if (fb > 1 && fatorBalanceamento(no->esq) < 0) {
        no->esq = rotacaoEsquerda(no->esq);
        return rotacaoDireita(no);
    }
    
    else if (fb < -1 && fatorBalanceamento(no->dir) <= 0) {
        return rotacaoEsquerda(no);
    }

    else if (fb < -1 && fatorBalanceamento(no->dir) > 0) {
        no->dir = rotacaoDireita(no->dir);
        return rotacaoEsquerda(no);
    }

    return no;
}

/**
 * @brief Gera uma árvore AVL aleatória.
 * Insere nós com valores de 0 a 100.
 */
void ArvoreAVL::gerarArvoreAleatoria() {
    srand(time(nullptr));

    int n = rand() % 10 + 1;

    for (int i = 0; i < n; i++) {
        int v = rand() % 101;
        inserir(v);
    }
}

/**
 * @brief Imprime a árvore gerada.
 * @return String formatada da árvore.
 */
std::string ArvoreAVL::imprimir() {
    if (raiz == nullptr) {
        return "Árvore vazia.\n";
    }

    struct NoInfo {
        No* node;
        int pos;
    };

    int h = alturaTotal(raiz);
    if (h <= 0) return "Árvore vazia.\n";

    const int MAX_WIDTH = 4096;
    long long width_ll = (1LL << h) * 2LL;
    int width = (width_ll > MAX_WIDTH) ? MAX_WIDTH : static_cast<int>(width_ll);
    if (width < 32) width = 32;

    std::queue<NoInfo> q;
    q.push({raiz, width / 2});

    int level = 0;
    int nodesInLevel = 1;

    std::ostringstream out;

    while (!q.empty() && level < h) {
        std::vector<char> line(width, ' ');
        std::vector<char> branch(width, ' ');

        int nextLevelNodes = 0;

        for (int i = 0; i < nodesInLevel; ++i) {
            NoInfo ni = q.front();
            q.pop();

            if (ni.node != nullptr) {
                std::string keyStr = std::to_string(ni.node->valor);

                for (size_t j = 0; j < keyStr.size(); ++j) {
                    int idx = ni.pos + static_cast<int>(j);
                    if (idx >= 0 && idx < width) line[idx] = keyStr[j];
                }

                if (ni.node->esq != nullptr) {
                    int idx = ni.pos - 1;
                    if (idx >= 0 && idx < width) branch[idx] = '/';
                }
                if (ni.node->dir != nullptr) {
                    int idx = ni.pos + static_cast<int>(keyStr.size());
                    if (idx >= 0 && idx < width) branch[idx] = '\\';
                }

                int gap = (h - level >= 2) ? (1 << (h - level - 2)) : 1;
                q.push({ni.node->esq, ni.pos - gap});
                q.push({ni.node->dir, ni.pos + gap});
                nextLevelNodes += 2;
            } else {
                int gap = (h - level >= 2) ? (1 << (h - level - 2)) : 1;
                q.push({nullptr, ni.pos - gap});
                q.push({nullptr, ni.pos + gap});
                nextLevelNodes += 2;
            }
        }

        for (char ch : line) out << ch;
        out << '\n';
        for (char ch : branch) out << ch;
        out << '\n';

        nodesInLevel = nextLevelNodes;
        ++level;

        bool allNull = true;
        std::queue<NoInfo> tmpq = q;
        for (int i = 0; i < nodesInLevel && !tmpq.empty(); ++i) {
            if (tmpq.front().node != nullptr) { allNull = false; break; }
            tmpq.pop();
        }
        if (allNull) break;
    }

    return out.str();
}

/**
 * @brief Retorna o nó com o menor valor a partir de um determinado nó.
 * @param no Ponteiro para o nó inicial.
 */
ArvoreAVL::No* ArvoreAVL::minimo(No* no) {
    while (no && no->esq) no = no->esq;
    return no;
}

/**
 * @brief Remove recursivamente um nó da árvore AVL.
 *
 * Este método:
 * - Encontra o nó a ser removido.
 * - Realiza a remoção conforme o caso (0, 1 ou 2 filhos).
 * - Atualiza as alturas e realiza rotações necessárias para manter o balanceamento.
 *
 * @param no Ponteiro para o nó atual.
 * @param valor Valor a ser removido.
 */
ArvoreAVL::No* ArvoreAVL::removerRec(No* no, int valor) {
    if (!no) return no;

    if (valor < no->valor)
        no->esq = removerRec(no->esq, valor);
    else if (valor > no->valor)
        no->dir = removerRec(no->dir, valor);
    else {
        if (!no->esq) {
            No* temp = no->dir;
            delete no;
            return temp;
        } else if (!no->dir) {
            No* temp = no->esq;
            delete no;
            return temp;
        }

        No* temp = minimo(no->dir);
        no->valor = temp->valor;
        no->dir = removerRec(no->dir, temp->valor);
    }

    atualizaAltura(no);
    return balancear(no);
}