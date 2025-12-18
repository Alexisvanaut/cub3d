/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:07:41 by lbolens           #+#    #+#             */
/*   Updated: 2025/12/17 14:00:00 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
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

static bool	check_empty_lines(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (is_empty_line(map[i]))
			return (ft_putstr_fd("Error\nEmpty line in map\n", 2), false);
		i++;
	}
	return (true);
}

bool	get_map(t_data *data, char **file)
{
	int		start_index;
	char	**map;

	start_index = find_map_start(file);
	if (start_index == -1)
		return (ft_putstr_fd("Error\nNo map in the file\n", 2), false);
	map = extract_map(file, start_index);
	if (!map)
		return (false);
	if (!check_empty_lines(map))
		return (free_map_array(map), false);
	data->map = map;
	data->map_height = get_map_height(map);
	data->map_width = get_map_width(map);
	return (true);
}
