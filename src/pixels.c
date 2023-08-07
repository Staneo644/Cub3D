/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 17:06:23 by tlafay            #+#    #+#             */
/*   Updated: 2022/05/05 17:06:26 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_pixel(t_image *img, int x, int y)
{
	char	*dst;
	int		color;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return (color);
}

int	better_get_pixel(t_texture text, int x, int y)
{
	y = invert_y(y, text.height);
	return (get_pixel(&text.img, x, y));
}

void	better_pixel_put(t_image *img, int x, int y, int color)
{
	y = invert_y(y, SIZE_SCREEN_HEIGHT);
	if (x >= 0 && x < SIZE_SCREEN_WIDTH
		&& y >= 0 && y < SIZE_SCREEN_HEIGHT)
		my_mlx_pixel_put(img, x, y, color);
}
