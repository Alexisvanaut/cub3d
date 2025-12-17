/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvanaut <alvanaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 00:00:00 by alvanaut          #+#    #+#             */
/*   Updated: 2025/11/26 00:00:00 by alvanaut         ###   ########.fr       */
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

static bool	parse_file(char *filename, t_data *data)
{
	char	**file;

	file = manage_file(filename);
	if (!file)
		return (false);
	if (!get_textures(file, data))
		return (free_file(file), false);
	if (!get_colors(file, data))
		return (free_file(file), false);
	if (!get_map(data, file))
		return (free_file(file), false);
	if (!parse_map(data, data->map))
		return (free_file(file), false);
	free_file(file);
	return (true);
}

static bool	init_game(t_data *data)
{
	if (!init_mlx(data))
		return (false);
	if (!load_textures(data))
	{
		cleanup(data);
		return (false);
	}
	init_player(data);
	return (true);
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	if (argc != 2)
	{
		printf("Error: usage: ./cub3D <map.cub>\n");
		return (1);
	}
	if (!parse_file(argv[1], &data))
		return (1);
	if (!init_game(&data))
		return (1);
	render_frame(&data);
	mlx_hook(data.win, 2, 1L << 0, handle_keypress, &data);
	mlx_hook(data.win, 17, 0, handle_close, &data);
	mlx_loop(data.mlx);
	return (0);
}
