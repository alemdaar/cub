/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddadi <ahaddadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 22:45:24 by ahaddadi          #+#    #+#             */
/*   Updated: 2024/12/27 17:54:49 by ahaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	costume_free(char **buffer)
{
	if (buffer && *buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
}

static char	*extract(char **line)
{
	int		i;
	char	*dst;
	char	*rest;

	i = 0;
	if (!line && !*line)
		return (NULL);
	while ((*line)[i] && (*line)[i] != '\n')
		i++;
	if ((*line)[i] == '\n')
		i++;
	dst = malloc(i + 1);
	if (!dst)
		return (NULL);
	cp2nl(&dst, line);
	rest = my_dup((*line) + i);
	if (!rest)
		return (costume_free(line), costume_free(&dst), NULL);
	costume_free(line);
	*line = rest;
	return (dst);
}

static char	*r2end(int fd, char **line)
{
	char	*temp;
	char	*buffer;
	int		r;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (costume_free(line), NULL);
	while (1)
	{
		r = read(fd, buffer, BUFFER_SIZE);
		if (r < 0)
			return (costume_free(&buffer), costume_free(line), NULL);
		buffer[r] = 0;
		temp = my_join(*line, buffer);
		if (!temp)
			return (costume_free(&buffer), costume_free(line), NULL);
		costume_free(line);
		*line = temp;
		if (my_strchr(*line, '\n') || r == 0)
			break ;
	}
	costume_free(&buffer);
	return (*line);
}

char	*get_next_line(int fd)
{
	static char	*all;
	char		*extra;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	all = r2end(fd, &all);
	if (!all)
		return (costume_free(&all), NULL);
	extra = extract(&all);
	if (!extra || my_strlen(extra) == 0)
		return (costume_free(&extra), costume_free(&all), NULL);
	return (extra);
}
