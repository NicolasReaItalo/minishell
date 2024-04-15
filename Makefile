# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/11 15:58:40 by tjoyeux           #+#    #+#              #
#    Updated: 2024/04/15 09:30:31 by nrea             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#________________________________Variables___________________________________
NAME = minishell
LIBFT_PATH = ./libft/
LIBFT = $(LIBFT_PATH)libft.a
INCLUDE_PATH = ./include/

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -g3 -I$(INCLUDE_PATH) -I$(LIBFT_PATH) -I./test
LDFLAGS		= -L$(LIBFT_PATH) -lft -lreadline
RM			= rm -f

SRC_PATH	= ./srcs/
OBJ_PATH	= ./objs/
#SRCS		= $(wildcard $(SRC_PATH)*.c) $(wildcard $(SRC_PATH)parsing/*.c) $(wildcard $(SRC_PATH)execution/*.c) $(wildcard $(SRC_PATH)env_variables/*.c)  $(wildcard test/utils/*.c)
#OBJS		= $(SRC:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)
SRCS		=	$(SRC_PATH)minishell.c \
				$(SRC_PATH)minishell_utils.c\
				$(SRC_PATH)minishell_evaluate.c\
				$(SRC_PATH)minishell_repl.c\
				$(SRC_PATH)minishell_signals.c\
				$(SRC_PATH)minishell_signals_hd.c\
				$(SRC_PATH)parsing/token.c \
				$(SRC_PATH)parsing/token_utils.c \
				$(SRC_PATH)parsing/token_utils2.c \
				$(SRC_PATH)parsing/check_syntax.c \
				$(SRC_PATH)parsing/redirections.c \
				$(SRC_PATH)parsing/here_doc.c \
				$(SRC_PATH)parsing/check_outer_brackets.c \
				$(SRC_PATH)parsing/find_operator.c \
				$(SRC_PATH)parsing/strip_brackets.c \
				$(SRC_PATH)parsing/split_token_list.c \
				$(SRC_PATH)parsing/parse_tree.c \
				$(SRC_PATH)parsing/parse_tree_nodes.c \
				$(SRC_PATH)env_variables/env_var_exit_status.c \
				$(SRC_PATH)env_variables/env_var_fetch.c \
				$(SRC_PATH)env_variables/env_var_push.c \
				$(SRC_PATH)env_variables/env_var_op.c \
				$(SRC_PATH)env_variables/env_var_set_vars.c \
				$(SRC_PATH)env_variables/env_var_shell_vars_op.c\
				$(SRC_PATH)env_variables/env_var_utils.c\
				$(SRC_PATH)execution/pipe_operations.c\
				$(SRC_PATH)execution/redir_simple.c\
				$(SRC_PATH)execution/apply_redirs.c\
				$(SRC_PATH)execution/redir_here_doc.c\
				$(SRC_PATH)execution/exec_root.c\
				$(SRC_PATH)execution/exec_binary.c\
				$(SRC_PATH)execution/exec_pipe.c\
				$(SRC_PATH)execution/exec_utils.c\
				$(SRC_PATH)expansion/expansion.c \
				$(SRC_PATH)expansion/field_splitting.c \
				$(SRC_PATH)expansion/param_expansion.c \
				$(SRC_PATH)expansion/pathname_expansion.c\
				$(SRC_PATH)expansion/redir_expansion.c\
				$(SRC_PATH)expansion/redir_expansion_tools.c\
				$(SRC_PATH)expansion/unquotting.c\
				$(SRC_PATH)builtins/builtins.c\
				$(SRC_PATH)builtins/builtins_utils.c\
				$(SRC_PATH)builtins/pwd.c\
				$(SRC_PATH)builtins/echo.c\
				$(SRC_PATH)builtins/env.c\
				$(SRC_PATH)builtins/export.c\
				$(SRC_PATH)builtins/unset.c\
				$(SRC_PATH)builtins/cd.c\
				$(SRC_PATH)builtins/exit.c\
				test/utils/test_utils.c

