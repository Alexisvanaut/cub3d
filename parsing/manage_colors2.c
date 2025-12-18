/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_colors2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:19:07 by lbolens           #+#    #+#             */
/*   Updated: 2025/12/17 14:00:00 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	free_split_rgb(char **split)
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
			return (ft_putstr_fd("Error\nInvalid RGB value\n", 2), false);
		rgb[j] = ft_atoi(split[j]);
		if (rgb[j] < 0 || rgb[j] > 255)
			return (ft_putstr_fd("Error\nRGB must be [0,255]\n", 2), false);
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
		free_split_rgb(split);
		return (ft_putstr_fd("Error\nInvalid RGB format\n", 2), false);
	}
	if (!validate_rgb_values(split, rgb))
	{
		free_split_rgb(split);
		return (false);
	}
	free_split_rgb(split);
	return (true);
}

bool	check_and_store_color(char *line, t_data *data, int *count, int index)
{
	int	*color;

	count[index]++;
	if (count[index] > 1)
		return (ft_putstr_fd("Error\nColor defined multiple times\n", 2), false);
	if (index == 0)
		color = data->floor_color;
	else
		color = data->ceiling_color;
	if (!extract_rgb(line, color))
		return (false);
	return (true);
}
