/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:21:11 by ajossera          #+#    #+#             */
/*   Updated: 2022/05/05 16:39:17 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_move(t_cub *game, t_pos *pers, int x, int y)
{
	if (game->map.map[(int)(pers->p_y + (SPEED * (x * sin(pers->angle_of_view)
					+ y * cos(pers->angle_of_view))))]
		[(int)(pers->p_x + SPEED * (x * cos(pers->angle_of_view)
				- y * sin(pers->angle_of_view)))] == '1')
		return (0);
	(void)game;
	pers->p_x = pers->p_x + SPEED
		* (x * cos(pers->angle_of_view) - y * sin(pers->angle_of_view));
	pers->p_y = pers->p_y + SPEED
		* (x * sin(pers->angle_of_view) + y * cos(pers->angle_of_view));
	return (0);
}

t_image	ft_draw_frame(t_image img, t_cub *game)
{
	img = raycast(img, game);
	img = minimap(img, game);
	return (img);
}

int	ft_search_p(char **argv, char a, int x)
{
	int	i;
	int	j;

	i = -1;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (argv[i][j] == a && x == 1)
				return (i);
			if (argv[i][j] == a && x == 0)
				return (j);
		}
	}
	return (-1);
}

int	ft_next_pars(t_map *map)
{
	t_cub	game;

	ft_init_cub(&game, map);
	game.img.img = mlx_new_image(game.mlx, SIZE_SCREEN_WIDTH,
			SIZE_SCREEN_HEIGHT);
	game.img.addr = mlx_get_data_addr(game.img.img,
			&game.img.bits_per_pixel, &game.img.line_length,
			&game.img.endian);
	game.tmp.img = mlx_new_image(game.mlx,
			SIZE_SCREEN_WIDTH, SIZE_SCREEN_HEIGHT);
	game.tmp.addr = mlx_get_data_addr(game.tmp.img,
			&game.tmp.bits_per_pixel, &game.tmp.line_length, &game.tmp.endian);
	game.win = mlx_new_window(game.mlx, SIZE_SCREEN_WIDTH,
			SIZE_SCREEN_HEIGHT, "Andy Murray casting");
	load_xpms(&game);
	mlx_hook(game.win, 17, 1L << 17, ft_close, &game);
	mlx_hook(game.win, 2, 1L << 0, ft_key, &game);
	mlx_hook(game.win, 3, 1L << 1, ft_key_release, &game);
	mlx_hook(game.win, 6, 0L, mouse_turn, &game);
	mlx_mouse_hide();
	mlx_mouse_move(game.win, SIZE_SCREEN_WIDTH / 2, SIZE_SCREEN_HEIGHT / 2);
	game.old_x = SIZE_SCREEN_WIDTH / 2;
	mlx_loop_hook(game.mlx, render_next_frame, &game);
	mlx_loop(game.mlx);
	return (0);
}
