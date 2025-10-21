#include "../includes/cub3d.h"

void my_mlx_pixel_put(t_info *info, int x, int y, int color) {
	char *dst;

	dst = info->addr + (y * info->line_length + x * (info->bits_per_pixel / 8));
   *(int *)dst = color;
}

void draw_square(t_info *info, int start_x, int start_y, int size, int color) {
	int x = start_x;
	int y = start_y;

	while (y < start_y + size) {
		while (x < start_x + size) {
			my_mlx_pixel_put(info, x, y, color);
			x++;
		}
		x = start_x;
		y++;
	}
}

int main(void) {
	t_vars vars;
	t_info img;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1080, 1080, "Cub3d");
	img.img = mlx_new_image(vars.mlx, 1080, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	draw_square(&img, 100, 100, 200, 0xFF0000);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_loop(vars.mlx);
	return 0;
}
