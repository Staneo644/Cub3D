/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajossera <ajossera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:51:18 by ajossera          #+#    #+#             */
/*   Updated: 2022/05/10 13:56:04 by ajossera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_pstrlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_free_pstr(char **pstr)
{
	int	i;

	i = -1;
	while (pstr[++i])
		free(pstr[i]);
	free(pstr);
	return (0);
}

char	**ft_add_to_pstr(char **pstr, char *str)
{
	char	**rend;
	int		i;

	i = -1;
	if (!pstr)
		return (NULL);
	rend = malloc(sizeof(char *) * (ft_pstrlen(pstr) + 2));
	if (!rend && !ft_error("Malloc error\n"))
	{
		free(str);
		return (NULL);
	}
	while (pstr[++i])
	{
		rend[i] = pstr[i];
	}
	rend[i] = str;
	rend[i + 1] = NULL;
	if (pstr)
		free(pstr);
	pstr = NULL;
	return (rend);
}

int	ft_map_pars(int fd, t_map *map)
{
	char	*str;

	str = NULL;
	map->map = malloc(sizeof(char *) * 1);
	str = get_next_line(fd);
	if (str == NULL || !map->map)
		return (0);
	map->map[0] = NULL;
	while (str[0] == '\0')
	{
		free(str);
		str = get_next_line(fd);
		if (str == NULL)
			return (0);
	}
	while (str != NULL && str[0] != '\0')
	{
		map->map = ft_add_to_pstr(map->map, str);
		if (!(map->map))
			return (0);
		str = get_next_line(fd);
	}
	free(str);
	return (1);
}
