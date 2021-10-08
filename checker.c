/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 02:15:53 by ztouzri           #+#    #+#             */
/*   Updated: 2021/10/06 18:04:12 by ztouzri          ###   ########.fr       */
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
		if (!ft_isin("10 NSEW", line[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_bool	crosscheck(char **map, int y, int x)
{
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
	int	i;

	i = 0;
	while (map[y][i])
	{
		if (ft_isin("0NSWE", map[y][i]))
			return (FALSE);
		printf("%s\n", &map[y][i]);
		i++;
	}
	if (map[y - 1][x] == ' '
	|| map[y][x - 1] == ' '
	|| map[y][x + 1] == ' ')
		return (FALSE);
	return (TRUE);
}

t_bool	ismapgood(char **map)
{
	int	y;
	int	x;

	if (!map)
		return (FALSE);
	y = 0;
	while (map[y])
	{
		if (!iscorrectmapline(map[y]))
			return (FALSE);
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0')
			{
				if (y == 0)
				{
					if (!tcheck(map, x))
						return (FALSE);
				}
				else if (x == 0)
				{
					if (!lefttcheck(map, y))
						return (FALSE);
				}
				else if (x == (int)ft_strlen(map[y]) - 1)
				{
					if (!righttcheck(map, y, x))
						return (FALSE);
				}
				else if (y == ft_splitlen(map) - 1)
				{
					if (!bottomtcheck(map, y, x))
						return (FALSE);
				}
				else if (!crosscheck(map, y, x))
					return (FALSE);
			}
			x++;
		}
		y++;
	}
	return (TRUE);
}
