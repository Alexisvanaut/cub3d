/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvanaut < alvanaut@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:08:06 by alvanaut          #+#    #+#             */
/*   Updated: 2025/12/18 15:08:08 by alvanaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_textured_line(t_data *data, int x, t_ray *ray)
{
	int		y;
	int		tex_x;
	int		tex_y;
	int		color;
	double	step;
	double	tex_pos;
	t_img	*texture;

	texture = &data->textures[get_wall_texture_index(ray)];
	calculate_texture_params(data, ray, &tex_x, texture);
	step = 1.0 * texture->height / ray->line_height;
	tex_pos = (ray->draw_start - WIN_HEIGHT / 2
			+ ray->line_height / 2) * step;
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

void	draw_floor_ceiling(t_data *data, int x,
		int draw_start, int draw_end)
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
		my_mlx_pixel_put(&data->img, x, y++, ceiling_color);
	y = draw_end;
	while (y < WIN_HEIGHT)
		my_mlx_pixel_put(&data->img, x, y++, floor_color);
}

void	draw_vertical_line(t_data *data, int x, t_ray *ray)
{
	draw_floor_ceiling(data, x, ray->draw_start, ray->draw_end);
	draw_textured_line(data, x, ray);
}
