# Compilador e bibliotecas necessárias
CC      = gcc
LIBS    = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Executável e diretórios
TARGET  = main
SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin

# Arquivos fonte e objetos
SRCS    = $(SRC_DIR)/main.c $(SRC_DIR)/game_functions.c
OBJS    = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
OUTPUT  = $(BIN_DIR)/$(TARGET)

# Default: arquivo executável do jogo na pasta /bin
all: $(OUTPUT)

# Fase de linkagem e geração do executável
$(OUTPUT): $(OBJS) | $(BIN_DIR)
	$(CC) $^ -o $@ $(LIBS)

# Compilação parcial dos arquivos fonte
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/game_functions.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Cria os diretórios se já não existem
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Limpando os arquivos gerados
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)