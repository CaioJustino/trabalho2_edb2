#ifndef ARVORE_H
#define ARVORE_H

// Imports
#include <string>

/**
 * @class "Arvore"
 * @brief Classe abstrata que representa uma árvore qualquer.
 *
 * Assim, ela está em uma relação de herança com as classes
 * "ArvoreAVL" e "ArvoreRN", que devem implementar os métodos
 * de geração, inserção, remoção, busca binária e impressão.
 */
class Arvore {
    public:
        /**
         * @brief Destrutor virtual da classe.
         */
        virtual ~Arvore() = default;

        virtual void gerarArvoreAleatoria() = 0;

        virtual void inserir(int valor) = 0;

        virtual bool buscar(int valor) = 0;

        virtual std::string imprimir() = 0;
};

#endif