# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alvanaut <alvanaut@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/26 00:00:00 by alvanaut          #+#    #+#              #
#    Updated: 2025/12/17 14:00:00 by alvanaut         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

# Directories
SRCDIR		= src
PARSEDIR	= parsing
OBJDIR		= obj
INCDIR		= includes

# Colors
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
RED			= \033[0;31m
NC			= \033[0m

# Source files
SRC_FILES	= main.c init.c textures.c raycasting.c render.c controls.c cleanup.c
PARSE_FILES	= check_map.c check_zeros.c flood_fill.c manage_colors.c \
			  manage_file.c manage_map.c manage_texture.c parse_map.c

SRCS		= $(addprefix $(SRCDIR)/, $(SRC_FILES)) \
			  $(addprefix $(PARSEDIR)/, $(PARSE_FILES))

OBJS		= $(SRCS:%.c=$(OBJDIR)/%.o)
DEPS		= $(OBJS:.o=.d)

# Libraries
LIBFT		= libft/libft.a
MLX			= minilibx-linux/libmlx.a

# Compiler and flags
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -I$(INCDIR) -I./libft -I./minilibx-linux -MMD -MP
MLXFLAGS	= -L./minilibx-linux -lmlx -lXext -lX11
LDFLAGS		= -lm -no-pie

# Rules
all: $(NAME)
	@echo "$(GREEN)✓ cub3D compiled successfully!$(NC)"

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@echo "$(YELLOW)Linking $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLXFLAGS) $(LDFLAGS) -o $(NAME)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@echo "$(YELLOW)Building libft...$(NC)"
	@make -C libft --no-print-directory

$(MLX):
	@echo "$(YELLOW)Building minilibx...$(NC)"
	@make -C minilibx-linux --no-print-directory

clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@rm -rf $(OBJDIR)
	@make -C libft clean --no-print-directory
	@-make -C minilibx-linux clean 2>/dev/null || true

fclean: clean
	@echo "$(RED)Cleaning executables...$(NC)"
	@rm -f $(NAME)
	@make -C libft fclean --no-print-directory

re: fclean all

# Include dependencies
-include $(DEPS)

.PHONY: all clean fclean re
