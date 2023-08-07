/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:28:11 by tlafay            #+#    #+#             */
/*   Updated: 2022/05/06 11:21:23 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

long	time_diff(struct timeval start, struct timeval end)
{
	return ((end.tv_sec * 1000000 + end.tv_usec)
		- (start.tv_sec * 1000000 + start.tv_usec));
}

int	invert_y(int y, int height)
{
	y -= height * 0.5;
	return (-y + height * 0.5);
}

void	ft_exit(char *str)
{
	if (str)
		ft_put(str);
	exit(EXIT_FAILURE);
}

double	ft_fabs(double num)
{
	if (num > 0)
		return (num);
	else
		return (-num);
}
