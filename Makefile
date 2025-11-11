# Compilador e bibliotecas necessárias
CC      = gcc
LIBS    = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Executável e diretório para os arquivos .o
TARGET  = main
SRC_DIR = .
OBJ_DIR = obj

# Arquivos fonte e objetos
SRCS    = $(SRC_DIR)/main.c $(SRC_DIR)/game_functions.c
OBJS    = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Default: Executável do jogo
all: $(TARGET)

# Fase de linkagem
$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(LIBS)

# Compilando os arquivos fonte .c em arquivos objetos .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/game_functions.h | $(OBJ_DIR)
	$(CC) -c $< -o $@

# Cria diretório 'obj' se já não existe
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Limpando os arquivos gerados
clean:
	rm -rf $(OBJ_DIR) $(TARGET)
