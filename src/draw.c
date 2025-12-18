/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasbolens <lucasbolens@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:08:06 by alvanaut          #+#    #+#             */
/*   Updated: 2025/12/18 16:35:41 by lucasbolens      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_tex_vars(t_data *data, t_ray *ray, double *vars, t_img **tex)
{
	*tex = &data->textures[get_wall_texture_index(ray)];
	calculate_texture_params(data, ray, (int *)&vars[0], *tex);
	vars[1] = 1.0 * (*tex)->height / ray->line_height;
	vars[2] = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2)
		* vars[1];
}

void	draw_textured_line(t_data *data, int x, t_ray *ray)
{
	int		y;
	double	vars[3];
	t_img	*texture;

	init_tex_vars(data, ray, vars, &texture);
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		my_mlx_pixel_put(&data->img, x, y, get_texture_color(texture,
				(int)vars[0], (int)vars[2] & (texture->height - 1)));
		vars[2] += vars[1];
		y++;
	}
}

void	draw_floor_ceiling(t_data *data, int x, int draw_start, int draw_end)
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
