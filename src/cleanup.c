/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvanaut <alvanaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 00:00:00 by alvanaut          #+#    #+#             */
/*   Updated: 2025/12/17 14:00:00 by alvanaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_textures_paths(t_data *data)
{
	if (data->north_texture)
	{
		free(data->north_texture);
		data->north_texture = NULL;
	}
	if (data->south_texture)
	{
		free(data->south_texture);
		data->south_texture = NULL;
	}
	if (data->west_texture)
	{
		free(data->west_texture);
		data->west_texture = NULL;
	}
	if (data->east_texture)
	{
		free(data->east_texture);
		data->east_texture = NULL;
	}
}

static void	free_texture_images(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data->textures[i].img)
		{
			mlx_destroy_image(data->mlx, data->textures[i].img);
			data->textures[i].img = NULL;
		}
		i++;
	}
}

void	free_map_array(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	cleanup(t_data *data)
{
	free_textures_paths(data);
	free_texture_images(data);
	free_map_array(data->map);
	data->map = NULL;
	if (data->img.img)
	{
		mlx_destroy_image(data->mlx, data->img.img);
		data->img.img = NULL;
	}
	if (data->win)
	{
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
	}
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		data->mlx = NULL;
	}
}
