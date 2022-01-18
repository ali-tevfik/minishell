# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: hyilmaz <hyilmaz@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2022/01/12 22:21:32 by hyilmaz       #+#    #+#                  #
#    Updated: 2022/01/18 13:07:00 by hyilmaz       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

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

# Unity tester requirements
UNITY_HEADERS = -Iunity/extras/fixture/src/ \
				-Iunity/src

UNITY_OPTIONS = -D UNITY_FIXTURE_NO_EXTRAS \
				-D UNITY_OUTPUT_COLOR

# Source, tests, header and object files
SRC_DIR = src
SRC_FILES = minishell.c \
			parser/tokenizer.c

TEST_FILES = 	unity/src/unity.c \
				unity/extras/fixture/src/unity_fixture.c \
				test/main/all_tests.c \
				test/main/all_tests_runner.c \
				test/test_unity.c \
				src/test_unity.c \
				test/test_tokenizer.c \
				src/parser/tokenizer.c \
				test/test_iterator_api.c \
				src/parser/iterator_api.c

HEADER_FILES = 	incl/minishell.h \
				parser/tokenizer.h

OBJ_DIR = obj
OBJ = $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)

DBG_OBJ_DIR = dbg_obj
DBG_OBJ = $(SRC_FILES:%.c=$(DBG_OBJ_DIR)/%.o)

TEST_OBJ_DIR = test_obj
TEST_OBJ_FILES= $(TEST_FILES:%.c=$(TEST_OBJ_DIR)/%.o)

# Set VPATH to search in all source directories
VPATH = $(SRC_DIR)
				
# Program name
NAME = minishell
DBG_NAME = debug_minishell
TEST_NAME = test_minishell

# #Libft
LIBFT = libft.a
LIBFT_DIR = src/libft

# Build release
all: $(OBJ_DIR) $(LIBFT) $(NAME)

run: all
	./$(NAME)

# Build libft
$(LIBFT):
	@make -C $(LIBFT_DIR) bonus

# Build normal
$(OBJ_DIR):
	@mkdir -p $@

$(NAME): $(OBJ)
	$(GCC) $(FLAGS) $^ -o $@ $(LIBFT_DIR)/$(LIBFT) -lreadline
	@echo "$(GREEN) Created minishell executable.$(NORMAL)"

$(OBJ): $(OBJ_DIR)/%.o : %.c $(HEADER_FILES)
	@mkdir -p $(@D)
	@$(GCC) $(FLAGS) -c $< -o $@

# Build debug
debug: $(DBG_OBJ_DIR) $(DBG_NAME)

$(DBG_OBJ_DIR):
	@mkdir -p $@

$(DBG_NAME): $(DBG_OBJ)
	@echo "$(GREEN) Created minishell debug executable.$(NORMAL)"
	@$(GCC) $(FLAGS) $(DBG_FLAGS) $^ -o $@ -lreadline $(LIBFT_DIR)/$(LIBFT)

$(DBG_OBJ): $(DBG_OBJ_DIR)/%.o : %.c $(HEADER_FILES)
	@mkdir -p $(@D)
	@$(GCC) $(FLAGS) $(DBG_FLAGS) -c $< -o $@

# Build test
test: $(TEST_OBJ_DIR) $(LIBFT) $(TEST_NAME)

test_run: test
	@./$(TEST_NAME) -v

$(TEST_OBJ_DIR):
	@mkdir -p $@

$(TEST_NAME): $(TEST_OBJ_FILES)
	@$(GCC) $(FLAGS) $^ -o $@ $(LIBFT_DIR)/$(LIBFT)
	@echo "$(GREEN) Created unit-test executable.$(NORMAL)"

$(TEST_OBJ_FILES): $(TEST_OBJ_DIR)/%.o : %.c
	@mkdir -p $(@D)
	@$(GCC) $(FLAGS) $(UNITY_HEADERS) $(UNITY_OPTIONS) -c $< -o $@

clean:
	@rm -rdf $(OBJ_DIR) $(DBG_OBJ_DIR) $(TEST_OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo "$(RED) Deleted all object files.$(NORMAL)"

fclean: clean
	@rm -f $(NAME) $(DBG_NAME) $(TEST_NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "$(RED) Deleted all executables.$(NORMAL)"

re: fclean all
	
.PHONY: clean fclean re
	