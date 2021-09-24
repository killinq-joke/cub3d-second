/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 16:02:37 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/24 16:02:56 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	fillnorth(char *line, t_info *infos)
{
	int	i;

	i = 2;
	if (!ft_strncmp("NO ", line, 3) && !infos->no)
	{
		while (line[i] == ' ')
			i++;
		infos->no = open(&line[i], O_RDONLY);
		if (infos->no == -1)
			return (FALSE);
		return (TRUE);
	}
	else
		return (FALSE);
}

t_bool	fillsouth(char *line, t_info *infos)
{
	int	i;

	i = 2;
	if (!ft_strncmp("SO ", line, 3) && !infos->so)
	{
		while (line[i] == ' ')
			i++;
		infos->so = open(&line[i], O_RDONLY);
		if (infos->so == -1)
			return (FALSE);
		return (TRUE);
	}
	else
		return (FALSE);
}

t_bool	fillwest(char *line, t_info *infos)
{
	int	i;

	i = 2;
	if (!ft_strncmp("WE ", line, 3) && !infos->so)
	{
		while (line[i] == ' ')
			i++;
		infos->we = open(&line[i], O_RDONLY);
		if (infos->we == -1)
			return (FALSE);
		return (TRUE);
	}
	else
		return (FALSE);
}

t_bool	filleast(char *line, t_info *infos)
{
	int	i;

	i = 2;
	if (!ft_strncmp("EA ", line, 3) && !infos->so)
	{
		while (line[i] == ' ')
			i++;
		infos->ea = open(&line[i], O_RDONLY);
		if (infos->ea == -1)
			return (FALSE);
		return (TRUE);
	}
	else
		return (FALSE);
}
