/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvanaut <alvanaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 00:00:00 by alvanaut          #+#    #+#             */
/*   Updated: 2025/11/26 00:00:00 by alvanaut         ###   ########.fr       */
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

static bool	is_valid_pos(t_data *data, double x, double y)
{
	double	margin;

	margin = 0.2;
	if (is_wall(data, (int)(x - margin), (int)(y - margin)))
		return (false);
	if (is_wall(data, (int)(x + margin), (int)(y - margin)))
		return (false);
	if (is_wall(data, (int)(x - margin), (int)(y + margin)))
		return (false);
	if (is_wall(data, (int)(x + margin), (int)(y + margin)))
		return (false);
	return (true);
}

static void	move_forward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x + data->player.dir_x * MOVE_SPEED;
	new_y = data->player.pos_y + data->player.dir_y * MOVE_SPEED;
	if (is_valid_pos(data, new_x, data->player.pos_y))
		data->player.pos_x = new_x;
	if (is_valid_pos(data, data->player.pos_x, new_y))
		data->player.pos_y = new_y;
}

static void	move_backward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x - data->player.dir_x * MOVE_SPEED;
	new_y = data->player.pos_y - data->player.dir_y * MOVE_SPEED;
	if (is_valid_pos(data, new_x, data->player.pos_y))
		data->player.pos_x = new_x;
	if (is_valid_pos(data, data->player.pos_x, new_y))
		data->player.pos_y = new_y;
}

static void	move_left(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x - data->player.plane_x * MOVE_SPEED;
	new_y = data->player.pos_y - data->player.plane_y * MOVE_SPEED;
	if (is_valid_pos(data, new_x, data->player.pos_y))
		data->player.pos_x = new_x;
	if (is_valid_pos(data, data->player.pos_x, new_y))
		data->player.pos_y = new_y;
}

static void	move_right(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x + data->player.plane_x * MOVE_SPEED;
	new_y = data->player.pos_y + data->player.plane_y * MOVE_SPEED;
	if (is_valid_pos(data, new_x, data->player.pos_y))
		data->player.pos_x = new_x;
	if (is_valid_pos(data, data->player.pos_x, new_y))
		data->player.pos_y = new_y;
}

static void	rotate_left(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(ROT_SPEED)
		- data->player.dir_y * sin(ROT_SPEED);
	data->player.dir_y = old_dir_x * sin(ROT_SPEED)
		+ data->player.dir_y * cos(ROT_SPEED);
	old_plane_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(ROT_SPEED)
		- data->player.plane_y * sin(ROT_SPEED);
	data->player.plane_y = old_plane_x * sin(ROT_SPEED)
		+ data->player.plane_y * cos(ROT_SPEED);
}

static void	rotate_right(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(-ROT_SPEED)
		- data->player.dir_y * sin(-ROT_SPEED);
	data->player.dir_y = old_dir_x * sin(-ROT_SPEED)
		+ data->player.dir_y * cos(-ROT_SPEED);
	old_plane_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(-ROT_SPEED)
		- data->player.plane_y * sin(-ROT_SPEED);
	data->player.plane_y = old_plane_x * sin(-ROT_SPEED)
		+ data->player.plane_y * cos(-ROT_SPEED);
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
		move_left(data);
	else if (keycode == KEY_D)
		move_right(data);
	else if (keycode == KEY_LEFT)
		rotate_left(data);
	else if (keycode == KEY_RIGHT)
		rotate_right(data);
	render_frame(data);
	return (0);
}

int	handle_close(t_data *data)
{
	cleanup(data);
	exit(0);
	return (0);
}
