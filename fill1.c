/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 16:35:28 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/28 20:48:44by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	gethex(char *line)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	split = ft_split(line, ',');
	if (!ft_strisnum(split[0]) || !ft_strisnum(split[1]) || !ft_strisnum(split[2])
	|| ft_splitlen(split) != 3)
		return (-1);
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0)
		return (-1);
	freesplit(split);
	return (r * 256 * 256 + g * 256 + b);
}

t_bool	fillfloor(char *line, t_info *infos)
{
	int	i;

	i = 1;
	if (!ft_strncmp("F ", line, 2))
	{
		if (infos->f != -1 || !infos->ea || !infos->we || !infos->so || !infos->no)
			return (FALSE);
		while (line[i] == ' ')
			i++;
		infos->f = gethex(&line[i]);
		if (infos->f == -1)
			return (FALSE);
		return (TRUE);
	}
	return (TRUE);
}

t_bool	fillceil(char *line, t_info *infos)
{
	int	i;

	i = 1;
	if (!ft_strncmp("C ", line, 2))
	{
		if (infos->c != -1 || infos->f == -1 || !infos->ea
			|| !infos->we || !infos->so || !infos->no)
			return (FALSE);
		while (line[i] == ' ')
			i++;
		infos->c = gethex(&line[i]);
		// printf("hex = %x = %d\n", gethex(&line[i]), gethex(&line[i]));
		if (infos->c == -1)
			return (FALSE);
		return (TRUE);
	}
	return (TRUE);
}
