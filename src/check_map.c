/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajossera <ajossera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:49:38 by ajossera          #+#    #+#             */
/*   Updated: 2022/05/10 13:56:02 by ajossera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_check_with_zero(char **str, int i, int j)
{
	if (str[i][j + 1] == ' ' || str[i][j + 1] == '\0')
		return (1);
	if (str[i][j - 1] == ' ')
		return (1);
	if (i == 0 || j == 0)
		return (1);
	if (i == (ft_pstrlen(str) - 1) || j == (ft_strlen(str[i])))
		return (1);
	if (ft_strlen(str[i - 1]) < (j + 2))
		return (1);
	if (ft_strlen(str[i + 1]) < (j + 2))
		return (1);
	if (str[i - 1][j - 1] == ' ' || str[i - 1][j] == ' '
			|| str[i - 1][j + 1] == ' ')
		return (1);
	if (str[i + 1][j - 1] == ' ' || str[i + 1][j] == ' '
			|| str[i + 1][j + 1] == ' ')
		return (1);
	return (0);
}

int	ft_for_norminette(int i, int j)
{
	return (1
		+ ft_error("An empty place doesn't have walls in ")
		+ ft_putnb(i + 1) + ft_put(" line and ")
		+ ft_putnb(j + 1) + ft_put(" column\n"));
}

int	ft_check_map_error(char **str, int i)
{
	int		j;
	char	whichchar;

	whichchar = 0;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if ((str[i][j] == 'N' || str[i][j] == 'S' || str[i][j] == 'E'
					|| str[i][j] == 'W') && whichchar == 0)
				whichchar = str[i][j];
			else if (str[i][j] != ' ' && str[i][j] != '1' && str[i][j] != '0')
				return (1 + ft_error("Invalid caracter in the map, in ")
					+ ft_putnb(i + 1) + ft_put(" line and ")
					+ ft_putnb(j + 1) + ft_put(" column\n"));
			if (str[i][j] == '0' || str[i][j] == whichchar)
				if (ft_check_with_zero(str, i, j))
					return (ft_for_norminette(i, j));
		}
	}
	if (whichchar == 0)
		return (1 + ft_error("There is no place in the map to pop\n"));
	return (0);
}
