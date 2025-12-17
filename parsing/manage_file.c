/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:40:50 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/27 13:27:27 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	check_file_syntax(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len < 5)
	{
		printf("Error: filename too short\n");
		return (false);
	}
	if (ft_strcmp(&str[len - 4], ".cub") != 0)
	{
		printf("Error: file must end with .cub\n");
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
	while ((line = get_next_line(fd)) != NULL)
	{
		free(line);
		file_size++;
	}
	close(fd);
	return (file_size);
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
	_file = malloc((map_size + 1) * sizeof(char *));
	if (!_file)
	{
		close(fd);
		return (NULL);
	}
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
		_file[i++] = line;
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
		printf("Error: couldn't import file.\n");
		return (NULL);
	}
	return (_file);
}
