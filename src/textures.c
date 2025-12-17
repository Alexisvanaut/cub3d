/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvanaut <alvanaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 00:00:00 by alvanaut          #+#    #+#             */
/*   Updated: 2025/11/26 00:00:00 by alvanaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	load_single_texture(t_data *data, t_img *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(data->mlx, path,
			&texture->width, &texture->height);
	if (!texture->img)
	{
		printf("Error: Failed to load texture: %s\n", path);
		return (false);
	}
	texture->addr = mlx_get_data_addr(texture->img,
			&texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	return (true);
}

static void	free_loaded_textures(t_data *data, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (data->textures[i].img)
		{
			mlx_destroy_image(data->mlx, data->textures[i].img);
			data->textures[i].img = NULL;
		}
		i++;
	}
}

bool	load_textures(t_data *data)
{
	if (!load_single_texture(data, &data->textures[0], data->north_texture))
		return (false);
	if (!load_single_texture(data, &data->textures[1], data->south_texture))
		return (free_loaded_textures(data, 1), false);
	if (!load_single_texture(data, &data->textures[2], data->west_texture))
		return (free_loaded_textures(data, 2), false);
	if (!load_single_texture(data, &data->textures[3], data->east_texture))
		return (free_loaded_textures(data, 3), false);
	return (true);
}

int	get_texture_color(t_img *texture, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	dst = texture->addr + (y * texture->line_length
			+ x * (texture->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}
