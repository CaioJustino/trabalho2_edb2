// Imports
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <queue>
#include <utility>
#include <set>

#include "arvore.h"

using namespace std;

/**
 * @brief Construtor da classe.
 * Inicializa o nó NIL e define a raiz como NIL.
 */
ArvoreRN::ArvoreRN() {
    NIL = new No(0);
    NIL->cor = PRETO;
    NIL->esq = NIL->dir = NIL->pai = NIL;
    raiz = NIL;
}

/**
 * @brief Calcula a altura total da subárvore a partir de um nó.
 * @param no Nó raiz da subárvore.
 * @return Altura da subárvore.
 */
int ArvoreRN::alturaTotal(No* no) {
    if (no == NIL) {
        return 0;
    }

    return 1 + max(alturaTotal(no->esq), alturaTotal(no->dir));
}

/**
 * @brief Realiza a rotação à esquerda em um nó.
 * @param x Nó a ser rotacionado.
 * @return Novo nó raiz da subárvore.
 */
void ArvoreRN::rotacaoEsquerda(No* x) {
    if (x == NIL) {
        return;
    }
    No* y = x->dir;
    
    if (y == NIL) {
        return;
    }
    x->dir = y->esq;
    
    if (y->esq != NIL) {
        y->esq->pai = x;
    }
    y->pai = x->pai;
    
    if (x->pai == NIL) {
        raiz = y;
    }

    if (x == x->pai->esq) {
        x->pai->esq = y;
    }

    else {
        x->pai->dir = y;
    }

    y->esq = x;
    x->pai = y;
}

/**
 * @brief Realiza a rotação à direita em um nó.
 * @param y Nó a ser rotacionado.
 * @return Novo nó raiz da subárvore.
 */
void ArvoreRN::rotacaoDireita(No* y) {
    if (y == NIL) {
        return;
    }
    No* x = y->esq;
    
    if (x == NIL) {
        return;
    }
    y->esq = x->dir;
    
    if (x->dir != NIL) {
        x->dir->pai = y;
    }
    x->pai = y->pai;
    
    if (y->pai == NIL) {
        raiz = x;
    }

    if (y == y->pai->dir) {
        y->pai->dir = x;
    }

    else {
        y->pai->esq = x;
    }

    x->dir = y;
    y->pai = x;
}

/**
 * @brief Gera uma árvore rubro-negra aleatória.
 * Insere nós com valores de 0 a 100.
 */
void ArvoreRN::gerarArvoreAleatoria() {
    srand((unsigned)time(nullptr));

    int n = rand() % 10 + 1;

    set<int> usados;

    while ((int)usados.size() < n) {
        int v = rand() % 101;

        if (usados.insert(v).second) {
            inserir(v);
        }
    }
}

/**
 * @brief Imprime a árvore gerada.
 * @return String formatada da árvore.
 */
std::string ArvoreRN::imprimir() {
    if (raiz == NIL) {
        return "Árvore vazia.\n";
    }

    struct NoInfo {
        No* node;
        int pos;
    };

    int h = alturaTotal(raiz);
    if (h <= 0) return "Árvore vazia.\n";

    const int MAX_WIDTH = 4096;
    long long width_ll = (1LL << (h + 3));
    int width = (width_ll > MAX_WIDTH) ? MAX_WIDTH : static_cast<int>(width_ll);
    if (width < 64) width = 64;

    std::queue<NoInfo> q;
    q.push({raiz, width / 2});

    int level = 0;
    int nodesInLevel = 1;

    std::ostringstream out;

    while (!q.empty() && level < h) {
        std::vector<char> line(width, ' ');
        std::vector<char> branch(width, ' ');

        int nextLevelNodes = 0;

        int gap = std::max(2, (1 << (h - level - 1)));

        for (int i = 0; i < nodesInLevel; ++i) {
            NoInfo ni = q.front();
            q.pop();

            if (ni.node && ni.node != NIL) {
                std::string colorStr = (ni.node->cor == VERMELHO) ? "(V)" : "(P)";
                std::string keyStr = std::to_string(ni.node->valor) + colorStr;

                int len = static_cast<int>(keyStr.size());
                int start = ni.pos - len / 2;
                if (start < 0) start = 0;
                int end = std::min(start + len, width);

                for (int j = start; j < end; ++j) {
                    line[j] = keyStr[j - start];
                }

                if (ni.node->esq != NIL) {
                    int idx = ni.pos - gap / 2;
                    if (idx >= 0 && idx < width) branch[idx] = '/';
                }
                if (ni.node->dir != NIL) {
                    int idx = ni.pos + gap / 2;
                    if (idx >= 0 && idx < width) branch[idx] = '\\';
                }

                q.push({ni.node->esq, ni.pos - gap});
                q.push({ni.node->dir, ni.pos + gap});
                nextLevelNodes += 2;
            } else {
                q.push({NIL, ni.pos - gap});
                q.push({NIL, ni.pos + gap});
                nextLevelNodes += 2;
            }
        }

        for (char ch : line) out << ch;
        out << '\n';
        for (char ch : branch) out << ch;
        out << '\n';

        nodesInLevel = nextLevelNodes;
        ++level;

        bool allNil = true;
        std::queue<NoInfo> tmp = q;
        for (int i = 0; i < nodesInLevel && !tmp.empty(); ++i) {
            if (tmp.front().node != NIL) { allNil = false; break; }
            tmp.pop();
        }
        if (allNil) break;
    }

    return out.str();
}

