/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_map2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:07:41 by lbolens           #+#    #+#             */
/*   Updated: 2026/01/12 16:31:19 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	is_valid_header_line(char *line)
{
	char	*trimmed;

	trimmed = line;
	while (*trimmed == ' ' || *trimmed == '\t')
		trimmed++;
	if (*trimmed == '\n' || *trimmed == '\0')
		return (true);
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
		return (true);
	if (ft_strncmp(trimmed, "SO ", 3) == 0)
		return (true);
	if (ft_strncmp(trimmed, "WE ", 3) == 0)
		return (true);
	if (ft_strncmp(trimmed, "EA ", 3) == 0)
		return (true);
	if (ft_strncmp(trimmed, "F ", 2) == 0)
		return (true);
	if (ft_strncmp(trimmed, "C ", 2) == 0)
		return (true);
	return (false);
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
		if (!is_valid_header_line(file[i]))
		{
			ft_putstr_fd("Error\nInvalid content before map: ", 2);
			ft_putstr_fd(file[i], 2);
			return (-1);
		}
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
