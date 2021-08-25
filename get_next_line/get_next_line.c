/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 16:00:50 by bbaudry           #+#    #+#             */
/*   Updated: 2020/03/12 23:30:43 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_checkbn(char *buffer)
{
	int	x;

	x = -1;
	while (buffer[++x])
		if (buffer[x] == '\n')
			return (1);
	return (0);
}

void	just_for_new_norme(char *buffer)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (buffer[x] != '\n')
		x++;
	while (buffer[++x])
		buffer[y++] = buffer[x];
	buffer[y] = '\0';
}

int	ft_read(int fd, char ***line, char *buffer)
{
	int	ret;

	ret = read(fd, buffer, BUFFER_SIZE);
	while (ret >= 0)
	{
		buffer[ret] = '\0';
		**line = ft_strjoin(**line, buffer, 2);
		if (!(**line))
			return (-1);
		if (ft_checkbn(buffer))
		{
			just_for_new_norme(buffer);
			return (1);
		}
		if (ret == 0)
			return (0);
		ret = read(fd, buffer, BUFFER_SIZE);
	}
	free(**line);
	return (-1);
}

int	get_next_line(int fd, char **line)
{
	static char	buffer[255][BUFFER_SIZE + 1];
	int			x;
	int			y;

	x = 0;
	y = 0;
	if (fd >= 0 && BUFFER_SIZE > 0)
	{
		*line = ft_strjoin(buffer[fd], "", 1);
		if (!(*line))
			return (-1);
		if (ft_checkbn(buffer[fd]))
		{
			while (buffer[fd][x] != '\n')
				x++;
			while (buffer[fd][++x])
				buffer[fd][y++] = buffer[fd][x];
			buffer[fd][y] = '\0';
			return (1);
		}
		return (ft_read(fd, &line, buffer[fd]));
	}
	return (-1);
}
