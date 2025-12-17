/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_zeros.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:23:02 by lbolens           #+#    #+#             */
/*   Updated: 2025/12/17 14:00:00 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	is_valid_neighbor(char **map, int x, int y, int max_y)
{
	int	len;

	if (y < 0 || y >= max_y)
		return (false);
	len = ft_strlen(map[y]);
	if (len > 0 && map[y][len - 1] == '\n')
		len--;
	if (x < 0 || x >= len)
		return (false);
	if (map[y][x] == ' ')
		return (false);
	return (true);
}

static bool	is_walkable_tile(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static bool	check_tile_neighbors(char **map, int x, int y, int map_height)
{
	if (!is_valid_neighbor(map, x + 1, y, map_height))
		return (printf("Error\n0 adjacent to space/border\n"), false);
	if (!is_valid_neighbor(map, x - 1, y, map_height))
		return (printf("Error\n0 adjacent to space/border\n"), false);
	if (!is_valid_neighbor(map, x, y + 1, map_height))
		return (printf("Error\n0 adjacent to space/border\n"), false);
	if (!is_valid_neighbor(map, x, y - 1, map_height))
		return (printf("Error\n0 adjacent to space/border\n"), false);
	return (true);
}

bool	check_zeros(char **map)
{
	int	i;
	int	j;
	int	map_height;

	map_height = get_map_height(map);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] && map[i][j] != '\n')
		{
			if (is_walkable_tile(map[i][j]))
			{
				if (!check_tile_neighbors(map, j, i, map_height))
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}
