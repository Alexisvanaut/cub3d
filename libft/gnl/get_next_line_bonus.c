/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvanaut < alvanaut@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:27:51 by alvanaut          #+#    #+#             */
/*   Updated: 2025/09/09 13:28:47 by alvanaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static t_fd_data	*get_fd_data(int fd)
{
	static t_fd_data	data[OPEN_MAX];

	if (fd < 0 || fd >= OPEN_MAX)
		return (NULL);
	if (data[fd].fd != fd)
	{
		data[fd].fd = fd;
		data[fd].pos = 0;
		data[fd].len = 0;
	}
	return (&data[fd]);
}

static int	fill_buffer(t_fd_data *data)
{
	if (data->pos >= data->len)
	{
		data->len = read(data->fd, data->buffer, BUFFER_SIZE);
		if (data->len <= 0)
			return (0);
		data->pos = 0;
		data->buffer[data->len] = '\0';
	}
	return (1);
}

static char	*ft_substr(char *line, int start, int len)
{
	char	*str;
	int		i;

	if (!line || start < 0 || len <= 0)
		return (NULL);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && line[start + i])
	{
		str[i] = line[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*extract_line(t_fd_data *data)
{
	char	*line;
	int		start;
	int		end;

	start = data->pos;
	end = start;
	while (end < data->len && data->buffer[end] != '\n')
		end++;
	if (end < data->len && data->buffer[end] == '\n')
		end++;
	line = ft_substr(data->buffer, start, end - start);
	data->pos = end;
	return (line);
}

char	*get_next_line(int fd)
{
	t_fd_data	*data;
	char		*line;

	data = get_fd_data(fd);
	if (!data || !fill_buffer(data))
		return (NULL);
	line = extract_line(data);
	if (!line)
	{
		data->pos = data->len;
		return (NULL);
	}
	return (line);
}

/*int	main(int ac, char **av)
{
	char	*line;

	int fd1, fd2;
	(void)ac;
	fd1 = open(av[1], O_RDONLY);
	fd2 = open(av[2], O_RDONLY);
	if (fd1 < 0 || fd2 < 0)
		return (printf("Error ouverture du fichier\n"), 1);
	for (int i = 0; i < 5; i++)
	{
		line = get_next_line(fd1);
		printf("fd1: %s", line ? line : "NULL\n");
		if (line)
			free(line);
		line = get_next_line(fd2);
		printf("fd2: %s", line ? line : "NULL\n");
		if (line)
			free(line);
	}
	close(fd1);
	close(fd2);
	return (0);
}
*/
