/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajossera <ajossera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:10:41 by ajossera          #+#    #+#             */
/*   Updated: 2022/04/07 15:24:56 by ajossera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_strstr(char *a, char b)
{
	int	i;

	i = 0;
	while (a[i])
	{
		if (a[i] == b)
			return (i);
		i++;
	}
	return (-1);
}

static char	*ft_strjoin(char *a, char *b, int i, int j)
{
	char	*rend;

	while (a && a[i])
		i++;
	while (b && b[j])
		j++;
	rend = malloc(sizeof(char) * (i + j + 1));
	if (!rend)
		return (NULL);
	i = 0;
	while (a && a[i])
	{
		rend[i] = a[i];
		i++;
	}
	j = 0;
	while (b && b[j])
	{
		rend[i + j] = b[j];
		j++;
	}
	rend[i + j] = '\0';
	if (a)
		free(a);
	return (rend);
}

static int	ft_get_read(int fd, char **line, char **backup, int o)
{
	char	reading[BUFFER_SIZE + 1];

	*line = ft_strjoin(*line, *backup, 0, 0);
	while (ft_strstr(*line, '\n') == -1)
	{
		o = read(fd, reading, BUFFER_SIZE);
		if (o <= 0)
		{
			if (*backup)
				free(*backup);
			*backup = NULL;
			return (*line && (*line)[0] != '\0');
		}
		reading[o] = '\0';
		*line = ft_strjoin(*line, reading, 0, 0);
	}
	o = ft_strstr(*line, '\n');
	if (o >= 0)
	{
		free(*backup);
		*backup = ft_strjoin(NULL, &(*line)[o + 1], 0, 0);
		(*line)[o] = '\0';
	}
	return (1);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*backup[65536] = {0};

	line = NULL;
	if (fd >= 0 && fd < 65536 && BUFFER_SIZE >= 1
		&& !ft_get_read(fd, &line, &(backup[fd]), 0))
	{
		free (line);
		line = NULL;
	}
	return (line);
}
