/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:36:27 by tlafay            #+#    #+#             */
/*   Updated: 2022/05/05 16:26:10 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/*int	add_shade(int color, double intensity)
{
	return (create_trgb(get_t(color), get_r(color) * intensity,
			get_g(color) * intensity, get_b(color) * intensity));
}*/

t_image	vertical_line(t_line line, t_point pos, int orientation)
{
	int			height;
	double		diff;
	double		hit;

	if (orientation == SOUTH || orientation == NORTH)
		hit = (pos.x - floor(pos.x));
	else
		hit = (pos.y - floor(pos.y));
	if (orientation == SOUTH || orientation == EAST)
			hit = ((hit - 0.5) * -1) + 0.5;
	line.distance = (double)WALL_HEIGHT / line.distance;
	diff = (SIZE_SCREEN_HEIGHT - line.distance) * 0.5;
	if (diff < 0)
		diff = 0;
	height = 0;
	height = draw_floor(&line.img, create_trgb(0, line.game->map.f[0],
				line.game->map.f[1], line.game->map.f[2]), line.x, diff);
	line.img = draw_walls(line, get_texture(line.game, orientation),
			&height, hit);
	line.img = draw_ceiling(line.img, height,
			create_trgb(0, line.game->map.c[0],
				line.game->map.c[1], line.game->map.c[2]), line.x);
	return (line.img);
}

t_point	calculate_diff(t_cub *game, int x, double H, double unit)
{
	t_point	left;
	t_point	right;
	t_point	current;
	t_point	dir;
	double	norm;

	H = 1.0 / cos(FOV * 0.5);
	right.x = game->pos.p_x + H * cos(game->pos.angle_of_view - FOV * 0.5);
	right.y = game->pos.p_y + H * sin(game->pos.angle_of_view - FOV * 0.5);
	left.x = game->pos.p_x + H * cos(game->pos.angle_of_view + FOV * 0.5);
	left.y = game->pos.p_y + H * sin(game->pos.angle_of_view + FOV * 0.5);
	unit = 2.0 * tan((FOV) * 0.5) * (double)INV_SIZE_SCREEN_WIDTH;
	norm = sqrt((right.x - left.x) * (right.x - left.x)
			+ (right.y - left.y) * (right.y - left.y));
	current.x = left.x + ((unit * x
				/ norm) * (right.x - left.x));
	current.y = left.y + ((unit * x
				/ norm) * (right.y - left.y));
	dir.x = (current.x - game->pos.p_x);
	dir.y = (current.y - game->pos.p_y);
	return (dir);
}

t_line	init_line(t_cub *game, t_image img, int x, double distance)
{
	t_line	ret;

	ret.game = game;
	ret.img = img;
	ret.x = x;
	ret.distance = distance;
	return (ret);
}

t_image	raycast(t_image img, t_cub *game)
{
	double	distance;
	int		x;
	int		orientation;
	t_point	pos;
	t_point	dir;

	x = 0;
	while (x < SIZE_SCREEN_WIDTH)
	{
		dir = calculate_diff(game, x, 0, 0);
		distance = 0;
		launch_ray(game, dir, &distance, &orientation);
		pos.x = game->pos.p_x + dir.x * distance;
		pos.y = game->pos.p_y + dir.y * distance;
		img = vertical_line(init_line(game,
					img, x, distance), pos, orientation);
		x++;
	}
	return (img);
}
