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

static int	get_map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
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
			return (NULL);
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
		if (ft_isdigit(file[i][j]) || file[i][j] == '1')
			return (i);
		i++;
	}
	return (-1);
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
	data->map = map;
	data->map_height = get_map_height(map);
	data->map_width = get_map_width(map);
	return (true);
}
