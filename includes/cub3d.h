/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvanaut < alvanaut@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:15:18 by alvanaut          #+#    #+#             */
/*   Updated: 2025/12/18 16:26:08 by alvanaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../libft/gnl/get_next_line.h"
# include "../minilibx-linux/mlx.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

// Window settings
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

// Movement settings
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05

// Collision settings
# define COLLISION_MARGIN 0.2

// FOV settings
# define FOV_PLANE 0.66

// Key codes (Linux)
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

// Image structure
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}			t_img;

// Player structure
typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}			t_player;

// Ray structure
typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}			t_ray;

// Main data structure
typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_img		textures[4];
	t_player	player;
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	int			floor_color[3];
	int			ceiling_color[3];
	char		**map;
	int			map_width;
	int			map_height;
	char		player_dir;
	int			player_x;
	int			player_y;
	bool		needs_render;
}				t_data;

typedef struct s_tex_draw
{
	double	step;
	double	tex_pos;
	int		tex_y;
	int		y;
}	t_tex_draw;

// PARSING - File management
char		**manage_file(char *file);

// PARSING - Textures
bool		get_textures(char **file, t_data *data);

// PARSING - Colors
bool		get_colors(char **file, t_data *data);

// PARSING - Map
bool		get_map(t_data *data, char **file);
bool		parse_map(t_data *data, char **map);
int			get_map_height(char **map);

// PARSING - Validation
char		*skip_spaces(char *str);
bool		check_lines(char **map);
bool		check_rows(char **map);
bool		check_one_player(t_data *data, char **map);
bool		check_characters(char **map);
bool		check_zeros(char **map);
bool		flood_fill(t_data *data);

// GRAPHICS - Init
bool		init_mlx(t_data *data);
void		init_player(t_data *data);

// GRAPHICS - Textures
bool		load_textures(t_data *data);
int			get_texture_color(t_img *texture, int x, int y);

// GRAPHICS - Raycasting
void		perform_dda(t_data *data, t_ray *ray);
void		init_ray(t_data *data, t_ray *ray, int x);

// GRAPHICS - Set steps
void		set_step_x(t_data *data, t_ray *ray);
void		set_step_y(t_data *data, t_ray *ray);

// GRAPHICS - Draw
void		draw_vertical_line(t_data *data, int x, t_ray *ray);
void		draw_textured_line(t_data *data, int x, t_ray *ray);
void		draw_floor_ceiling(t_data *data, int x,
				int draw_start, int draw_end);

// GRAPHICS - Render
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
void		draw_vertical_line(t_data *data, int x, t_ray *ray);
void		render_frame(t_data *data);
int			get_wall_texture_index(t_ray *ray);
void		calculate_texture_params(t_data *data, t_ray *ray,
				int *tex_x, t_img *texture);

// GRAPHICS - move
void		move_forward(t_data *data);
void		move_backward(t_data *data);
void		move_strafe(t_data *data, int direction);
void		rotate_player(t_data *data, double angle);

// GRAPHICS - Controls
int			handle_keypress(int keycode, t_data *data);
int			handle_close(t_data *data);
bool		is_valid_move(t_data *data, double new_x, double new_y);

// GRAPHICS - Cleanup
void		cleanup(t_data *data);
void		free_map_array(char **map);
void		free_textures_paths(t_data *data);

#endif
