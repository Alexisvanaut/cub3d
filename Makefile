# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: your_login <your_login@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/29 00:00:00 by your_login       #+#    #+#              #
#    Updated: 2025/10/29 00:00:00 by your_login      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

# Directories
SRC_DIR	= parsing
OBJ_DIR		= obj
INC_DIR		= includes
MLX_DIR		= minilibx-linux
LIBFT_DIR	= libft

# Compiler and flags
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3
INCLUDES	= -I$(INC_DIR) -I$(MLX_DIR) -I$(LIBFT_DIR)
LIBS		= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -L$(LIBFT_DIR) -lft

# Source files
SRC_SRCS = src/check_map.c \
			   src/check_zeros.c \
			   src/flood_fill.c \
			   src/main_parsing.c \
			   src/manage_colors.c \
			   src/manage_file.c \
			   src/manage_map.c \
			   src/manage_texture.c \
			   src/parse_map.c

# Object files
OBJS		= $(SRC_SRCS:%.c=$(OBJ_DIR)/%.o)

# Colors
GREEN		= \033[0;32m
RED			= \033[0;31m
RESET		= \033[0m

# Rules
all: $(MLX_DIR) $(LIBFT_DIR) $(NAME)

$(NAME): $(OBJS)
	@make -C $(MLX_DIR)
	@make -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)✓ cub3D compiled successfully!$(RESET)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(GREEN)Compiled: $<$(RESET)"

$(MLX_DIR):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "$(RED)Error: minilibx-linux directory not found!$(RESET)"; \
		echo "Please clone it with: git clone https://github.com/42Paris/minilibx-linux.git"; \
		exit 1; \
	fi

$(LIBFT_DIR):
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		echo "$(RED)Error: libft directory not found!$(RESET)"; \
		exit 1; \
	fi

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(MLX_DIR) 2>/dev/null || true
	@make clean -C $(LIBFT_DIR) 2>/dev/null || true
	@echo "$(RED)✓ Object files cleaned$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR) 2>/dev/null || true
	@echo "$(RED)✓ Executable removed$(RESET)"

re: fclean all

.PHONY: all clean fclean re
