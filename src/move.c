/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvanaut < alvanaut@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:12:08 by alvanaut          #+#    #+#             */
/*   Updated: 2025/12/18 15:12:10 by alvanaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move_forward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x + data->player.dir_x * MOVE_SPEED;
	new_y = data->player.pos_y + data->player.dir_y * MOVE_SPEED;
	if (is_valid_move(data, new_x, data->player.pos_y))
		data->player.pos_x = new_x;
	if (is_valid_move(data, data->player.pos_x, new_y))
		data->player.pos_y = new_y;
	data->needs_render = true;
}

void	move_backward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x - data->player.dir_x * MOVE_SPEED;
	new_y = data->player.pos_y - data->player.dir_y * MOVE_SPEED;
	if (is_valid_move(data, new_x, data->player.pos_y))
		data->player.pos_x = new_x;
	if (is_valid_move(data, data->player.pos_x, new_y))
		data->player.pos_y = new_y;
	data->needs_render = true;
}

void	move_strafe(t_data *data, int direction)
{
	double	new_x;
	double	new_y;

	if (direction == KEY_A)
	{
		new_x = data->player.pos_x - data->player.plane_x * MOVE_SPEED;
		new_y = data->player.pos_y - data->player.plane_y * MOVE_SPEED;
	}
	else
	{
		new_x = data->player.pos_x + data->player.plane_x * MOVE_SPEED;
		new_y = data->player.pos_y + data->player.plane_y * MOVE_SPEED;
	}
	if (is_valid_move(data, new_x, data->player.pos_y))
		data->player.pos_x = new_x;
	if (is_valid_move(data, data->player.pos_x, new_y))
		data->player.pos_y = new_y;
	data->needs_render = true;
}

void	rotate_player(t_data *data, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(angle)
		- data->player.dir_y * sin(angle);
	data->player.dir_y = old_dir_x * sin(angle)
		+ data->player.dir_y * cos(angle);
	old_plane_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(angle)
		- data->player.plane_y * sin(angle);
	data->player.plane_y = old_plane_x * sin(angle)
		+ data->player.plane_y * cos(angle);
	data->needs_render = true;
}
