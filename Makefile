# Variables
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
TARGET = philosophers
SRC = $(SRC_DIR)/main.c $(SRC_DIR)/init.c $(SRC_DIR)/provi.c $(SRC_DIR)/utils.c $(SRC_DIR)/utils_threads.c $(SRC_DIR)/threads.c
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Reglas principales
all: $(TARGET)

# Compilación del ejecutable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compilación de archivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Creación del directorio de objetos si no existe
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Limpieza
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(TARGET)

# Reconstrucción total
re: fclean all

# Indicaciones para que make no borre los archivos intermedios automáticamente
.PHONY: all clean fclean re
