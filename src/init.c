/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvanaut <alvanaut@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 00:00:00 by alvanaut          #+#    #+#             */
/*   Updated: 2025/11/26 00:33:17 by alvanaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		printf("Error: MLX initialization failed\n");
		return (false);
	}
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!data->win)
	{
		printf("Error: Window creation failed\n");
		return (false);
	}
	data->img.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->img.img)
	{
		printf("Error: Image creation failed\n");
		return (false);
	}
	data->img.addr = mlx_get_data_addr(data->img.img,
			&data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	data->img.width = WIN_WIDTH;
	data->img.height = WIN_HEIGHT;
	return (true);
}

static void	set_player_direction(t_data *data)
{
	if (data->player_dir == 'N')
	{
		data->player.dir_x = 0;
		data->player.dir_y = -1;
		data->player.plane_x = 0.66;
		data->player.plane_y = 0;
	}
	else if (data->player_dir == 'S')
	{
		data->player.dir_x = 0;
		data->player.dir_y = 1;
		data->player.plane_x = -0.66;
		data->player.plane_y = 0;
	}
	else if (data->player_dir == 'E')
	{
		data->player.dir_x = 1;
		data->player.dir_y = 0;
		data->player.plane_x = 0;
		data->player.plane_y = 0.66;
	}
	else if (data->player_dir == 'W')
	{
		data->player.dir_x = -1;
		data->player.dir_y = 0;
		data->player.plane_x = 0;
		data->player.plane_y = -0.66;
	}
}

void	init_player(t_data *data)
{
	data->player.pos_x = (double)data->player_x + 0.5;
	data->player.pos_y = (double)data->player_y + 0.5;
	set_player_direction(data);
}
