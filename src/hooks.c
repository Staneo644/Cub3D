/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 10:00:43 by tlafay            #+#    #+#             */
/*   Updated: 2022/05/10 14:43:14 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_close(t_cub *game)
{
	ft_free_map(&(game->map), -1);
	ft_exit("");
	return (0);
}

int	ft_key(int a, t_cub *game)
{
	if (a == 53)
		ft_close(game);
	if (a == UP || a == DOWN || a == 123
		|| a == 124 || a == 0 || a == 2)
	{
		if (a == UP)
			game->key.up_p = 1;
		if (a == DOWN)
			game->key.down_p = 1;
		if (a == LEFT)
			game->key.left_p = 1;
		if (a == RIGHT)
			game->key.right_p = 1;
		if (a == 123)
			game->pos.angle_of_view += SPEED_TURN_VIEW;
		if (a == 124)
			game->pos.angle_of_view -= SPEED_TURN_VIEW;
	}
	return (0);
}

int	ft_key_release(int a, t_cub *game)
{
	if (a == UP)
		game->key.up_p = 0;
	if (a == DOWN)
		game->key.down_p = 0;
	if (a == LEFT)
		game->key.left_p = 0;
	if (a == RIGHT)
		game->key.right_p = 0;
	return (0);
}

int	mouse_turn(int x, int y, t_cub *game)
{
	double	pos;

	(void)y;
	pos = x;
	mlx_mouse_hide();
	game->pos.angle_of_view += (double)((game->old_x - pos) / 200);
	if (pos >= SIZE_SCREEN_WIDTH)
		pos -= SIZE_SCREEN_WIDTH;
	if (pos < 0)
		pos += SIZE_SCREEN_WIDTH;
	mlx_mouse_move(game->win, pos, SIZE_SCREEN_HEIGHT / 2);
	game->old_x = pos;
	return (0);
}

int	render_next_frame(t_cub *game)
{
	struct timeval	now;
	char			*fps;

	if (game->key.up_p)
		ft_move(game, &(game->pos), 1, 0);
	if (game->key.down_p)
		ft_move(game, &(game->pos), -1, 0);
	if (game->key.left_p)
		ft_move(game, &(game->pos), 0, 1);
	if (game->key.right_p)
		ft_move(game, &(game->pos), 0, -1);
	if (game->pos.angle_of_view >= M_PI * 2)
		game->pos.angle_of_view -= M_PI * 2;
	if (game->pos.angle_of_view < 0)
		game->pos.angle_of_view += M_PI * 2;
	game->img = ft_draw_frame(game->img, game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	gettimeofday(&now, NULL);
	fps = ft_itoa(1000000 / time_diff(game->last_time, now));
	mlx_string_put(game->mlx, game->win, 5, 15,
		0x0000FF00, fps);
	free(fps);
	game->last_time = now;
	return (0);
}
