# Colors
GREEN = \033[38;5;2m
NORMAL = \033[38;5;255m
RED = \033[38;5;1m
BLUE = \033[38;5;4m
YELLOW = \033[1;33m

# Compiler settings
GCC = gcc
FLAGS = -Wall -Wextra -Werror
DBG_FLAGS = -g -fsanitize=address

# Source, header and object files
SRC_DIR = src
SRC_FILES = minishell.c

HEADER_FILES = incl/minishell.h

OBJ_DIR = obj
OBJ = $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)

DBG_OBJ_DIR = dbg_obj
DBG_OBJ = $(SRC_FILES:%.c=$(DBG_OBJ_DIR)/%.o)

# Set VPATH to search in all source directories
VPATH = $(SRC_DIR)

# Program name
NAME = minishell
DBG_NAME = debug_minishell

# Build release
all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $@

$(NAME): $(OBJ)
	@$(GCC) $(FLAGS) $^ -o $@
	@echo "$(GREEN) Created minishell executable.$(NORMAL)"

$(OBJ): $(OBJ_DIR)/%.o : %.c $(HEADER_FILES)
	@$(GCC) $(FLAGS) -c $< -o $@

# Build debug
debug: $(DBG_OBJ_DIR) $(DBG_NAME)

$(DBG_OBJ_DIR):
	@mkdir -p $@

$(DBG_NAME): $(DBG_OBJ)
	@echo "$(GREEN) Created minishell debug executable.$(NORMAL)"
	@$(GCC) $(FLAGS) $(DBG_FLAGS) $^ -o $@

$(DBG_OBJ): $(DBG_OBJ_DIR)/%.o : %.c $(HEADER_FILES)
	@$(GCC) $(FLAGS) $(DBG_FLAGS) -c $< -o $@

clean:
	@rm -rdf $(OBJ_DIR) $(DBG_OBJ_DIR)
	@echo "$(RED) Deleted all object files.$(NORMAL)"

fclean: clean
	@rm -f $(NAME) $(DBG_NAME)
	@echo "$(RED) Deleted all executables.$(NORMAL)"

re: fclean all
	
.PHONY: clean fclean re
	