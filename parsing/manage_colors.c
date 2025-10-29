/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:19:07 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/27 13:27:26 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static char	*skip_spaces(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}

static bool	extract_rgb(char *line, int *rgb)
{
	int		i;
	int		j;
	char	**split;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	split = ft_split(&line[i], ',');
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
		return (printf("Error: invalid RGB format\n"), false);
	j = -1;
	while (++j < 3)
	{
		rgb[j] = ft_atoi(split[j]);
		if (rgb[j] < 0 || rgb[j] > 255)
			return (printf("Error: RGB value must be [0,255]\n"),
				free(split[j]), free(split), false);
		free(split[j]);
	}
	free(split);
	return (true);
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

static int	check_and_store_color(char *line, t_data *data, int *count,
		int index)
{
	int	*color;

	count[index]++;
	if (count[index] > 1)
		return (printf("Error: color defined multiple times\n"), 0);
	if (index == 0)
		color = data->floor_color;
	else
		color = data->ceiling_color;
	if (!extract_rgb(line, color))
		return (0);
	return (1);
}

static int	parse_color_line(char *line, t_data *data, int *count)
{
	if (ft_strncmp(line, "F ", 2) == 0)
		return (check_and_store_color(line, data, count, 0));
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (check_and_store_color(line, data, count, 1));
	return (1);
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
		return (printf("Error: missing color(s)\n"), false);
	return (true);
}
