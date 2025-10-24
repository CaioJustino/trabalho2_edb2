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
    if (!raiz) {
        return "Árvore vazia.\n";
    }

    std::ostringstream oss;
    std::queue<No*> fila;
    fila.push(raiz);

    int h = alturaTotal(raiz);
    int nivel = 0;
    int elementosNoNivel = 1;
    int proximoNivel = 0;
    int espaco = (1 << (h - 1)) * 3;

    while (!fila.empty()) {
        std::ostringstream linhaNos, linhaConexoes;
        bool temProximoNivel = false;

        for (int i = 0; i < elementosNoNivel; i++) {
            No* no = fila.front();
            fila.pop();

            linhaNos << std::setw(espaco)
                     << (no ? std::to_string(no->valor) : " ");

            if (no) {
                fila.push(no->esq);
                fila.push(no->dir);
                proximoNivel += 2;
                
                if (no->esq || no->dir) {
                    temProximoNivel = true;
                }

                linhaConexoes << std::setw(espaco - 2)
                              << (no->esq ? "/" : " ")
                              << " "
                              << (no->dir ? "\\" : " ");
            }
            
            else {
                fila.push(nullptr);
                fila.push(nullptr);
                proximoNivel += 2;
                linhaConexoes << std::setw(espaco) << " ";
            }
        }

        oss << linhaNos.str() << "\n";
        
        if (temProximoNivel) {
            oss << linhaConexoes.str() << "\n";
        }

        nivel++;
        
        if (!temProximoNivel) {
            break;
        }

        elementosNoNivel = proximoNivel;
        proximoNivel = 0;
        espaco = std::max(espaco / 2, 3);
    }

    return oss.str();
}