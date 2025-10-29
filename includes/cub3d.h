#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <unistd.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_data
{
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	int		floor_color[3];
	int		ceiling_color[3];
	char	**map;
	int		map_width;
	int		map_height;
	char	player_dir;
	int		player_x;
	int		player_y;
}			t_data;

// PARSING

char		**manage_file(char *file);
bool		get_textures(char **file, t_data *data);
bool		get_colors(char **file, t_data *data);
bool		get_map(t_data *data, char **file);
bool		parse_map(t_data *data, char **map);
bool		check_lines(char **map);
bool		check_rows(char **map);
bool		check_one_player(t_data *data, char **map);
bool		check_characters(char **map);
bool		check_zeros(char **map);
bool		flood_fill(t_data *data);

#endif
