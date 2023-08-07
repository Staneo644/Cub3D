/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 10:14:36 by tlafay            #+#    #+#             */
/*   Updated: 2022/05/06 11:31:40 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_init_pos(t_cub *game, char a)
{
	if (ft_search_p(game->map.map, a, 1) == -1)
		return (0);
	if (a == 'W')
		game->pos.angle_of_view = 0;
	if (a == 'S')
		game->pos.angle_of_view = M_PI_2;
	if (a == 'E')
		game->pos.angle_of_view = M_PI;
	if (a == 'N')
		game->pos.angle_of_view = M_PI + M_PI_2;
	game->map.map[ft_search_p(game->map.map, a, 1)]
	[ft_search_p(game->map.map, a, 0)] = 'P';
	game->pos.p_x = ft_search_p(game->map.map, 'P', 0) + 0.5;
	game->pos.p_y = ft_search_p(game->map.map, 'P', 1) + 0.5;
	game->key.down_p = 0;
	game->key.up_p = 0;
	game->key.left_p = 0;
	game->key.right_p = 0;
	return (1);
}

int	ft_init_cub(t_cub *game, t_map *map)
{
	game->map = *map;
	ft_init_pos(game, 'N');
	ft_init_pos(game, 'S');
	ft_init_pos(game, 'E');
	ft_init_pos(game, 'W');
	game->mlx = mlx_init();
	gettimeofday(&(game->last_time), NULL);
	return (1);
}

void	check_xpms(t_cub *game)
{
	if (open(game->map.eafd, O_RDONLY) == -1
		|| open(game->map.wefd, O_RDONLY) == -1
		|| open(game->map.sofd, O_RDONLY) == -1
		|| open(game->map.nofd, O_RDONLY) == -1)
	{
		ft_error("There was an error opening a texture file\n");
		exit(1);
	}
}

void	load_xpms(t_cub *game)
{
	check_xpms(game);
	game->ea_text.img.img = mlx_xpm_file_to_image(game->mlx,
			game->map.eafd, &game->ea_text.width, &game->ea_text.height);
	game->ea_text.img.addr = mlx_get_data_addr(game->ea_text.img.img,
			&game->ea_text.img.bits_per_pixel,
			&game->ea_text.img.line_length, &game->ea_text.img.endian);
	game->no_text.img.img = mlx_xpm_file_to_image(game->mlx,
			game->map.nofd, &game->no_text.width, &game->no_text.height);
	game->no_text.img.addr = mlx_get_data_addr(game->no_text.img.img,
			&game->no_text.img.bits_per_pixel,
			&game->no_text.img.line_length, &game->no_text.img.endian);
	game->we_text.img.img = mlx_xpm_file_to_image(game->mlx,
			game->map.wefd, &game->we_text.width, &game->we_text.height);
	game->we_text.img.addr = mlx_get_data_addr(game->we_text.img.img,
			&game->we_text.img.bits_per_pixel,
			&game->we_text.img.line_length, &game->we_text.img.endian);
	game->so_text.img.img = mlx_xpm_file_to_image(game->mlx,
			game->map.sofd, &game->so_text.width, &game->so_text.height);
	game->so_text.img.addr = mlx_get_data_addr(game->so_text.img.img,
			&game->so_text.img.bits_per_pixel,
			&game->so_text.img.line_length, &game->so_text.img.endian);
}