OBJS		= $(addprefix $(OBJ_PATH),$(notdir $(SRCS:.c=.o)))

FLAG_FILE	:= .build_started
FLAG_BONUS	:= .build_started_bonus
BUILD_FLAG	:= .build_done
#________________________________Minishell___________________________________

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJS)
	@echo "$(GREEN)$(BOLD)$(ITALIC)$$LINKING$(RESET)\n"
	@echo "$(MAGENTA)$(BOLD)Linking Server: $(RESET)$(BLUE)$(ITALIC)$@$(RESET)"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

$(LIBFT) : $(LIBFT_PATH)/Makefile
	@echo "$(GREEN)$(BOLD)$(ITALIC)$$LIBFT_HEADER$(RESET)\n"
	@echo "$(MAGENTA)$(BOLD)Libft Construction: $(BLUE)$(ITALIC)$(LIBFT)$(RESET)"
	make -C $(LIBFT_PATH)
	@echo "$(RESET)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@if [ ! -f $(FLAG_FILE) ]; then touch $(FLAG_FILE); echo "$(GREEN)$(BOLD)$$COMPILATION$(RESET)"; fi
	@mkdir -p $(OBJ_PATH)
#	@echo "$$COMPILATION\n"
	@echo "$(MAGENTA)$(BOLD)Compilation: $(RESET)$(BLUE)$(ITALIC)$<$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@
	@touch $(BUILD_FLAG)

$(OBJ_PATH)%.o: $(SRC_PATH)parsing/%.c
	@if [ ! -f $(FLAG_FILE) ]; then touch $(FLAG_FILE); echo "$(GREEN)$(BOLD)$$COMPILATION$(RESET)"; fi
	@mkdir -p $(OBJ_PATH)
#	@echo "$$COMPILATION\n"
	@echo "$(MAGENTA)$(BOLD)Compilation: $(RESET)$(BLUE)$(ITALIC)$<$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@
	@touch $(BUILD_FLAG)

$(OBJ_PATH)%.o: $(SRC_PATH)execution/%.c
	@if [ ! -f $(FLAG_FILE) ]; then touch $(FLAG_FILE); echo "$(GREEN)$(BOLD)$$COMPILATION$(RESET)"; fi
	@mkdir -p $(OBJ_PATH)
#	@echo "$$COMPILATION\n"
	@echo "$(MAGENTA)$(BOLD)Compilation: $(RESET)$(BLUE)$(ITALIC)$<$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@
	@touch $(BUILD_FLAG)

$(OBJ_PATH)%.o: $(SRC_PATH)expansion/%.c
	@if [ ! -f $(FLAG_FILE) ]; then touch $(FLAG_FILE); echo "$(GREEN)$(BOLD)$$COMPILATION$(RESET)"; fi
	@mkdir -p $(OBJ_PATH)
#	@echo "$$COMPILATION\n"
	@echo "$(MAGENTA)$(BOLD)Compilation: $(RESET)$(BLUE)$(ITALIC)$<$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@
	@touch $(BUILD_FLAG)

$(OBJ_PATH)%.o: $(SRC_PATH)env_variables/%.c
	@if [ ! -f $(FLAG_FILE) ]; then touch $(FLAG_FILE); echo "$(GREEN)$(BOLD)$$COMPILATION$(RESET)"; fi
	@mkdir -p $(OBJ_PATH)
#	@echo "$$COMPILATION\n"
	@echo "$(MAGENTA)$(BOLD)Compilation: $(RESET)$(BLUE)$(ITALIC)$<$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@
	@touch $(BUILD_FLAG)

$(OBJ_PATH)%.o: $(SRC_PATH)builtins/%.c
	@if [ ! -f $(FLAG_FILE) ]; then touch $(FLAG_FILE); echo "$(GREEN)$(BOLD)$$COMPILATION$(RESET)"; fi
	@mkdir -p $(OBJ_PATH)
