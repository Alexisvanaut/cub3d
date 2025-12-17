/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvanaut <alvanaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 00:00:00 by alvanaut          #+#    #+#             */
/*   Updated: 2025/12/17 14:00:00 by alvanaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	is_wall(t_data *data, int x, int y)
{
	if (x < 0 || x >= data->map_width)
		return (true);
	if (y < 0 || y >= data->map_height)
		return (true);
	if (data->map[y][x] == '1')
		return (true);
	return (false);
}

bool	is_valid_move(t_data *data, double new_x, double new_y)
{
	if (is_wall(data, (int)(new_x - COLLISION_MARGIN),
			(int)(new_y - COLLISION_MARGIN)))
		return (false);
	if (is_wall(data, (int)(new_x + COLLISION_MARGIN),
			(int)(new_y - COLLISION_MARGIN)))
		return (false);
	if (is_wall(data, (int)(new_x - COLLISION_MARGIN),
			(int)(new_y + COLLISION_MARGIN)))
		return (false);
	if (is_wall(data, (int)(new_x + COLLISION_MARGIN),
			(int)(new_y + COLLISION_MARGIN)))
		return (false);
	return (true);
}

static void	move_forward(t_data *data)
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

static void	move_backward(t_data *data)
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

static void	move_strafe(t_data *data, int direction)
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

static void	rotate_player(t_data *data, double angle)
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

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		handle_close(data);
	else if (keycode == KEY_W || keycode == KEY_UP)
		move_forward(data);
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		move_backward(data);
	else if (keycode == KEY_A)
		move_strafe(data, KEY_A);
	else if (keycode == KEY_D)
		move_strafe(data, KEY_D);
	else if (keycode == KEY_LEFT)
		rotate_player(data, -ROT_SPEED);
	else if (keycode == KEY_RIGHT)
		rotate_player(data, ROT_SPEED);
	if (data->needs_render)
	{
		render_frame(data);
		data->needs_render = false;
	}
	return (0);
}

int	handle_close(t_data *data)
{
	cleanup(data);
	exit(0);
	return (0);
}
