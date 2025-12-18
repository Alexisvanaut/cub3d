/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:14:01 by lbolens           #+#    #+#             */
/*   Updated: 2025/12/17 14:00:00 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static char	**duplicate_map(char **map, int height)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static bool	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static bool	is_out_of_bounds(char **map, int x, int y, t_data *data)
{
	int	len;

	if (y < 0 || y >= data->map_height)
		return (true);
	len = ft_strlen(map[y]);
	if (len > 0 && map[y][len - 1] == '\n')
		len--;
	if (x < 0 || x >= len)
		return (true);
	if (map[y][x] == ' ')
		return (true);
	return (false);
}

static bool	fill(char **map, int x, int y, t_data *data)
{
	if (is_out_of_bounds(map, x, y, data))
		return (false);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (true);
	if (!is_walkable(map[y][x]))
		return (false);
	map[y][x] = 'V';
	if (!fill(map, x + 1, y, data))
		return (false);
	if (!fill(map, x - 1, y, data))
		return (false);
	if (!fill(map, x, y + 1, data))
		return (false);
	if (!fill(map, x, y - 1, data))
		return (false);
	return (true);
}

bool	flood_fill(t_data *data)
{
	char	**map_copy;
	bool	result;

	map_copy = duplicate_map(data->map, data->map_height);
	if (!map_copy)
		return (ft_putstr_fd("Error\nMalloc failed in flood_fill\n", 2), false);
	result = fill(map_copy, data->player_x, data->player_y, data);
	free_map_array(map_copy);
	if (!result)
		ft_putstr_fd("Error\nMap is not closed (flood fill failed)\n", 2);
	return (result);
}
