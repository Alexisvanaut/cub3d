/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:44:04 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/27 13:29:46 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	free_file(char **file)
{
	int	i;

	if (!file)
		return ;
	i = 0;
	while (file[i])
		free(file[i++]);
	free(file);
}

int	main(int argc, char **argv)
{
	t_data	data;
	char	**file;

	if (argc != 2)
	{
		printf("Error: usage: ./cub3D <map.cub>\n");
		return (1);
	}
	file = manage_file(argv[1]);
	if (!file)
		return (1);
	if (!get_textures(file, &data))
		return (free_file(file), 1);
	if (!get_colors(file, &data))
		return (free_file(file), 1);
	if (!get_map(&data, file))
		return (free_file(file), 1);
	if (!parse_map(&data, data.map))
		return (free_file(file), 1);
	free_file(file);
	return (0);
}
