/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 16:35:28 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/26 19:26:52 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	fillfloor(char *line, t_info *infos)
{
	int	i;

	i = 1;
	if (!ft_strncmp("F ", line, 2))
	{
		if (infos->f || !infos->ea || !infos->we || !infos->so || !infos->no)
			return (FALSE);
		while (line[i] == ' ')
			i++;
		infos->f = open(&line[i], O_RDONLY);
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
		if (infos->c || !infos->f || !infos->ea
			|| !infos->we || !infos->so || !infos->no)
			return (FALSE);
		while (line[i] == ' ')
			i++;
		infos->c = open(&line[i], O_RDONLY);
		if (infos->c == -1)
			return (FALSE);
		return (TRUE);
	}
	return (TRUE);
}
