/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_color_parse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajossera <ajossera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:57:33 by ajossera          #+#    #+#             */
/*   Updated: 2022/05/10 13:58:16 by ajossera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	*ft_add_to_str(char *str, char c)
{
	char	*rend;
	int		i;

	i = -1;
	if (!str)
		return (NULL);
	rend = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!rend && !ft_error("Malloc error\n"))
	{
		free(str);
		return (NULL);
	}
	while (str[++i])
	{
		rend[i] = str[i];
	}
	rend[i] = c;
	rend[i + 1] = '\0';
	if (str)
		free(str);
	str = NULL;
	return (rend);
}

int	ft_second_file_parse(char c, int fd, char **ret_fd)
{
	int		error;

	*ret_fd = malloc(sizeof(char) * 2);
	if (!(*ret_fd))
		return (ft_error("Malloc error\n"));
	ret_fd[0][0] = c;
	ret_fd[0][1] = '\0';
	while (1)
	{
		error = read(fd, &c, 1);
		if (error <= 0)
			return (ft_error("No map in the file\n"));
		if (c == '\n')
			break ;
		*ret_fd = ft_add_to_str(*ret_fd, c);
		if (!(*ret_fd))
			return (0);
	}
	return (1);
}

int	ft_file_parse(char err, char search, char **ret_fd, int fd)
{
	int		error;
	char	c;

	if (*ret_fd)
		return (ft_error("Two same parameters\n"));
	error = read(fd, &c, 1);
	if (error <= 0 || c != search)
		return (ft_error("Incorrect second letter with ")
			+ ft_putc(err) + ft_put(" caracter\n"));
	c = ft_mute_char(fd, ' ', 1);
	if (c == 0)
		return (ft_error("No space or invalid read with ")
			+ ft_putc(err) + ft_put(" type\n"));
	if (c == '\n')
		return (ft_error("No file after ") + ft_putc(err) + ft_put(" type\n"));
	return (ft_second_file_parse(c, fd, ret_fd));
}

int	ft_init_color(int **color)
{
	*color = malloc(sizeof(int) * 3);
	if (!color)
		return (ft_error("Malloc error\n"));
	color[0][0] = 0;
	color[0][1] = 0;
	color[0][2] = 0;
	return (1);
}

int	ft_color_parse(char err, int **color, int fd)
{
	char	c;
	int		i;

	if (ft_init_color(color) == 0)
		return (0);
	c = ft_mute_char(fd, ' ', 1);
	if (c == 0)
		return (ft_error("No space or invalid read with ")
			+ ft_putc(err) + ft_put(" type\n"));
	if (c == '\n')
		return (ft_error("No color after ") + ft_putc(err) + ft_put(" type\n"));
	i = -1;
	while (++i < 2)
	{
		if (ft_atoi(c, &(color[0][i]), fd, ',') == 0)
			return (ft_error("Incorrect type of number for the ")
				+ ft_putc(i + '1') + ft_put(" number of ")
				+ ft_putc(err) + ft_put(" color\n"));
		c = ft_mute_char(fd, ' ', 0);
	}
	if (ft_atoi(c, &(color[0][i]), fd, '\n') == 0)
		return (ft_error("Incorrect type of number for the 3 number of ")
			+ ft_putc(err) + ft_put(" color\n"));
	return (1);
}
