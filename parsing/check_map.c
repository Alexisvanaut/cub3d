/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:23:50 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/27 13:29:29 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'N'
				&& map[i][j] != 'S' && map[i][j] != 'E' && map[i][j] != 'W'
				&& map[i][j] != ' ' && map[i][j] != '\n')
			{
				printf("Error: forbiden character found <%c>\n", map[i][j]);
				return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

bool	check_one_player(t_data *data, char **map)
{
	int		i;
	int		j;
	bool	already_checked;

	i = 0;
	already_checked = false;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
			{
				if (already_checked)
				{
					printf("Error: multiple players\n");
					return (false);
				}
				data->player_dir = map[i][j];
				data->player_x = j;
				data->player_y = i;
				already_checked = true;
			}
			j++;
		}
		i++;
	}
	if (!already_checked)
	{
		printf("Error: zero player found\n");
		return (false);
	}
	return (true);
}

bool	check_rows(char **map)
{
	int	i;
	int	last_row;

	last_row = 0;
	while (map[last_row])
		last_row++;
	last_row--;
	i = 0;
	while (map[0][i])
	{
		if (map[0][i] != '1' && map[0][i] != ' ' && map[0][i] != '\n')
		{
			printf("Error: first row must be walls or spaces\n");
			return (false);
		}
		i++;
	}
	i = 0;
	while (map[last_row][i])
	{
		if (map[last_row][i] != '1' && map[last_row][i] != ' '
			&& map[last_row][i] != '\n')
		{
			printf("Error: last row must be walls or spaces\n");
			return (false);
		}
		i++;
	}
	return (true);
}

bool	check_lines(char **map)
{
	int i;
	int len;

	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > 0 && map[i][len - 1] == '\n')
			len--;
		if (len > 0 && map[i][0] != '1' && map[i][0] != ' ')
		{
			printf("Error: first column must be walls or spaces\n");
			return (false);
		}
		if (len > 0 && map[i][len - 1] != '1' && map[i][len - 1] != ' ')
		{
			printf("Error: last column must be walls or spaces\n");
			return (false);
		}
		i++;
	}
	return (true);
}