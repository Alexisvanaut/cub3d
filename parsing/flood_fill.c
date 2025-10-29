/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:14:01 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/27 13:27:23 by lbolens          ###   ########.fr       */
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

static void	free_map_copy(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static bool	fill(char **map, int x, int y, t_data *data)
{
	int	len;

	if (y < 0 || y >= data->map_height)
		return (false);
	len = ft_strlen(map[y]);
	if (len > 0 && map[y][len - 1] == '\n')
		len--;
	if (x < 0 || x >= len)
		return (false);
	if (map[y][x] == ' ')
		return (false);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (true);
	if (map[y][x] != '0' && map[y][x] != 'N' && map[y][x] != 'S'
		&& map[y][x] != 'E' && map[y][x] != 'W')
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
		return (printf("Error: malloc failed in flood_fill\n"), false);
	result = fill(map_copy, data->player_x, data->player_y, data);
	free_map_copy(map_copy);
	if (!result)
		printf("Error: map is not closed (flood fill failed)\n");
	return (result);
}
