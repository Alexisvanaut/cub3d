/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:07:41 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/27 13:27:28 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	get_map_width(char **map)
{
	int	i;
	int	max_width;
	int	current_width;

	max_width = 0;
	i = 0;
	while (map[i])
	{
		current_width = 0;
		while (map[i][current_width])
			current_width++;
		if (current_width > max_width)
			max_width = current_width;
		i++;
	}
	return (max_width);
}

int	get_map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

static void	free_partial_map(char **map, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static bool	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (false);
		i++;
	}
	return (true);
}

static char	**extract_map(char **file, int start_index)
{
	char	**map;
	int		i;
	int		j;
	int		map_size;

	map_size = 0;
	i = start_index;
	while (file[i])
	{
		map_size++;
		i++;
	}
	map = malloc((map_size + 1) * sizeof(char *));
	if (!map)
		return (printf("Error: couldn't malloc map\n"), NULL);
	i = start_index;
	j = 0;
	while (file[i])
	{
		map[j] = ft_strdup(file[i]);
		if (!map[j])
			return (free_partial_map(map, j), NULL);
		i++;
		j++;
	}
	map[j] = NULL;
	return (map);
}

static int	find_map_start(char **file)
{
	int	i;
	int	j;

	i = 0;
	while (file[i])
	{
		j = 0;
		while ((file[i][j] == ' ' || file[i][j] == '\t') && file[i][j])
			j++;
		if (file[i][j] == '0' || file[i][j] == '1')
			return (i);
		i++;
	}
	return (-1);
}

static bool	check_empty_lines(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (is_empty_line(map[i]))
			return (printf("Error: empty line in map\n"), false);
		i++;
	}
	return (true);
}

static void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

bool	get_map(t_data *data, char **file)
{
	int		start_index;
	char	**map;

	start_index = find_map_start(file);
	if (start_index == -1)
		return (printf("Error: no map in the file\n"), false);
	map = extract_map(file, start_index);
	if (!map)
		return (false);
	if (!check_empty_lines(map))
		return (free_map(map), false);
	data->map = map;
	data->map_height = get_map_height(map);
	data->map_width = get_map_width(map);
	return (true);
}
