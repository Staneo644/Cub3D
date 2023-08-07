/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:31:49 by tlafay            #+#    #+#             */
/*   Updated: 2022/04/19 17:32:25 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_image	draw_square(t_image img, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_P_SIZE)
	{
		j = 0;
		while (j < MINIMAP_P_SIZE)
		{
			better_pixel_put(&img, x + i + MINIMAP_WIDTH,
				y + j + MINIMAP_HEIGHT, color);
			j++;
		}
		i++;
	}
	return (img);
}

t_image	minimap(t_image img, t_cub *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map.map[y])
	{
		x = 0;
		while (game->map.map[y][x])
		{
			if (game->map.map[y][x] == '1')
				img = draw_square(img, x * MINIMAP_P_SIZE,
						y * MINIMAP_P_SIZE, 0x000000FF);
			else if (game->map.map[y][x] != ' ')
				img = draw_square(img, x * MINIMAP_P_SIZE,
						y * MINIMAP_P_SIZE, 0x00FF0000);
			x++;
		}
		y++;
	}
	img = draw_square(img, game->pos.p_x * MINIMAP_P_SIZE - MINIMAP_P_SIZE / 2,
			game->pos.p_y * MINIMAP_P_SIZE - MINIMAP_P_SIZE / 2, 0x0000FF00);
	return (img);
}
