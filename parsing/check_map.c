/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:23:50 by lbolens           #+#    #+#             */
/*   Updated: 2025/12/18 16:46:00 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	print_forbidden_char(char c)
{
	ft_putstr_fd("Error: forbiden character found <", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd(">\n", 2);
}

bool	check_characters(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!check_char_valid(map[i][j]))
			{
				print_forbidden_char(map[i][j]);
				return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

static bool	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static bool	handle_player_found(t_data *data, char **map, int i, int j)
{
	data->player_dir = map[i][j];
	data->player_x = j;
	data->player_y = i;
	return (true);
}

bool	check_one_player(t_data *data, char **map)
{
	int		i;
	int		j;
	bool	found;

	i = -1;
	found = false;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (is_player_char(map[i][j]))
			{
				if (found)
					return (ft_putstr_fd("Error: many players\n", 2), false);
				handle_player_found(data, map, i, j);
				found = true;
			}
		}
	}
	if (!found)
		return (ft_putstr_fd("Error: zero player found\n", 2), false);
	return (true);
}
