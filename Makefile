# Text effects
RESET := \033[0m
BOLD := \033[1m
BLACK := \033[30m
GREEN := \033[32m
YELLOW := \033[33m
RED := \033[31m
BLUE := \033[34m

# Directories
SRC_DIR := src
OBJ_DIR := obj
LIB_DIR := lib
LIB_DIR_FT := $(LIB_DIR)/libft
INC_DIR := inc
DEP_DIR := $(OBJ_DIR)/dep
TEST_DIR := tests

# Libraries
LDFLAGS := -L $(LIB_DIR_FT)
LDLIBS := -l ft -l readline

# Compiling
CC := cc
CPPFLAGS := -I $(INC_DIR) -I lib/libft
CFLAGS = -Wall -Werror -Wextra -g -gdwarf-4
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEP_DIR)/$*.Td
COMPILE = $(CC) $(DEPFLAGS) $(CPPFLAGS) $(CFLAGS) -c
POSTCOMPILE = @mv -f $(DEP_DIR)/$*.Td $(DEP_DIR)/$*.d && touch $@

# Targets
NAME := minishell
LIBFT := $(LIB_DIR_FT)/libft.a
TEST := test

# Source files
SRC :=	main.c \
		ft_memory.c \
		ft_string.c \
		replace_token.c \
		hashtable_generate.c \
		hashtable_utils.c \
		hashtable_utils2.c \
		exit_failure.c \
		init.c \
		pwd.c \
		shlvl.c \
		prompt.c \
		prompt_replace_h.c \
		prompt_replace_u.c \
		prompt_replace_small.c \
		prompt_replace_w.c \
		lexer_utils.c \
		lexer_list.c \
		lexer_src.c \
		lexer_tok.c \
		lexer_tok_utils.c \
		lexer_check_syntax.c \
		utils.c \
		env_envp.c \
		expand_expr.c \
		expand_tilde.c \
		expand_var.c \
SRCS := $(addprefix $(SRC_DIR)/, $(SRC))

# Objects
OBJ := $(SRC:.c=.o)
OBJS := $(addprefix $(OBJ_DIR)/, $(OBJ))

# Dependencies
DEPFILES :=$(SRC:%.c=$(DEP_DIR)/%.d)

# Test
TEST_SRC := test_main.c \
			test_replace_token.c \
			test_prompt.c \
			test_hashtable.c \
			test_lexer.c \
			test_check_syntax.c \
			test_env_envp.c \
			test_expand_expr.c
TEST_SRCS := $(addprefix $(TEST_DIR)/, $(TEST_SRC))
TEST_OBJ := $(TEST_SRC:.c=.o)
TEST_OBJS := $(addprefix $(TEST_DIR)/, $(TEST_OBJ))

.PHONY: all
all: $(NAME)

# Linking the NAME target
$(NAME): $(LIBFT) $(OBJS)
	@printf "\n$(YELLOW)$(BOLD)link binary$(RESET) [$(BLUE)minishell$(RESET)]\n"
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $@
	@printf "\n$(YELLOW)$(BOLD)compilation successful$(RESET) [$(BLUE)minishell$(RESET)]\n"
	@printf "$(GREEN)$(NAME) created!$(RESET)\n"

# This target adds fsanitize leak checker to the flags. It needs to clean and recompile.
.PHONY: leak
leak: CFLAGS += -fsanitize=leak
leak: LDFLAGS += -fsanitize=leak
leak: clean $(NAME)
	@printf "Compiled with $(YELLOW)$(BOLD)fsanitize=leak$(RESET)\n\n"

# Create the binary tester, which has its own test_main. To avoid compile problems it sets the
# TESTING variable which renames "normal" main, and removes the main if it exists.
# After compiling it removes normal main again, making regular compilation of NAME target possible.
$(TEST): CFLAGS = -g -DTESTING -gdwarf-4
$(TEST): prep_test $(TEST_OBJS) $(OBJS)
	$(CC) $(LDFLAGS) $(TEST_OBJS) $(OBJS) $(LDLIBS) -o $@
	rm -f obj/main.o
	@printf "$(GREEN)Starting test!$(RESET)\n"

# To ensure "normal" main is compiled with flag TESTING it gets removed.
.PHONY: prep_test
prep_test:
	rm -f obj/main.o

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

# Use Makefile of libft to compile the library.
$(LIBFT):
	@printf "$(YELLOW)$(BOLD)compilation$(RESET) [$(BLUE)libft$(RESET)]\n"
	$(MAKE) -s -C $(LIB_DIR)/libft

.PHONY: clean
clean:
	@printf "$(YELLOW)$(BOLD)clean$(RESET) [$(BLUE)minishell$(RESET)]\n"
	@rm -rf $(OBJ_DIR)
	@printf "$(RED)removed subdir $(OBJ_DIR)$(RESET)\n"

.PHONY: fclean
fclean: clean
	@rm -rf $(NAME)
	@printf "$(RED)clean bin $(NAME)$(RESET)\n"
	@printf "$(YELLOW)$(BOLD)clean$(RESET) [$(BLUE)libft$(RESET)]\n"
	@$(MAKE) --no-print-directory -C $(LIB_DIR_FT) fclean

# Clean test objects and tester
.PHONY: tclean
tclean:
	@printf "$(YELLOW)$(BOLD)clean test files$(RESET) [$(BLUE)minishell$(RESET)]\n"
	@rm -rf $(TEST_DIR)/*.o
	@printf "$(RED)removed .o files in subdir $(TEST_DIR)$(RESET)\n"
	@rm -rf $(TEST)
	@printf "$(RED)clean bin $(TEST)$(RESET)\n"

.PHONY: re
re: fclean all

# Include the dependency files that exist. Use wildcard to avoid failing on non-existent files.
include $(wildcard $(DEPFILES))

# Perform memory check on leaks
.PHONY: valgr
valgr:
	@valgrind --leak-check=full\
			--show-leak-kinds=all\
			--trace-children=no\
			--track-fds=no\
			--log-file=valgrind-out.txt\
			./test
	@less ./valgrind-out.txt
