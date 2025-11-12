# Compilador e bibliotecas necessárias
CC      = gcc
CFLAGS  = -O2
LIBS    = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Executável e diretórios
TARGET  = main
SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin

# Arquivos fonte .c e arquivos objetos .o
SRCS    = $(SRC_DIR)/main.c $(SRC_DIR)/game_functions.c
OBJS    = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
OUTPUT  = $(BIN_DIR)/$(TARGET)

# Default: gera o executável do jogo
all: $(OUTPUT)

# Fase de linkagem
$(OUTPUT): $(OBJS)
	$(CC) $^ -o $@ $(LIBS)

# Compilação parcial dos arquivos fonte
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/game_functions.h
	$(CC) $(CFLAGS) -c $< -o $@

# Limpa os arquivos gerados
clean:
	rm -f $(OBJ_DIR)/*.o $(OUTPUT)
