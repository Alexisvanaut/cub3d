/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_texture3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:43:41 by lbolens           #+#    #+#             */
/*   Updated: 2026/01/12 16:31:21 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*extract_path(char *line)
{
	int		i;
	int		j;
	int		k;
	char	*path;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	j = i;
	while (line[j] && line[j] != ' ' && line[j] != '\n' && line[j] != '\t')
		j++;
	path = malloc(sizeof(char) * (j - i + 1));
	if (!path)
		return (NULL);
	k = 0;
	while (i < j)
		path[k++] = line[i++];
	path[k] = '\0';
	return (path);
}
