/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajossera <ajossera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:53:49 by ajossera          #+#    #+#             */
/*   Updated: 2022/05/10 13:55:50 by ajossera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_write_pstr(char **pstr)
{
	int	i;

	i = -1;
	while (pstr[++i])
		printf("%s\n", pstr[i]);
	return (0);
}

void	ft_write_map(t_map *map)
{
	printf("N : %s\n", map->nofd);
	printf("S : %s\n", map->sofd);
	printf("E : %s\n", map->eafd);
	printf("W : %s\n\n", map->wefd);
	printf("Couleur sol : %d %d %d\n", map->f[0], map->f[1], map->f[2]);
	printf("Couleur plafond : %d %d %d\n\n", map->c[0], map->c[1], map->c[2]);
}

int	ft_putc(char a)
{
	int i = write(1, &a, 1);
	return (i - i);
}

int	ft_put(char *str)
{
	int i = write(2, str, ft_strlen(str));
	return (i - i);
}

int	ft_putnb(int nb)
{
	int	i;
	int	x;

	x = 0;
	i = 1000000000;
	if (!nb)
		return (ft_putc('0'));
	while (i != 0)
	{
		if ((nb / i) >= 1)
		{
			x = 1;
			ft_putc('0' + (nb / i));
			nb -= (nb / i) * i;
		}
		else if (x)
			ft_putc('0');
		i /= 10;
	}
	return (0);
}
