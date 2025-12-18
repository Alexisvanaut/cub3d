/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvanaut <alvanaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 00:00:00 by alvanaut          #+#    #+#             */
/*   Updated: 2025/12/17 14:00:00 by alvanaut         ###   ########.fr       */
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

int	get_wall_texture_index(t_ray *ray)
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

void	calculate_texture_params(t_data *data, t_ray *ray,
		int *tex_x, t_img *texture)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = data->player.pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = data->player.pos_x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	*tex_x = (int)(wall_x * (double)texture->width);
	if ((ray->side == 0 && ray->dir_x > 0)
		|| (ray->side == 1 && ray->dir_y < 0))
		*tex_x = texture->width - *tex_x - 1;
}

void	render_frame(t_data *data)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(data, &ray, x);
		perform_dda(data, &ray);
		draw_vertical_line(data, x, &ray);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}
