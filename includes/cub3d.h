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

typedef struct s_info {
	char *img;
	void *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
}		t_info;

typedef struct s_vars {
	void *mlx;
	void *win;
}		t_vars;

#endif
