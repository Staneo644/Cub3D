/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajossera <ajossera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:34:46 by ajossera          #+#    #+#             */
/*   Updated: 2022/05/10 14:04:42 by ajossera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	ft_mute_char(int fd, char muted, int type)
{
	char	car;
	int		i;

	if (type)
	{
		i = read(fd, &car, 1);
		if (i <= 0 || car != muted)
			return (0);
	}
	else
		car = muted;
	while (car == muted)
	{
		i = read(fd, &car, 1);
		if (i <= 0)
			return (0);
	}
	return (car);
}

int	ft_redirect_char(char a, int fd, t_map *map)
{
	if (a == 'N')
		return (ft_file_parse(a, 'O', &(map->nofd), fd));
	if (a == 'S')
		return (ft_file_parse(a, 'O', &(map->sofd), fd));
	if (a == 'E')
		return (ft_file_parse(a, 'A', &(map->eafd), fd));
	if (a == 'W')
		return (ft_file_parse(a, 'E', &(map->wefd), fd));
	if (a == 'F')
		return (ft_color_parse(a, &(map->f), fd));
	if (a == 'C')
		return (ft_color_parse(a, &(map->c), fd));
	return (ft_error("Incorrect char ") + ft_putc(a) + ft_putc('\n'));
}

int	ft_main_pars(int fd, t_map *map)
{
	char	a;

	ft_initialise_map(map);
	while (ft_is_not_full(map))
	{
		a = ft_mute_char(fd, '\n', 0);
		if (!a)
			return (ft_error("No map in the file\n"));
		if (ft_redirect_char(a, fd, map) == 0)
			return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_map	map;

	if (argc != 2)
		return (ft_error("Incorrect number of arguments\n"));
	if (ft_strlen(argv[1]) < 5)
		return (ft_error("Incorrect size of arguments\n"));
	if (argv[1][ft_strlen(argv[1]) - 1] != 'b'
		|| argv[1][ft_strlen(argv[1]) - 2] != 'u'
		|| argv[1][ft_strlen(argv[1]) - 3] != 'c'
		|| argv[1][ft_strlen(argv[1]) - 4] != '.')
		return (ft_error("Incorrect type of file\n"));
	argc = open(argv[1], O_RDONLY);
	if (argc == -1)
		return (ft_error("Error in file's opening\n"));
	if (!ft_main_pars(argc, &map))
		return (ft_free_map(&map, argc));
	if (!ft_map_pars(argc, &map))
		return (ft_free_map(&map, argc));
	if (ft_check_map_error(map.map, -1))
		return (ft_free_map(&map, argc));
	close(argc);
	ft_next_pars(&map);
	return (0);
}
	//ft_write_map(&map);
	//ft_write_pstr(map.map);
