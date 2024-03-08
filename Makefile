# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joyeux <joyeux@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/11 15:58:40 by tjoyeux           #+#    #+#              #
#    Updated: 2024/03/08 12:01:00 by tjoyeux          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#________________________________Variables___________________________________
NAME = minishell
#NAME_C = client
#NAME_BONUS_S = server_bonus
#NAME_BONUS_C = client_bonus
LIBFT_PATH = ./libft/
LIBFT = $(LIBFT_PATH)libft.a
INCLUDE_PATH = ./include/

CC		= gcc
CFLAGS		= -Wall -Werror -Wextra -g3
LDFLAGS		= -L$(LIBFT_PATH) -lft
RM		= rm -f

SRC_PATH	= ./srcs/
OBJ_PATH	= ./objs/
#BONUS_PATH	= ./bonus/

#COMMON_SRC	= $(filter-out $(SRC_PATH)main.c $(SRC_PATH)main_bonus.c, $(wildcard $(SRC_PATH)*.c))
#SRC		= $(COMMON_SRC) $(SRC_PATH)main.c
#SRC_BONUS	= $(COMMON_SRC) $(SRC_PATH)main_bonus.c
#OBJ		= $(SRC:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)
#OBJ_BONUS	= $(SRC_BONUS:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)
SRC_C				= $(SRC_PATH)client.c
SRC_S				= $(SRC_PATH)server.c
OBJ_C				= $(SRC_C:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)
OBJ_S				= $(SRC_S:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)
SRC_BONUS_C			= $(SRC_PATH)client_bonus.c
SRC_BONUS_S			= $(SRC_PATH)server_bonus.c
OBJ_BONUS_C			= $(SRC_BONUS_C:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)
OBJ_BONUS_S			= $(SRC_BONUS_S:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)

FLAG_FILE	:= .build_started
FLAG_BONUS	:= .build_started_bonus
BUILD_FLAG	:= .build_done
#________________________________Minitalk___________________________________

all : $(NAME_S) $(NAME_C)

$(NAME_S) : $(LIBFT) $(OBJ_S) minitalk.h
	@echo "$(GREEN)$(BOLD)$(ITALIC)$$LINKING$(RESET)\n"
	@echo "$(MAGENTA)$(BOLD)Linking Server: $(RESET)$(BLUE)$(ITALIC)$@$(RESET)"
	$(CC) $(CFLAGS) -o $(NAME_S) $(OBJ_S) $(LDFLAGS)

$(NAME_C) : $(LIBFT) $(OBJ_C) minitalk.h
	@echo "$(GREEN)$(BOLD)$(ITALIC)$$LINKING$(RESET)\n"
	@echo "$(MAGENTA)$(BOLD)Linking Client: $(RESET)$(BLUE)$(ITALIC)$@$(RESET)"
	$(CC) $(CFLAGS) -o $(NAME_C) $(OBJ_C) $(LDFLAGS)

# #_________________________________Bonus____________________________________

bonus : $(NAME_BONUS_C) $(NAME_BONUS_S)

$(NAME_BONUS_S) : $(LIBFT) $(OBJ_BONUS_S) minitalk.h
	@echo "$(GREEN)$(BOLD)$(ITALIC)$$LINKING$(RESET)\n"
	@echo "$(MAGENTA)$(BOLD)Linking Server Bonus: $(RESET)$(BLUE)$(ITALIC)$@$(RESET)"
	$(CC) $(CFLAGS) -o $(NAME_BONUS_S) $(OBJ_BONUS_S) $(LDFLAGS)

$(NAME_BONUS_C) : $(LIBFT) $(OBJ_BONUS_C) minitalk.h
	@echo "$(GREEN)$(BOLD)$(ITALIC)$$LINKING$(RESET)\n"
	@echo "$(MAGENTA)$(BOLD)Linking Client Bonus: $(RESET)$(BLUE)$(ITALIC)$@$(RESET)"
	$(CC) $(CFLAGS) -o $(NAME_BONUS_C) $(OBJ_BONUS_C) $(LDFLAGS)

# #____________________________Common operations_______________________________

$(LIBFT) : $(LIBFT_PATH)/Makefile
	@echo "$(GREEN)$(BOLD)$(ITALIC)$$LIBFT_HEADER$(RESET)\n"
	@echo "$(MAGENTA)$(BOLD)Libft Construction: $(BLUE)$(ITALIC)$(LIBFT)$(RESET)"
	make -C $(LIBFT_PATH)
	@echo "$(RESET)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@if [ ! -f $(FLAG_FILE) ]; then touch $(FLAG_FILE); echo "$(GREEN)$(BOLD)$$COMPILATION$(RESET)"; fi
	@mkdir -p $(@D)
#	@echo "$$COMPILATION\n"
	@echo "$(MAGENTA)$(BOLD)Compilation: $(RESET)$(BLUE)$(ITALIC)$<$(RESET)"
	$(CC) $(CFLAGS) -I. -c $< -o $@
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
	$(RM) $(NAME_C)
	$(RM) $(NAME_S)
	$(RM) $(NAME_BONUS_C)
	$(RM) $(NAME_BONUS_S)

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

define MLX_HEADER

 __   __  ___   __    _  ___   ___      ___   _______  __   __
|  |_|  ||   | |  |  | ||   | |   |    |   | |  _    ||  |_|  |
|       ||   | |   |_| ||   | |   |    |   | | |_|   ||       |
|       ||   | |       ||   | |   |    |   | |       ||       |
|       ||   | |  _    ||   | |   |___ |   | |  _   |  |     |
| ||_|| ||   | | | |   ||   | |       ||   | | |_|   ||   _   |
|_|   |_||___| |_|  |__||___| |_______||___| |_______||__| |__|



endef
export MLX_HEADER

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
