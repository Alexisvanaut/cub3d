/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:23:50 by lbolens           #+#    #+#             */
/*   Updated: 2026/01/12 16:31:06 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	is_wall_or_space(char c)
{
	return (c == '1' || c == ' ');
}

static bool	check_first_row(char **map)
{
	int	i;
	int	len;

	len = ft_strlen(map[0]);
	if (len > 0 && map[0][len - 1] == '\n')
		len--;
	i = 0;
	while (i < len)
	{
		if (!is_wall_or_space(map[0][i]))
		{
			ft_putstr_fd("Error: first row must be walls or spaces\n", 2);
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	check_last_row(char **map, int last_row)
{
	int	i;
	int	len;

	len = ft_strlen(map[last_row]);
	if (len > 0 && map[last_row][len - 1] == '\n')
		len--;
	i = 0;
	while (i < len)
	{
		if (!is_wall_or_space(map[last_row][i]))
		{
			ft_putstr_fd("Error: last row must be walls or spaces\n", 2);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	check_rows(char **map)
{
	int	last_row;

	last_row = 0;
	while (map[last_row])
		last_row++;
	last_row--;
	if (!check_first_row(map))
		return (false);
	if (!check_last_row(map, last_row))
		return (false);
	return (true);
}

bool	check_lines(char **map)
{
	int	i;
	int	len;

	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > 0 && map[i][len - 1] == '\n')
			len--;
		if (len > 0 && map[i][0] != '1' && map[i][0] != ' ')
			return (ft_putstr_fd("Error: first column not walls or spaces\n",
					2), false);
		if (len > 0 && map[i][len - 1] != '1' && map[i][len - 1] != ' ')
			return (ft_putstr_fd("Error: last column must be walls or spaces\n",
					2), false);
		i++;
	}
	return (true);
}
