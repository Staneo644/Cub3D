/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajossera <ajossera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:59:14 by ajossera          #+#    #+#             */
/*   Updated: 2022/05/10 14:00:03 by ajossera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_atoi(char firtst_nb, int *num, int fd, char delimited_char)
{
	int			error;
	char		c;

	if (firtst_nb > '9' || firtst_nb < '0')
		return (0);
	*num = firtst_nb - '0';
	while (1)
	{
		error = read(fd, &c, 1);
		if (error <= 0 || ((c < '0' || c > '9') && c != delimited_char))
			return (0);
		if (c == delimited_char)
			return (1);
		*num *= 10;
		*num += (c - '0');
		if (*num > 255)
			return (0);
	}
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_free(void *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
	return (0);
}

int	ft_error(char *str)
{
	write(2, "Error\n", 7);
	write(2, str, ft_strlen(str));
	return (0);
}

void	*ft_malloc(size_t x)
{
	x += x;
	return (NULL);
}
