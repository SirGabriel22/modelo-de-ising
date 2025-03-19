# Compilador de C:
CC = gcc

# Flags do compilador:

CFLAGS = -O2

# Biblioteca matemática:

LIBS = -lm

# Arquivo-fonte e cabeçalho:

SRC = modeloising.c
HEADERS = funcoesising.h

# Nome do executável

TARGET = saida.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compilação do programa:

$(TARGET): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

clean:
	@rm -f $(TARGET) *.o *.mod
