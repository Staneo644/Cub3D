/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_map_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajossera <ajossera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:01:33 by ajossera          #+#    #+#             */
/*   Updated: 2022/05/10 14:01:49 by ajossera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_is_not_full(t_map *map)
{
	if (map->eafd == NULL || map->nofd == NULL
		|| map->sofd == NULL || map->wefd == NULL)
		return (1);
	if (map->f == NULL || map->c == NULL)
		return (1);
	return (0);
}

void	ft_initialise_map(t_map *map)
{
	map->nofd = NULL;
	map->sofd = NULL;
	map->wefd = NULL;
	map->eafd = NULL;
	map->c = NULL;
	map->f = NULL;
	map->map = NULL;
}

int	ft_free_map(t_map *map, int fd)
{
	int	i;

	if (map->eafd)
		free(map->eafd);
	if (map->nofd)
		free(map->nofd);
	if (map->sofd)
		free(map->sofd);
	if (map->wefd)
		free(map->wefd);
	if (map->f)
		free(map->f);
	if (map->c)
		free(map->c);
	if (map->map)
	{
		i = -1;
		while (map->map[++i])
			if (map->map[i])
				free(map->map[i]);
		free(map->map);
	}
	if (fd > -1)
		close(fd);
	return (0);
}
