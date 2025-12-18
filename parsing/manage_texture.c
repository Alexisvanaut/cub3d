/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:51:56 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/27 13:27:29 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_textures_data(t_data *data)
{
	data->north_texture = NULL;
	data->south_texture = NULL;
	data->west_texture = NULL;
	data->east_texture = NULL;
}

void	free_textures_data(t_data *data)
{
	if (data->north_texture)
		free(data->north_texture);
	if (data->south_texture)
		free(data->south_texture);
	if (data->west_texture)
		free(data->west_texture);
	if (data->east_texture)
		free(data->east_texture);
}

static int	parse_texture_line(char *line, t_data *data, int *count)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (check_and_store_texture(line, data, count, 0));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (check_and_store_texture(line, data, count, 1));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (check_and_store_texture(line, data, count, 2));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (check_and_store_texture(line, data, count, 3));
	return (1);
}

bool	get_textures(char **file, t_data *data)
{
	int		count[4];
	char	*line;
	int		i;

	count[0] = 0;
	count[1] = 0;
	count[2] = 0;
	count[3] = 0;
	init_textures_data(data);
	i = -1;
	while (file[++i])
	{
		line = skip_spaces(file[i]);
		if (!parse_texture_line(line, data, count))
			return (false);
	}
	if (count[0] != 1 || count[1] != 1 || count[2] != 1 || count[3] != 1)
		return (ft_putstr_fd("Error: missing texture(s)\n", 2),
			free_textures_data(data), false);
	if (!open_textures(data))
		return (free_textures_data(data), false);
	return (true);
}
