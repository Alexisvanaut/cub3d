/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:39:29 by lbolens           #+#    #+#             */
/*   Updated: 2026/01/12 16:31:22 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	parse_map(t_data *data, char **map)
{
	if (!check_one_player(data, map))
		return (false);
	if (!check_characters(map))
		return (false);
	if (!check_rows(map))
		return (false);
	if (!check_lines(map))
		return (false);
	if (!flood_fill(data))
		return (false);
	return (true);
}
