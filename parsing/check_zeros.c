/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_zeros.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:23:02 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/27 13:27:22 by lbolens          ###   ########.fr       */
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

static int	get_map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
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
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (!is_valid_neighbor(map, j + 1, i, map_height))
					return (printf("Error: 0 adjacent to space/border\n"),
						false);
				if (!is_valid_neighbor(map, j - 1, i, map_height))
					return (printf("Error: 0 adjacent to space/border\n"),
						false);
				if (!is_valid_neighbor(map, j, i + 1, map_height))
					return (printf("Error: 0 adjacent to space/border\n"),
						false);
				if (!is_valid_neighbor(map, j, i - 1, map_height))
					return (printf("Error: 0 adjacent to space/border\n"),
						false);
			}
			j++;
		}
		i++;
	}
	return (true);
}
