/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 10:21:47 by tlafay            #+#    #+#             */
/*   Updated: 2022/05/06 10:23:51 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	draw_floor(t_image *img, int color, int x, double diff)
{
	int	height;

	height = 0;
	while (height <= diff)
	{
		better_pixel_put(img, x, height, color);
		height++;
	}
	return (height);
}

t_texture	get_texture(t_cub *game, int orientation)
{
	if (orientation == EAST)
		return (game->ea_text);
	else if (orientation == NORTH)
		return (game->no_text);
	else if (orientation == SOUTH)
		return (game->so_text);
	else
		return (game->we_text);
}

t_image	draw_walls(t_line line, t_texture text, int *height, double hit)
{
	int			y;
	int			color;
	double		inv_distance;
	double		x_text;
	double		end;

	y = 0;
	if (line.distance > SIZE_SCREEN_HEIGHT)
		y = (int)((line.distance - SIZE_SCREEN_HEIGHT) * 0.5);
	inv_distance = 1 / line.distance;
	x_text = hit * text.width;
	end = ((SIZE_SCREEN_HEIGHT - line.distance) * 0.5) + line.distance;
	if (end - line.distance < 0)
		end = line.distance;
	while (*height < SIZE_SCREEN_HEIGHT && *height <= end)
	{
		color = better_get_pixel(text, x_text,
				(double)(y * inv_distance) *text.height);
		better_pixel_put(&line.img, line.x, *height, color);
		(*height)++;
		y++;
	}
	return (line.img);
}

t_image	draw_ceiling(t_image img, int height, int color, int x)
{
	while (height < SIZE_SCREEN_HEIGHT)
	{
		better_pixel_put(&img, x, height, color);
		height++;
	}
	return (img);
}
