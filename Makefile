# Compilador e Option Flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I.

# Nome do Arquivo Executável
TARGET = programa

# Fontes
SRC = main.cpp \
      avl/arvore.cpp \
      avl/insercao.cpp \
      avl/buscabinaria.cpp \
      avl/remocao.cpp \
      rubro-negra/arvore.cpp \
      rubro-negra/insercao.cpp \
      rubro-negra/buscabinaria.cpp \
      rubro-negra/remocao.cpp

# Objetos
OBJ = $(SRC:.cpp=.o)

# Regra Padrão: Compilar Tudo
make: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Executar o Programa
run: $(TARGET)
	./$(TARGET)

# Limpar Arquivos Compilados
clean:
	rm -f $(OBJ) $(TARGET)