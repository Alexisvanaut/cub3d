/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mock_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvanaut <alvanaut@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:30:00 by alvanaut          #+#    #+#             */
/*   Updated: 2025/10/21 15:30:00 by alvanaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	init_mock_data(t_data *data)
{
	char	**map;

	map = malloc(sizeof(char *) * 9);
	if (!map)
		return (-1);
	map[0] = ft_strdup("11111111");
	map[1] = ft_strdup("10000001");
	map[2] = ft_strdup("10000001");
	map[3] = ft_strdup("10000001");
	map[4] = ft_strdup("10000001");
	map[5] = ft_strdup("10000001");
	map[6] = ft_strdup("10000001");
	map[7] = ft_strdup("11111111");
	map[8] = NULL;
	data->map.grid = map;
	data->map.width = 8;
	data->map.height = 8;
	data->player.pos_x = 4.5;
	data->player.pos_y = 4.5;
	data->player.dir_x = 0.0;
	data->player.dir_y = -1.0;
	data->player.plane_x = 0.66;
	data->player.plane_y = 0.0;
	data->textures.floor_color = 0x808080;
	data->textures.ceiling_color = 0x87CEEB;
	return (0);
}

void	free_mock_data(t_data *data)
{
	int	i;

	if (data->map.grid)
	{
		i = 0;
		while (data->map.grid[i])
		{
			free(data->map.grid[i]);
			i++;
		}
		free(data->map.grid);
		data->map.grid = NULL;
	}
}

void	print_mock_map(t_data *data)
{
	int	y;
	int	x;

	ft_printf("\n=== MAP DEBUG ===\n");
	ft_printf("Size: %dx%d\n", data->map.width, data->map.height);
	ft_printf("Player pos: (%.2f, %.2f)\n", data->player.pos_x, 
		data->player.pos_y);
	ft_printf("Player dir: (%.2f, %.2f)\n\n", data->player.dir_x, 
		data->player.dir_y);
	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if ((int)data->player.pos_x == x && (int)data->player.pos_y == y)
				ft_printf("P");
			else
				ft_printf("%c", data->map.grid[y][x]);
			x++;
		}
		ft_printf("\n");
		y++;
	}
	ft_printf("\n=================\n\n");
}
