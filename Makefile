# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/28 13:03:05 by gwolf             #+#    #+#              #
#    Updated: 2023/08/18 13:52:49 by gwolf            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ******************************
# *     Text effects           *
# ******************************

RESET := \033[0m
BOLD := \033[1m
BLACK := \033[30m
GREEN := \033[32m
YELLOW := \033[33m
RED := \033[31m
BLUE := \033[34m

# ******************************
# *     Directories            *
# ******************************

SRC_DIR := src
OBJ_DIR := obj
LIB_DIR := lib
LIB_DIR_FT := $(LIB_DIR)/libft
INC_DIR := inc
DEP_DIR := $(OBJ_DIR)/dep
TEST_DIR := tests

# ******************************
# *     Libraries              *
# ******************************

LDFLAGS := -L $(LIB_DIR_FT)
LDLIBS := -l ft -l readline

# ******************************
# *     Vars for compiling     *
# ******************************

CC := cc
CPPFLAGS := -I $(INC_DIR) -I lib/libft
CFLAGS = -Wall -Werror -Wextra -g -gdwarf-4
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEP_DIR)/$*.Td
COMPILE = $(CC) $(DEPFLAGS) $(CPPFLAGS) $(CFLAGS) -c
POSTCOMPILE = @mv -f $(DEP_DIR)/$*.Td $(DEP_DIR)/$*.d && touch $@

# ******************************
# *     Targets                *
# ******************************

NAME := minishell
LIBFT := $(LIB_DIR_FT)/libft.a
TEST := test

# ******************************
# *     Source files           *
# ******************************

SRC :=	utils_memory.c \
		utils_string.c \
		buffer.c \
		hashtable_generate.c \
		hashtable_utils.c \
		exit_failure.c \
		env_setup.c \
		env_pwd.c \
		env_shlvl.c \
		env_pid.c \
		env_envp.c \
		prompt.c \
		prompt_replace_token.c \
		prompt_replace_h.c \
		prompt_replace_u.c \
		prompt_replace_small.c \
		prompt_replace_w.c \
		lexer_utils.c \
		lexer.c \
		lexer_src.c \
		lexer_tok.c \
		lexer_tok_utils.c \
		syntax.c \
		expand_expander.c \
		expand_field_split.c \
		expand_tilde.c \
		expand_utils.c \
		expand_dollar.c \
		expand.c \
		handle_input.c \
		parser.c \
		parser_utils.c \
		parser_fill_cmd.c \
		builtin_utils.c \
		builtin_error.c \
		builtin_echo.c \
		builtin_cd.c \
		builtin_pwd.c \
		builtin_export.c \
		builtin_unset.c \
		builtin_env.c \
		builtin_exit.c \
		executor.c \
		executor_create_child.c \
		executor_child.c \
		executor_cleanup.c \
		executor_cleanup2.c \
		executor_utils.c \
		executor_utils2.c \
		executor_heredoc.c \
		executor_heredoc2.c \
		executor_builtin.c \
		cleanup.c \
		tkn_list_create.c \
		tkn_list_delete.c \
		tkn_list_search.c \
		signal.c \
		error_temp.c
SRCS := $(addprefix $(SRC_DIR)/, $(SRC))

# ******************************
# *     Object files           *
# ******************************

OBJ := $(SRC:.c=.o)
OBJS := $(addprefix $(OBJ_DIR)/, $(OBJ))
OBJ_MAIN = $(OBJ_DIR)/main.o

# ******************************
# *     Dependency files       *
# ******************************

DEPFILES = $(SRC:%.c=$(DEP_DIR)/%.d)
# add dependency for main, since not in SRC
DEPFILES += $(DEP_DIR)/main.d

# ******************************
# *     Test files             *
# ******************************

TEST_SRC := test_replace_token.c \
			test_prompt.c \
			test_hashtable.c \
			test_lexer.c \
			test_check_syntax.c \
			test_env_envp.c \
			test_expand_expander.c \
			test_expand_field_split.c \
			test_expand_handler.c \
			test_expand.c \
			test_parser.c \
			test_builtin_echo.c \
			test_builtin_cd.c \
			test_builtin_pwd.c \
			test_builtin_export.c \
			test_builtin_unset.c \
			test_builtin_env.c \
			test_builtin_exit.c \
			test_executor.c \
			test_buffer.c
TEST_SRCS := $(addprefix $(TEST_DIR)/, $(TEST_SRC))
TEST_OBJ := $(TEST_SRC:.c=.o)
TEST_OBJS := $(addprefix $(TEST_DIR)/, $(TEST_OBJ))
TEST_OBJ_MAIN = $(TEST_DIR)/test_main.o

.PHONY: all
all: $(NAME)

# ******************************
# *     NAME linkage           *
# ******************************

# Linking the NAME target
$(NAME): $(LIBFT) $(OBJS) $(OBJ_MAIN)
	@printf "\n$(YELLOW)$(BOLD)link binary$(RESET) [$(BLUE)minishell$(RESET)]\n"
	$(CC) $(LDFLAGS) $(OBJS) $(OBJ_MAIN) $(LDLIBS) -o $@
	@printf "\n$(YELLOW)$(BOLD)compilation successful$(RESET) [$(BLUE)minishell$(RESET)]\n"
	@printf "$(BOLD)$(GREEN)$(NAME) created!$(RESET)\n\n"

# This target adds fsanitize leak checker to the flags. It needs to clean and recompile.
.PHONY: leak
leak: CFLAGS += -fsanitize=leak
leak: LDFLAGS += -fsanitize=leak
leak: clean $(NAME)
	@printf "Compiled with $(YELLOW)$(BOLD)fsanitize=leak$(RESET)\n\n"

# This target adds fsanitize address checker to the flags. It needs to clean and recompile.
.PHONY: address
address: CFLAGS += -fsanitize=address
address: LDFLAGS += -fsanitize=address
address: clean $(NAME)
	@printf "Compiled with $(YELLOW)$(BOLD)fsanitize=address$(RESET)\n\n"

# Perform memory check on NAME. Needs manual clean if target leak or address was called before
.PHONY: valgr
valgr: $(NAME)
	@valgrind --leak-check=full\
			--show-leak-kinds=all\
			--trace-children=no\
			--track-fds=no\
			--log-file=valgrind-out.txt\
			./$(NAME)
	@less ./valgrind-out.txt

# ******************************
# *     TEST linkage           *
# ******************************

# Create the binary TEST, which has its own test_main.
$(TEST): CFLAGS = -g -gdwarf-4
$(TEST): $(LIBFT) $(OBJS) $(TEST_OBJS) $(TEST_OBJ_MAIN)
	@printf "\n$(YELLOW)$(BOLD)link test binary$(RESET) [$(BLUE)minishell$(RESET)]\n"
	$(CC) $(LDFLAGS) $(OBJS) $(TEST_OBJS) $(TEST_OBJ_MAIN) $(LDLIBS) -o $@
	@printf "\n$(YELLOW)$(BOLD)compilation successful$(RESET) [$(BLUE)minishell$(RESET)]\n"
	@printf "$(BOLD)$(GREEN)$(TEST) created!$(RESET)\n\n"

# This target adds fsanitize leak checker to the flags. It needs to clean and recompile.
.PHONY: tleak
tleak: CFLAGS += -fsanitize=leak
tleak: LDFLAGS += -fsanitize=leak
tleak: clean tclean $(TEST)
	@printf "Compiled with $(YELLOW)$(BOLD)fsanitize=leak$(RESET)\n\n"

# This target adds fsanitize address checker to the flags. It needs to clean and recompile.
.PHONY: taddress
taddress: CFLAGS += -fsanitize=address
taddress: LDFLAGS += -fsanitize=address
taddress: clean tclean $(TEST)
	@printf "Compiled with $(YELLOW)$(BOLD)fsanitize=address$(RESET)\n\n"

# Perform memory check on TEST. Needs manual clean if tleak or taddress was called before
.PHONY: tvalgr
tvalgr: $(TEST)
	@valgrind --leak-check=full\
			--show-leak-kinds=all\
			--trace-children=no\
			--track-fds=no\
			--log-file=valgrind-out.txt\
			./$(TEST)
	@less ./valgrind-out.txt

# ******************************
# *     Object compiling and   *
# *     dependecy creation     *
# ******************************

# Create object and dependency files
# $(DEP_DIR)/%.d =	Declare the generated dependency file as a prerequisite of the target,
# 					so that if it’s missing the target will be rebuilt.
# | $(DEPDIR) = 	Declare the dependency directory as an order-only prerequisite of the target,
# 					so that it will be created when needed.
# $(POSTCOMPILE) =	Move temp dependency file and touch object to ensure right timestamps.
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEP_DIR)/%.d message | $(DEP_DIR)
	$(COMPILE) $< -o $@
	$(POSTCOMPILE)

# Print message only if there are objects to compile
.INTERMEDIATE: message
message:
	@printf "\n$(YELLOW)$(BOLD)compile objects$(RESET) [$(BLUE)minishell$(RESET)]\n"

# Create objects from test source files
$(TEST_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Create directory obj/dep if it doesn't exist
$(DEP_DIR):
	@printf "\n$(YELLOW)$(BOLD)create subdir$(RESET) [$(BLUE)minishell$(RESET)]\n"
	mkdir -p $@

# Mention each dependency file as a target, so that make won’t fail if the file doesn’t exist.
$(DEPFILES):

# ******************************
# *     External Libraries     *
# ******************************

# Use Makefile of libft to compile the library.
$(LIBFT):
	@printf "$(YELLOW)$(BOLD)compilation$(RESET) [$(BLUE)libft$(RESET)]\n"
	$(MAKE) -s -C $(LIB_DIR)/libft

# ******************************
# *     Cleanup                *
# ******************************

.PHONY: clean
clean:
	@printf "$(YELLOW)$(BOLD)clean$(RESET) [$(BLUE)minishell$(RESET)]\n"
	@rm -rf $(OBJ_DIR)
	@printf "$(RED)removed subdir $(OBJ_DIR)$(RESET)\n"

# Clean test objects and tester
.PHONY: tclean
tclean:
	@rm -rf $(TEST_DIR)/*.o
	@printf "$(RED)removed .o files in subdir $(TEST_DIR)$(RESET)\n"
	@rm -rf $(TEST)
	@printf "$(RED)clean bin $(TEST)$(RESET)\n"

.PHONY: fclean
fclean: clean tclean
	@rm -rf $(NAME)
	@printf "$(RED)clean bin $(NAME)$(RESET)\n"
	@printf "$(YELLOW)$(BOLD)clean$(RESET) [$(BLUE)libft$(RESET)]\n"
	@$(MAKE) --no-print-directory -C $(LIB_DIR_FT) fclean

# ******************************
# *     Recompilation          *
# ******************************

.PHONY: re
re: fclean all

# ******************************
# *     Various                *
# ******************************

# Include the dependency files that exist. Use wildcard to avoid failing on non-existent files.
# Needs to be last target
include $(wildcard $(DEPFILES))
