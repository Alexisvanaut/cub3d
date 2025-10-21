/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvanaut <alvanaut@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:20:00 by alvanaut          #+#    #+#             */
/*   Updated: 2025/10/21 15:20:00 by alvanaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

// ============================================================================
// CONSTANTES
// ============================================================================

# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03

// Keycodes Linux
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

// ============================================================================
// STRUCTURES
// ============================================================================

/**
 * Structure pour une texture individuelle
 */
typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_texture;

/**
 * Structure pour toutes les textures du jeu
 */
typedef struct s_textures
{
	t_texture	north;
	t_texture	south;
	t_texture	east;
	t_texture	west;
	int			floor_color;
	int			ceiling_color;
}	t_textures;

/**
 * Structure du joueur (position, direction, plan caméra)
 */
typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

/**
 * Structure de la map
 */
typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

/**
 * Structure principale contenant toutes les données du jeu
 */
typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_map		map;
	t_player	player;
	t_textures	textures;
}	t_data;

// ============================================================================
// MOCK DATA (données de test - à supprimer plus tard)
// ============================================================================

int		init_mock_data(t_data *data);
int		init_mock_data_complex(t_data *data);
void	free_mock_data(t_data *data);
void	print_mock_map(t_data *data);

// ============================================================================
// PARSING (fait par ton coéquipier)
// ============================================================================

int		parse_file(char *filename, t_data *data);
void	free_parsing(t_data *data);

// ============================================================================
// MLX & EXECUTION
// ============================================================================

int		init_mlx(t_data *data);
int		game_loop(t_data *data);
int		close_window(void *param);
int		handle_keypress(int keycode, void *param);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	render_map_2d(t_data *data);

// ============================================================================
// RAYCASTING (à implémenter)
// ============================================================================

void	raycasting(t_data *data);

// ============================================================================
// CONTROLS (à implémenter)
// ============================================================================

void	move_forward(t_data *data);
void	move_backward(t_data *data);
void	rotate_left(t_data *data);
void	rotate_right(t_data *data);

// ============================================================================
// UTILS
// ============================================================================

int		create_rgb(int r, int g, int b);

#endif
