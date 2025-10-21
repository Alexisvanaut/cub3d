#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include <stdlib.h>
# include <sys/time.h>
# include "../libft/libft.h"

typedef struct s_player {
	double player_x;
	double player_y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;

}			t_player;

typedef struct s_data {
	void *win;
	void *mlx;
	void *addr;
	t_player player;
}			t_data;

#endif
