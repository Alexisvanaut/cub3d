/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:19:07 by lbolens           #+#    #+#             */
/*   Updated: 2025/12/17 14:00:00 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*skip_spaces(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}

static void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static bool	is_valid_number(char *str)
{
	int	i;

	if (!str || !*str)
		return (false);
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (!str[i])
		return (false);
	while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

static bool	validate_rgb_values(char **split, int *rgb)
{
	int	j;

	j = 0;
	while (j < 3)
	{
		if (!is_valid_number(split[j]))
			return (printf("Error\nInvalid RGB value\n"), false);
		rgb[j] = ft_atoi(split[j]);
		if (rgb[j] < 0 || rgb[j] > 255)
			return (printf("Error\nRGB must be [0,255]\n"), false);
		j++;
	}
	return (true);
}

static bool	extract_rgb(char *line, int *rgb)
{
	int		i;
	char	**split;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	split = ft_split(&line[i], ',');
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
	{
		free_split(split);
		return (printf("Error\nInvalid RGB format\n"), false);
	}
	if (!validate_rgb_values(split, rgb))
	{
		free_split(split);
		return (false);
	}
	free_split(split);
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

static bool	check_and_store_color(char *line, t_data *data,
		int *count, int index)
{
	int	*color;

	count[index]++;
	if (count[index] > 1)
		return (printf("Error\nColor defined multiple times\n"), false);
	if (index == 0)
		color = data->floor_color;
	else
		color = data->ceiling_color;
	if (!extract_rgb(line, color))
		return (false);
	return (true);
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
		return (printf("Error\nMissing color(s)\n"), false);
	return (true);
}
