#ifndef ARVORE_RN_H
#define ARVORE_RN_H

// Imports
#include "../arvore.h"

/** @enum "Cor"
 *  @brief Cores dos nós da árvore Rubro-Negra.
 */
enum Cor { VERMELHO, PRETO };

/**
 * @class "ArvoreRN"
 * @brief Classe que implementa uma árvore Rubro-Negra balanceada.
 * Aqui, são implementadas os métodos virtuais da classe
 * abstrata "Arvore".
 */
class ArvoreRN : public Arvore {
    public:
        /**
         * @struct "No"
         * @brief Estrutura de um nó da Rubro-Negra.
         */
        struct No {
            int valor;  
            Cor cor;   
            No* esq;    
            No* dir;    
            No* pai; 
            No(int v) : valor(v), cor(VERMELHO), esq(nullptr), dir(nullptr), pai(nullptr) {}
        };

        /** 
         * @brief Raíz da árvore.
         */
        No* raiz;
        
        /** 
         * @brief Nó sentinel.
         */
        No* NIL;

        /** 
         * @brief Construtor da classe.
         */
        ArvoreRN();

        /**
         * @brief Gera uma árvore Rubro-Negra com valores aleatórios.
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
        int alturaTotal(No* no);
        void rotacaoEsquerda(No* x);
        void rotacaoDireita(No* y);
        void corrigirInsercao(No* z);
};

#endif