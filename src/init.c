/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvanaut <alvanaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 00:00:00 by alvanaut          #+#    #+#             */
/*   Updated: 2025/12/17 14:00:00 by alvanaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (printf("Error\nMLX initialization failed\n"), false);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!data->win)
		return (printf("Error\nWindow creation failed\n"), false);
	data->img.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->img.img)
		return (printf("Error\nImage creation failed\n"), false);
	data->img.addr = mlx_get_data_addr(data->img.img,
			&data->img.bits_per_pixel, &data->img.line_length,
			&data->img.endian);
	data->img.width = WIN_WIDTH;
	data->img.height = WIN_HEIGHT;
	data->needs_render = true;
	return (true);
}

static void	set_direction_north_south(t_data *data)
{
	if (data->player_dir == 'N')
	{
		data->player.dir_x = 0;
		data->player.dir_y = -1;
		data->player.plane_x = FOV_PLANE;
		data->player.plane_y = 0;
	}
	else
	{
		data->player.dir_x = 0;
		data->player.dir_y = 1;
		data->player.plane_x = -FOV_PLANE;
		data->player.plane_y = 0;
	}
}

static void	set_direction_east_west(t_data *data)
{
	if (data->player_dir == 'E')
	{
		data->player.dir_x = 1;
		data->player.dir_y = 0;
		data->player.plane_x = 0;
		data->player.plane_y = FOV_PLANE;
	}
	else
	{
		data->player.dir_x = -1;
		data->player.dir_y = 0;
		data->player.plane_x = 0;
		data->player.plane_y = -FOV_PLANE;
	}
}

void	init_player(t_data *data)
{
	data->player.pos_x = (double)data->player_x + 0.5;
	data->player.pos_y = (double)data->player_y + 0.5;
	if (data->player_dir == 'N' || data->player_dir == 'S')
		set_direction_north_south(data);
	else
		set_direction_east_west(data);
}
