/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_map2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:07:41 by lbolens           #+#    #+#             */
/*   Updated: 2025/12/17 14:00:00 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_map_width(char **map)
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

int	find_map_start(char **file)
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

static int	count_map_size(char **file, int start_index)
{
	int	i;
	int	map_size;

	map_size = 0;
	i = start_index;
	while (file[i])
	{
		map_size++;
		i++;
	}
	return (map_size);
}

static char	**fill_map(char **file, char **map, int start_index)
{
	int	i;
	int	j;

	i = start_index;
	j = 0;
	while (file[i])
	{
		map[j] = ft_strdup(file[i]);
		if (!map[j])
			return (free_map_array(map), NULL);
		i++;
		j++;
	}
	map[j] = NULL;
	return (map);
}

char	**extract_map(char **file, int start_index)
{
	char	**map;
	int		map_size;

	map_size = count_map_size(file, start_index);
	map = malloc((map_size + 1) * sizeof(char *));
	if (!map)
		return (ft_putstr_fd("Error\nCouldn't malloc map\n", 2), NULL);
	return (fill_map(file, map, start_index));
}
