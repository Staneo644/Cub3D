/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:01:22 by tlafay            #+#    #+#             */
/*   Updated: 2022/04/20 11:24:26 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	digit_num(long n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	get_tab(int i, long s, char *ret)
{
	if (s < 0)
	{
		ret[0] = '-';
		s *= -1;
	}
	while (s > 0)
	{
		ret[i] = '0' + (s % 10);
		s /= 10;
		i--;
	}
}

char	*ft_itoa(long n)
{
	unsigned long	s;
	int				i;
	char			*ret;

	s = n;
	i = digit_num(n);
	ret = (char *)malloc((i + 1) * sizeof(char));
	if (!ret)
		exit(1);
	ret[i--] = '\0';
	if (s == 0)
	{
		ret[0] = 48;
		return (ret);
	}
	get_tab(i, s, ret);
	return (ret);
}
