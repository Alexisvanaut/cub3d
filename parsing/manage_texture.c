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

static char	*skip_spaces(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}

static char	*extract_path(char *line)
{
	int		i;
	int		j;
	int		k;
	char	*path;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	j = i;
	while (line[j] && line[j] != ' ' && line[j] != '\n' && line[j] != '\t')
		j++;
	path = malloc(sizeof(char) * (j - i + 1));
	if (!path)
		return (NULL);
	k = 0;
	while (i < j)
		path[k++] = line[i++];
	path[k] = '\0';
	return (path);
}

static void	free_textures_data(t_data *data)
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

static void	init_textures_data(t_data *data)
{
	data->north_texture = NULL;
	data->south_texture = NULL;
	data->west_texture = NULL;
	data->east_texture = NULL;
}

static int	check_and_store_texture(char *line, t_data *data, int *count,
		int index)
{
	char	*path;

	count[index]++;
	if (count[index] > 1)
	{
		printf("Error: texture defined multiple times\n");
		free_textures_data(data);
		return (0);
	}
	path = extract_path(line);
	if (!path)
		return (0);
	if (index == 0)
		data->north_texture = path;
	else if (index == 1)
		data->south_texture = path;
	else if (index == 2)
		data->west_texture = path;
	else if (index == 3)
		data->east_texture = path;
	return (1);
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

static bool	open_textures(t_data *data)
{
	int	fd;

	fd = open(data->north_texture, O_RDONLY);
	if (fd < 0)
		return (printf("Error: couldn't open texture: %s\n",
				data->north_texture), false);
	close(fd);
	fd = open(data->south_texture, O_RDONLY);
	if (fd < 0)
		return (printf("Error: couldn't open texture: %s\n",
				data->south_texture), false);
	close(fd);
	fd = open(data->west_texture, O_RDONLY);
	if (fd < 0)
		return (printf("Error: couldn't open texture: %s\n",
				data->west_texture), false);
	close(fd);
	fd = open(data->east_texture, O_RDONLY);
	if (fd < 0)
		return (printf("Error: couldn't open texture: %s\n",
				data->east_texture), false);
	close(fd);
	return (true);
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
		return (printf("Error: missing texture(s)\n"), free_textures_data(data),
			false);
	if (!open_textures(data))
		return (free_textures_data(data), false);
	return (true);
}
