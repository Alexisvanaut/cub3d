/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:40:50 by lbolens           #+#    #+#             */
/*   Updated: 2025/12/17 14:00:00 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	check_file_syntax(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len < 5)
	{
		ft_putstr_fd("Error\nFilename too short\n", 2);
		return (false);
	}
	if (ft_strcmp(&str[len - 4], ".cub") != 0)
	{
		ft_putstr_fd("Error\nFile must end with .cub\n", 2);
		return (false);
	}
	return (true);
}

static size_t	get_map_size(char *file)
{
	int		fd;
	size_t	file_size;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	file_size = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		file_size++;
		line = get_next_line(fd);
	}
	close(fd);
	return (file_size);
}

static char	**allocate_file_array(int map_size)
{
	char	**file;

	file = malloc((map_size + 1) * sizeof(char *));
	if (!file)
		return (NULL);
	return (file);
}

static char	**read_file(char *file)
{
	int		fd;
	char	*line;
	char	**_file;
	int		i;
	int		map_size;

	map_size = get_map_size(file);
	if (map_size == 0)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	_file = allocate_file_array(map_size);
	if (!_file)
		return (close(fd), NULL);
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		_file[i++] = line;
		line = get_next_line(fd);
	}
	_file[i] = NULL;
	close(fd);
	return (_file);
}

char	**manage_file(char *file)
{
	char	**_file;

	if (!check_file_syntax(file))
		return (NULL);
	_file = read_file(file);
	if (!_file)
	{
		ft_putstr_fd("Error\nCouldn't import file\n", 2);
		return (NULL);
	}
	return (_file);
}
