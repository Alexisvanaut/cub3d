/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvanaut <alvanaut@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:00:00 by alvanaut          #+#    #+#             */
/*   Updated: 2025/10/21 15:00:00 by alvanaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * Ferme proprement le programme
 * Appelé quand on clique sur la croix rouge ou qu'on appuie sur ESC
 */
int	close_window(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free_mock_data(data);
	ft_printf("👋 Cub3D fermé proprement\n");
	exit(0);
	return (0);
}

/**
 * Gère les touches du clavier
 */
int	handle_keypress(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	
	// ESC pour quitter
	if (keycode == 65307)
		close_window(data);
	
	// Touches de déplacement (à implémenter plus tard)
	if (keycode == 119)  // W
		ft_printf("W appuyé - Avancer\n");
	if (keycode == 115)  // S
		ft_printf("S appuyé - Reculer\n");
	if (keycode == 97)   // A
		ft_printf("A appuyé - Gauche\n");
	if (keycode == 100)  // D
		ft_printf("D appuyé - Droite\n");
	if (keycode == 65361) // Flèche gauche
		ft_printf("← Tourner gauche\n");
	if (keycode == 65363) // Flèche droite
		ft_printf("→ Tourner droite\n");
	
	return (0);
}

/**
 * Met un pixel dans l'image (plus rapide que mlx_pixel_put)
 */
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/**
 * Dessine un carré (pour afficher la map en 2D)
 */
void	draw_square(t_data *data, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_mlx_pixel_put(data, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

/**
 * Affiche la map en 2D vue du dessus (debug visuel)
 */
void	render_map_2d(t_data *data)
{
	int		x;
	int		y;
	int		tile_size;
	int		color;

	tile_size = 40;  // Taille d'une case en pixels
	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if (data->map.grid[y][x] == '1')
				color = 0xFFFFFF;  // Blanc pour les murs
			else
				color = 0x000000;  // Noir pour le vide
			draw_square(data, x * tile_size, y * tile_size, tile_size, color);
			x++;
		}
		y++;
	}
	
	// Dessiner le joueur en rouge
	draw_square(data, (int)(data->player.pos_x * tile_size) - 5,
		(int)(data->player.pos_y * tile_size) - 5, 10, 0xFF0000);
}

/**
 * Fonction appelée à chaque frame (boucle de rendu)
 */
int	game_loop(t_data *data)
{
	// Efface l'image précédente (fond noir)
	int i = 0;
	while (i < SCREEN_WIDTH * SCREEN_HEIGHT)
	{
		((unsigned int *)data->addr)[i] = 0x000000;
		i++;
	}

	// Dessine la map 2D (pour le moment)
	render_map_2d(data);

	// Affiche l'image à l'écran
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);

	return (0);
}

/**
 * Initialise MLX et crée la fenêtre
 */
int	init_mlx(t_data *data)
{
	// 1. Connexion MLX
	data->mlx = mlx_init();
	if (!data->mlx)
		return (ft_printf("❌ Erreur: mlx_init failed\n"), -1);

	// 2. Créer la fenêtre
	data->win = mlx_new_window(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	if (!data->win)
		return (ft_printf("❌ Erreur: mlx_new_window failed\n"), -1);

	// 3. Créer une image (buffer pour dessiner)
	data->img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!data->img)
		return (ft_printf("❌ Erreur: mlx_new_image failed\n"), -1);

	// 4. Récupérer l'adresse mémoire de l'image
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
		&data->line_length, &data->endian);

	// 5. Brancher les événements
	mlx_hook(data->win, 17, 0, close_window, data);           // Croix rouge
	mlx_hook(data->win, 2, 1L<<0, handle_keypress, data);     // Clavier
	mlx_loop_hook(data->mlx, game_loop, data);                // Boucle de rendu

	ft_printf("✅ MLX initialisé avec succès!\n");
	ft_printf("🎮 Utilise ESC pour quitter\n\n");

	return (0);
}
