/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvanaut <alvanaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 00:00:00 by alvanaut          #+#    #+#             */
/*   Updated: 2025/11/26 00:00:00 by alvanaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static int	get_wall_texture_index(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			return (3);
		else
			return (2);
	}
	else
	{
		if (ray->step_y > 0)
			return (1);
		else
			return (0);
	}
}

static void	draw_textured_line(t_data *data, int x, t_ray *ray)
{
	int		y;
	int		tex_x;
	int		tex_y;
	int		color;
	double	wall_x;
	double	step;
	double	tex_pos;
	int		tex_index;
	t_img	*texture;

	tex_index = get_wall_texture_index(ray);
	texture = &data->textures[tex_index];
	if (ray->side == 0)
		wall_x = data->player.pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = data->player.pos_x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)texture->width);
	if ((ray->side == 0 && ray->dir_x > 0)
		|| (ray->side == 1 && ray->dir_y < 0))
		tex_x = texture->width - tex_x - 1;
	step = 1.0 * texture->height / ray->line_height;
	tex_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex_pos & (texture->height - 1);
		tex_pos += step;
		color = get_texture_color(texture, tex_x, tex_y);
		my_mlx_pixel_put(&data->img, x, y, color);
		y++;
	}
}

static void	draw_floor_ceiling(t_data *data, int x, int draw_start, int draw_end)
{
	int	y;
	int	ceiling_color;
	int	floor_color;

	ceiling_color = (data->ceiling_color[0] << 16)
		| (data->ceiling_color[1] << 8) | data->ceiling_color[2];
	floor_color = (data->floor_color[0] << 16)
		| (data->floor_color[1] << 8) | data->floor_color[2];
	y = 0;
	while (y < draw_start)
	{
		my_mlx_pixel_put(&data->img, x, y, ceiling_color);
		y++;
	}
	y = draw_end;
	while (y < WIN_HEIGHT)
	{
		my_mlx_pixel_put(&data->img, x, y, floor_color);
		y++;
	}
}

void	draw_vertical_line(t_data *data, int x, t_ray *ray)
{
	draw_floor_ceiling(data, x, ray->draw_start, ray->draw_end);
	draw_textured_line(data, x, ray);
}

void	render_frame(t_data *data)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIN_WIDTH)
	{
		ray.camera_x = x;
		perform_dda(data, &ray);
		draw_vertical_line(data, x, &ray);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}
