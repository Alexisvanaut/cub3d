/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_texture2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:51:56 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/27 13:27:29 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

static bool	check_xpm_extension(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4)
		return (false);
	if (ft_strcmp(&path[len - 4], ".xpm") != 0)
		return (false);
	return (true);
}

static void	store_texture_path(t_data *data, char *path, int index)
{
	if (index == 0)
		data->north_texture = path;
	else if (index == 1)
		data->south_texture = path;
	else if (index == 2)
		data->west_texture = path;
	else if (index == 3)
		data->east_texture = path;
}

int	check_and_store_texture(char *line, t_data *data, int *count, int index)
{
	char	*path;

	count[index]++;
	if (count[index] > 1)
	{
		ft_putstr_fd("Error: texture defined multiple times\n", 2);
		free_textures_data(data);
		return (0);
	}
	path = extract_path(line);
	if (!path)
		return (0);
	if (!check_xpm_extension(path))
	{
		ft_putstr_fd("Error: texture must be .xpm file: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		free(path);
		return (0);
	}
	store_texture_path(data, path, index);
	return (1);
}

static bool	print_texture_error(char *texture_path)
{
	ft_putstr_fd("Error: couldn't open texture: ", 2);
	ft_putstr_fd(texture_path, 2);
	ft_putstr_fd("\n", 2);
	return (false);
}

bool	open_textures(t_data *data)
{
	int	fd;

	fd = open(data->north_texture, O_RDONLY);
	if (fd < 0)
		return (print_texture_error(data->north_texture));
	close(fd);
	fd = open(data->south_texture, O_RDONLY);
	if (fd < 0)
		return (print_texture_error(data->south_texture));
	close(fd);
	fd = open(data->west_texture, O_RDONLY);
	if (fd < 0)
		return (print_texture_error(data->west_texture));
	close(fd);
	fd = open(data->east_texture, O_RDONLY);
	if (fd < 0)
		return (print_texture_error(data->east_texture));
	close(fd);
	return (true);
}
