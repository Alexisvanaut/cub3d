/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:19:07 by lbolens           #+#    #+#             */
/*   Updated: 2026/01/12 16:31:14 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*skip_spaces(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}

static void	init_colors_data(t_data *data)
{
	data->floor_color[0] = -1;
	data->floor_color[1] = -1;
	data->floor_color[2] = -1;
	data->ceiling_color[0] = -1;
	data->ceiling_color[1] = -1;
	data->ceiling_color[2] = -1;
}

static bool	parse_color_line(char *line, t_data *data, int *count)
{
	if (ft_strncmp(line, "F ", 2) == 0)
		return (check_and_store_color(line, data, count, 0));
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (check_and_store_color(line, data, count, 1));
	return (true);
}

bool	get_colors(char **file, t_data *data)
{
	int		count[2];
	char	*line;
	int		i;

	count[0] = 0;
	count[1] = 0;
	init_colors_data(data);
	i = -1;
	while (file[++i])
	{
		line = skip_spaces(file[i]);
		if (!parse_color_line(line, data, count))
			return (false);
	}
	if (count[0] != 1 || count[1] != 1)
		return (ft_putstr_fd("Error\nMissing color(s)\n", 2), false);
	return (true);
}
