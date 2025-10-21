/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvanaut <alvanaut@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:10:00 by alvanaut          #+#    #+#             */
/*   Updated: 2025/10/21 15:10:00 by alvanaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(void)
{
	t_data	data;

	ft_printf("\n🎮 === CUB3D - DEMO 2D ===\n\n");

	// Initialise les données de test
	if (init_mock_data(&data) == -1)
	{
		ft_printf("❌ Erreur: init mock data\n");
		return (1);
	}

	// Affiche la map dans le terminal
	print_mock_map(&data);

	// Initialise MLX et ouvre la fenêtre
	if (init_mlx(&data) == -1)
	{
		free_mock_data(&data);
		return (1);
	}

	// Lance la boucle infinie
	mlx_loop(data.mlx);

	return (0);
}
