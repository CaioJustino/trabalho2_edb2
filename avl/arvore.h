#ifndef ARVORE_AVL_H
#define ARVORE_AVL_H

// Imports
#include "../arvore.h"

/**
 * @class "ArvoreAVL"
 * @brief Classe que implementa uma árvore AVL balanceada.
 * Aqui, são implementadas os métodos virtuais da classe
 * abstrata "Arvore".
 */
class ArvoreAVL : public Arvore {
    public:
        /**
         * @struct "No"
         * @brief Estrutura de um nó de uma árvore AVL.
         */
        struct No {
            int valor;      
            No* esq;        
            No* dir;        
            int altura;     
            No(int v) : valor(v), esq(nullptr), dir(nullptr), altura(1) {}
        };

        
        /**
         * @brief Raíz da árvore.
         */
        No* raiz;

        /**
         * @brief Construtor da classe.
         */
        ArvoreAVL() : raiz(nullptr) {}

        /**
         * @brief Gera uma árvore AVL com valores aleatórios.
         */
        void gerarArvoreAleatoria() override;

        /**
         * @brief Insere um nó na árvore.
         */
        void inserir(int valor) override;

        /**
         * @brief Imprime a árvore.
         */
        std::string imprimir() override;

    private:
        int altura(No* t);
        void atualizaAltura(No* t);
        int alturaTotal(No* no);
        int fatorBalanceamento(No* t);
        No* rotacaoEsquerda(No* x);
        No* rotacaoDireita(No* y);
        No* balancear(No* no);
};

#endif