#	@echo "$$COMPILATION\n"
	@echo "$(MAGENTA)$(BOLD)Compilation: $(RESET)$(BLUE)$(ITALIC)$<$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@
	@touch $(BUILD_FLAG)

$(OBJ_PATH)%.o: test/utils/%.c
	@if [ ! -f $(FLAG_FILE) ]; then touch $(FLAG_FILE); echo "$(GREEN)$(BOLD)$$COMPILATION$(RESET)"; fi
	@mkdir -p $(OBJ_PATH)
#	@echo "$$COMPILATION\n"
	@echo "$(MAGENTA)$(BOLD)Compilation: $(RESET)$(BLUE)$(ITALIC)$<$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@
	@touch $(BUILD_FLAG)

#________________________________Cleaning____________________________________
clean :
	@echo "$(GREEN)$(BOLD)$$CLEANING$(RESET)"
	@echo "$(MAGENTA)$(BOLD)Cleaning: $(RESET)$(BLUE)$(ITALIC)$(OBJ)$(RESET)"
	$(RM) $(OBJ_PATH)*.o
	@echo "$(MAGENTA)$(BOLD)Cleaning: $(RESET)$(BLUE)$(ITALIC)$(FLAG_FILE)$(RESET)"
	$(RM) .build_started
	@echo "$(MAGENTA)$(BOLD)Cleaning: $(RESET)$(BLUE)$(ITALIC)$(MLX_PATH)*.o$(RESET)"
	make clean -C $(LIBFT_PATH)

fclean : clean
	@echo "$(MAGENTA)$(BOLD)Cleaning: $(RESET)$(BLUE)$(ITALIC)$(LIBFT)$(RESET)"
	make fclean -C $(LIBFT_PATH)
	@echo "$(MAGENTA)$(BOLD)Cleaning: $(RESET)$(BLUE)$(ITALIC)$(NAME)$(RESET)"
	$(RM) $(NAME)

re : fclean all

##debug :  push_swap.h
##	$(CC) $(CFLAGS) -c -I. -g3 -fsanitize=address $(SRC)

##debug_bonus :  push_swap.h
##	$(CC) $(CFLAGS) -c -I. -g3 -fsanitize=address $(SRC_BONUS)

.PHONY : all clean fclean re debug debug_bonus

#______________________________Presentation__________________________________
# Colors
RED := \033[0;31m
GREEN := \033[0;32m
BLUE := \033[0;34m
MAGENTA := \033[0;35m
RESET := \033[0m

# Style
BOLD := \033[1m
ITALIC := \033[3m
BLINK := \e[5m

define START


   ___| __ __|   \      _ \ __ __|
 \___ \    |    _ \    |   |   |
       |   |   ___ \   __ <    |
 _____/   _| _/    _\ _| \_\  _|



endef
export START

define LIBFT_HEADER


  |     _ _|  __ )   ____| __ __|
  |       |   __ \   |        |
  |       |   |   |  __|      |
 _____| ___| ____/  _|       _|


endef
export LIBFT_HEADER

define COMPILATION


   ___|   _ \    \  |   _ \ _ _|  |         \  __ __| _ _|   _ \    \  |
  |      |   |  |\/ |  |   |  |   |        _ \    |     |   |   |    \ |
  |      |   |  |   |  ___/   |   |       ___ \   |     |   |   |  |\  |
 \____| \___/  _|  _| _|    ___| _____| _/    _\ _|   ___| \___/  _| \_|



endef
export COMPILATION

define LINKING


  |     _ _|   \  |  |  / _ _|   \  |   ___|
  |       |     \ |  ' /    |     \ |  |
  |       |   |\  |  . \    |   |\  |  |   |
 _____| ___| _| \_| _|\_\ ___| _| \_| \____|


endef
export LINKING

define CLEANING


   ___|  |      ____|     \      \  | _ _|   \  |   ___|
  |      |      __|      _ \      \ |   |     \ |  |
  |      |      |       ___ \   |\  |   |   |\  |  |   |
 \____| _____| _____| _/    _\ _| \_| ___| _| \_| \____|

endef
export CLEANING
