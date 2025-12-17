# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alvanaut <alvanaut@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/26 00:00:00 by alvanaut          #+#    #+#              #
#    Updated: 2025/11/26 00:00:00 by alvanaut         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

# Directories
SRCDIR		= src
PARSEDIR	= parsing
OBJDIR		= obj
INCDIR		= includes

# Source files
SRC_FILES	= main.c init.c textures.c raycasting.c render.c controls.c cleanup.c
PARSE_FILES	= check_map.c check_zeros.c flood_fill.c manage_colors.c \
			  manage_file.c manage_map.c manage_texture.c parse_map.c

SRCS		= $(addprefix $(SRCDIR)/, $(SRC_FILES)) \
			  $(addprefix $(PARSEDIR)/, $(PARSE_FILES))

OBJS		= $(SRCS:%.c=$(OBJDIR)/%.o)

# Libraries
LIBFT		= libft/libft.a
MLX			= minilibx-linux/libmlx.a

# Compiler and flags
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -I$(INCDIR) -I./libft -I./minilibx-linux
MLXFLAGS	= -L./minilibx-linux -lmlx -lXext -lX11
LDFLAGS		= -lm -no-pie

# Rules
all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLXFLAGS) $(LDFLAGS) -o $(NAME)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft

$(MLX):
	make -C minilibx-linux

clean:
	rm -rf $(OBJDIR)
	make -C libft clean
	-make -C minilibx-linux clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
