# Trabalho Unidade 2: Árvores Balanceadas (AVL e Rubro-Negra)

A princípio, o objetivo desse presente trabalho é, por meio de um projeto prático e de um relatório técnico, desenvolver, implementar e analisar o funcionamento de árvores balanceadas, especificamente as árvores AVL e rubro-negra. As árvores geradas possuem média de 10 nós e os nós podem ser inseridos com valores de 0 a 100.
<br><br>

## 🔍 Operações Implementadas
1. Geração Aleatória de Árvores
2. Inserção de Nós
3. Busca Binária
4. Remoção de Nós
5. Impressão das Árvores
<br><br>

## 🛠️ Tecnologias Utilizadas
- Linguagem principal: [C++](https://devdocs.io/cpp)
- Ferramenta de desenvolvimento: [VS Code](https://code.visualstudio.com)
<br><br>

## 📚 Bibliotecas Utilizadas

- `iostream`: entrada e saída de dados.
- `limits`:  fornece informações sobre os limites numéricos.
- `memory`: fornece ferramentas para gerenciamento de memória.
- `iomanip`: manipula a formatação de entrada e saída.
- `sstream`: permite tratar uma string como um fluxo de entrada/saída.
- `cstdlib`: rand(), srand(), etc.
- `ctime`: time() para sementes aleatórias.
- `algorithm`: std::max, std::min.
- `queue`: std::queue (usado em impressão).
- `utility`: std::pair, std::make_pair.
- `string`: std::string, std::to_string.
<br><br>

## ⚠️ Dependências Necessárias
- Compilador: [GCC (GNU Compiler Collection)](https://gcc.gnu.org)
<br><br>

## ⚙️ Configuração e Instalação

1. Clone este repositório em sua máquina local.

```
git clone https://github.com/CaioJustino/trabalho2_edb2.git
```
<br>

2. Navegue até a pasta do projeto.

```
cd trabalho2_edb2
```
<br>

3. Em seguida, execute o comando `make` e, logo em seguida,  `make run`.

```
make
```
```
make run
```
<br>

4. Exemplo de saída (fluxo de árvore AVL):

```
 __  __                  
|  \/  | ___ _ __  _   _ 
| |\/| |/ _ \ '_ \| | | |
| |  | |  __/ | | | |_| |
|_|  |_|\___|_| |_|\__,_|

1 - Gerar uma árvore AVL aleatória.
2 - Gerar uma árvore rubro-negra aleatória.

3 - Inserir um nó na árvore AVL gerada.
4 - Inserir um nó na árvore rubro-negra gerada.

5 - Buscar um valor na árvore AVL gerada.
6 - Buscar um valor na árvore rubro-negra gerada.

7 - Imprimir a árvore AVL gerada.
8 - Imprimir a árvore rubro-negra gerada.

9 - Remover um nó da árvore AVL gerada.
10 - Remover um nó da árvore rubro-negra gerada.

0 - Encerrar a execução do programa.
Opção: 1

Árvore AVL gerada com sucesso!
 __  __                  
|  \/  | ___ _ __  _   _ 
| |\/| |/ _ \ '_ \| | | |
| |  | |  __/ | | | |_| |
|_|  |_|\___|_| |_|\__,_|

1 - Gerar uma árvore AVL aleatória.
2 - Gerar uma árvore rubro-negra aleatória.

3 - Inserir um nó na árvore AVL gerada.
4 - Inserir um nó na árvore rubro-negra gerada.

5 - Buscar um valor na árvore AVL gerada.
6 - Buscar um valor na árvore rubro-negra gerada.

7 - Imprimir a árvore AVL gerada.
8 - Imprimir a árvore rubro-negra gerada.

9 - Remover um nó da árvore AVL gerada.
10 - Remover um nó da árvore rubro-negra gerada.

0 - Encerrar a execução do programa.
Opção: 7

# - ÁRVORE AVL GERADA:

                77              
               /  \             
            35      96          
           /  \    /  \         
          14  39  85  100       
```
<br><br>

Discentes: Bianca Pires, Bruna Dantas e Caio Justino.
