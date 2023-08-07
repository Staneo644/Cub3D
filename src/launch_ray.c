/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 10:18:13 by tlafay            #+#    #+#             */
/*   Updated: 2022/05/06 10:18:55 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_point	ray_args(t_pos pos, t_point unit_step, t_point angle, t_point *ray)
{
	t_point	inc;

	if (angle.x < 0)
	{
		inc.x = -1;
		ray->x = (pos.p_x - (int)pos.p_x) * unit_step.x;
	}
	else
	{
		inc.x = 1;
		ray->x = ((int)pos.p_x + 1 - pos.p_x) * unit_step.x;
	}
	if (angle.y < 0)
	{
		inc.y = -1;
		ray->y = (pos.p_y - (int)pos.p_y) * unit_step.y;
	}
	else
	{
		inc.y = 1;
		ray->y = ((int)pos.p_y + 1 - pos.p_y) * unit_step.y;
	}
	return (inc);
}

double	ray_inc(int *coord, double inc, double *ray, double unit_step)
{
	double	distance;

	*coord += inc;
	distance = *ray;
	*ray += unit_step;
	return (distance);
}

double	orientate(double angle, int or1, int or2)
{
	if (angle > 0)
		return (or1);
	else
		return (or2);
}

void	launch_ray(t_cub *game, t_point angle,
	double *distance, int *orientation)
{
	t_point	unit_step;
	t_point	inc;
	t_point	ray;
	int		x;
	int		y;

	x = game->pos.p_x;
	y = game->pos.p_y;
	unit_step.x = ft_fabs(1.0f / angle.x);
	unit_step.y = ft_fabs(1.0f / angle.y);
	inc = ray_args(game->pos, unit_step, angle, &ray);
	while (game->map.map[y][x] != '1')
	{
		if (ray.x < ray.y)
		{
			*distance = ray_inc(&x, inc.x, &ray.x, unit_step.x);
			*orientation = orientate(angle.x, WEST, EAST);
		}
		else
		{
			*distance = ray_inc(&y, inc.y, &ray.y, unit_step.y);
			*orientation = orientate(angle.y, SOUTH, NORTH);
		}
	}
}
