/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 02:15:53 by ztouzri           #+#    #+#             */
/*   Updated: 2021/10/12 15:43:32 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	dotcubcheck(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!ft_strcmp(&str[i], ".cub"))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	dotxpmcheck(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!ft_strcmp(&str[i], ".xpm"))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	fullspacecheck(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] != ' ')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_bool	iscorrectmapline(char *line)
{
	int	i;

	if (!line)
		return (FALSE);
	i = 0;
	while (line[i])
	{
		printf("-----%s\n", &line[i]);
		if (!ft_isin("10 NSEW", line[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_bool	tcheck(char **map, int x)
{
	if (map[1][x] == ' '
	|| map[0][x - 1] == ' '
	|| map[0][x + 1] == ' ')
		return (FALSE);
	return (TRUE);
}

t_bool	lefttcheck(char **map, int y)
{
	if (map[y - 1][0] == ' '
	|| map[y + 1][0] == ' '
	|| map[y][1] == ' ')
		return (FALSE);
	return (TRUE);
}

t_bool	righttcheck(char **map, int y, int x)
{
	if (map[y - 1][x] == ' '
	|| map[y + 1][x] == ' '
	|| map[y][x - 1] == ' ')
		return (FALSE);
	return (TRUE);
}

t_bool	bottomtcheck(char **map, int y, int x)
{
	if (ft_isin("0NSWE", map[y][x]))
		return (FALSE);
	if (map[y - 1][x] == ' '
	|| map[y][x - 1] == ' '
	|| map[y][x + 1] == ' ')
		return (FALSE);
	return (TRUE);
}

t_bool	crosscheck(char **map, int y, int x)
{
	if (y == 0 && !tcheck(map, y))
		return (FALSE);
	if (x == 0 && !lefttcheck(map, y))
		return (FALSE);
	if (y == ft_splitlen(map) - 1 && !bottomtcheck(map, y, x))
		return (FALSE);
	if (x == (int)ft_strlen(map[y]) - 1 && !righttcheck(map, y, x))
		return (FALSE);
	if (map[y - 1][x] == ' '
	|| map[y + 1][x] == ' '
	|| map[y][x - 1] == ' '
	|| map[y][x + 1] == ' ')
	{
		printf("y == %d x == %d\n", y, x);
		return (FALSE);
	}
	return (TRUE);
}

t_bool	ismapgood(char **map)
{
	int	y;
	int	x;
	int	nbplayer;

	if (!map)
		return (FALSE);
	nbplayer = 0;
	y = 0;
	while (map[y])
	{
		if (!iscorrectmapline(map[y]))
			return (FALSE);
		x = 0;
		while (map[y][x])
		{
			if (ft_isin("0NSEW", map[y][x]))
			{
				if (!crosscheck(map, y, x))
					return (FALSE);
			}
			if (ft_isin("NSEW", map[y][x]))
				nbplayer++;
			x++;
		}
		y++;
	}
	if (!nbplayer || nbplayer > 1)
		return (FALSE);
	return (TRUE);
}