/**
 * @brief Busca um nó com o valor especificado na árvore rubro-negra.
 * @param valor Valor do nó a ser buscado.
 */
ArvoreRN::No* ArvoreRN::buscarNo(int valor) {
    No* atual = raiz;
    while (atual != NIL) {
        if (valor == atual->valor) return atual;
        else if (valor < atual->valor) atual = atual->esq;
        else atual = atual->dir;
    }
    return NIL;
}

/**
 * @brief Retorna o nó mínimo (menor valor) a partir de um nó dado.
 * @param no Nó inicial.
 */
ArvoreRN::No* ArvoreRN::minimo(No* no) {
    while (no->esq != NIL) no = no->esq;
    return no;
}

/**
 * @brief Substitui uma subárvore por outra durante remoção.
 * 
 * Este método liga o pai do nó `u` ao nó `v`, substituindo a posição de `u` por `v`.
 *
 * @param u Nó a ser substituído.
 * @param v Nó que substitui `u`.
 */
void ArvoreRN::transplante(No* u, No* v) {
    if (u->pai == NIL) {
        raiz = v;
    } else if (u == u->pai->esq) {
        u->pai->esq = v;
    } else {
        u->pai->dir = v;
    }
    v->pai = u->pai;
}

/**
 * @brief Corrige as propriedades da árvore rubro-negra após uma remoção.
 *
 * Esse método garante que as propriedades de balanceamento e coloração da árvore
 * sejam mantidas após a remoção de um nó preto. Realiza rotações e recolorações
 * conforme necessário.
 *
 * @param x Nó a partir do qual a correção deve ser iniciada.
 */
void ArvoreRN::corrigirRemocao(No* x) {
    while (x != raiz && x->cor == PRETO) {
        if (x == x->pai->esq) {
            No* w = x->pai->dir;
            if (w->cor == VERMELHO) {
                w->cor = PRETO;
                x->pai->cor = VERMELHO;
                rotacaoEsquerda(x->pai);
                w = x->pai->dir;
            }
            if (w->esq->cor == PRETO && w->dir->cor == PRETO) {
                w->cor = VERMELHO;
                x = x->pai;
            } else {
                if (w->dir->cor == PRETO) {
                    w->esq->cor = PRETO;
                    w->cor = VERMELHO;
                    rotacaoDireita(w);
                    w = x->pai->dir;
                }
                w->cor = x->pai->cor;
                x->pai->cor = PRETO;
                w->dir->cor = PRETO;
                rotacaoEsquerda(x->pai);
                x = raiz;
            }
        } else {
            No* w = x->pai->esq;
            if (w->cor == VERMELHO) {
                w->cor = PRETO;
                x->pai->cor = VERMELHO;
                rotacaoDireita(x->pai);
                w = x->pai->esq;
            }
            if (w->dir->cor == PRETO && w->esq->cor == PRETO) {
                w->cor = VERMELHO;
                x = x->pai;
            } else {
                if (w->esq->cor == PRETO) {
                    w->dir->cor = PRETO;
                    w->cor = VERMELHO;
                    rotacaoEsquerda(w);
                    w = x->pai->esq;
                }
                w->cor = x->pai->cor;
                x->pai->cor = PRETO;
                w->esq->cor = PRETO;
                rotacaoDireita(x->pai);
                x = raiz;
            }
        }
    }
    x->cor = PRETO;
}