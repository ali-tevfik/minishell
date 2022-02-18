# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: adoner <adoner@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/02/01 13:16:02 by adoner        #+#    #+#                  #
#    Updated: 2022/02/18 15:30:01 by hyilmaz       ########   odam.nl          #
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
			built_in/cd.c \
			built_in/pwd.c \
			built_in/echo.c \
			built_in/env.c \
			built_in/unset.c \
			built_in/export.c \
			read_line.c \
			expander.c \
			tokenizer/iterator_api.c \
			tokenizer/tokenize_dquotes.c \
			tokenizer/tokenize_pipe.c \
			tokenizer/tokenize_quotes.c \
			tokenizer/tokenize_redirection.c \
			tokenizer/tokenize_word.c \
			tokenizer/tokenizer_utils.c \
			tokenizer/tokenizer.c \
			tokenizer/validate_grammer.c \
			parser/create_parse_list.c \
			parser/create_simple_command.c \
			parser/parser_utils.c \
			fork/fork.c \
			src/executor/find_command.c\
			src/fork/waiting_last_child.c\
			src/fork/fork_file.c \
			src/match_str.c\
			src/create_envp.c \
			src/built_in/find_envp.c \
			src/built_in/file_name_check.c \
			src/built_in/create_lst_envp.c \
			src/built_in/delete_envp.c


TEST_FILES = 	unity/src/unity.c \
				unity/extras/fixture/src/unity_fixture.c \
				test/main/all_tests.c \
				test/main/all_tests_runner.c \
				test/test_unset.c \
				src/built_in/unset.c \
				src/built_in/export.c \
				test/test_export.c \
				src/expander.c \
				test/utils.c \
				test/test_tokenizer.c \
				src/tokenizer/tokenizer.c \
				test/test_iterator_api.c \
				src/tokenizer/iterator_api.c \
				test/test_tokenizer_utils.c \
				src/tokenizer/tokenizer_utils.c \
				test/test_tokenize_pipe.c \
				src/tokenizer/tokenize_pipe.c \
				test/test_tokenize_word.c \
				src/tokenizer/tokenize_word.c \
				test/test_tokenize_redirection.c \
				src/tokenizer/tokenize_redirection.c \
				test/test_tokenize_dquotes.c \
				src/tokenizer/tokenize_dquotes.c \
				test/test_tokenize_quotes.c \
				src/tokenizer/tokenize_quotes.c \
				test/test_validate_grammer.c \
				src/tokenizer/validate_grammer.c \
				test/test_create_simple_command.c \
				src/parser/create_simple_command.c \
				src/parser/parser_utils.c \
				test/test_create_parse_list.c \
				src/parser/create_parse_list.c \
				test/test_find_command.c \
				src/executor/find_command.c \
				src/built_in/env.c \
				src/match_str.c \
				src/built_in/delete_envp.c \
				src/create_envp.c \
				src/built_in/find_envp.c \
				src/built_in/file_name_check.c \
				src/built_in/create_lst_envp.c \
				src/expander/expand_single_variable.c \
				test/test_expand_single_variable.c

HEADER_FILES = 	incl/minishell.h

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
	@make -C $(LIBFT_DIR) bonus > /dev/null

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
debug: $(DBG_OBJ_DIR) $(LIBFT) $(DBG_NAME)

$(DBG_OBJ_DIR):
	@mkdir -p $@

$(DBG_NAME): $(DBG_OBJ)
	@$(GCC) $(FLAGS) $(DBG_FLAGS) $^ -o $@ -lreadline $(LIBFT_DIR)/$(LIBFT)
	@echo "$(GREEN) Created minishell debug executable.$(NORMAL)"

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
	@echo "$(GREEN) Created debug file.$(NORMAL)"

$(TEST_OBJ_FILES): $(TEST_OBJ_DIR)/%.o : %.c
	@mkdir -p $(@D)
	@$(GCC) $(FLAGS) $(UNITY_HEADERS) $(UNITY_OPTIONS) -c $< -o $@

clean:
	@rm -rdf $(OBJ_DIR) $(DBG_OBJ_DIR) $(TEST_OBJ_DIR)
	@make -C $(LIBFT_DIR) clean > /dev/null
	@echo "$(RED) Deleted all object files.$(NORMAL)"

fclean: clean
	@rm -f $(NAME) $(DBG_NAME) $(TEST_NAME)
	@make -C $(LIBFT_DIR) fclean > /dev/null
	@echo "$(RED) Deleted all executables.$(NORMAL)"

re: clean fclean all

.PHONY: clean fclean re
