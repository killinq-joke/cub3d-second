/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 16:02:37 by ztouzri           #+#    #+#             */
/*   Updated: 2021/11/04 11:31:33 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	fillnorth(char *line, t_info *infos)
{
	int	i;
	int	fd;

	i = 2;
	if (!ft_strncmp("NO ", line, 3))
	{
		if (infos->no != 0)
			return (FALSE);
		while (line[i] == ' ')
			i++;
		if (!dotxpmcheck(&line[i]))
			return (FALSE);
		fd = open(&line[i], O_RDONLY);
		if (fd == -1)
			return (FALSE);
		infos->no = ft_strdup(&line[i]);
		return (TRUE);
	}
	return (TRUE);
}

t_bool	fillsouth(char *line, t_info *infos)
{
	int	i;
	int	fd;

	i = 2;
	if (!ft_strncmp("SO ", line, 3))
	{
		if (infos->so || !infos->no)
			return (FALSE);
		while (line[i] == ' ')
			i++;
		if (!dotxpmcheck(&line[i]))
			return (FALSE);
		fd = open(&line[i], O_RDONLY);
		if (fd == -1)
			return (FALSE);
		infos->so = ft_strdup(&line[i]);
		return (TRUE);
	}
	return (TRUE);
}

t_bool	fillwest(char *line, t_info *infos)
{
	int	i;
	int	fd;

	i = 2;
	if (!ft_strncmp("WE ", line, 3))
	{
		if (infos->we || !infos->so || !infos->no)
			return (FALSE);
		while (line[i] == ' ')
			i++;
		if (!dotxpmcheck(&line[i]))
			return (FALSE);
		fd = open(&line[i], O_RDONLY);
		if (fd == -1)
			return (FALSE);
		infos->we = ft_strdup(&line[i]);
		return (TRUE);
	}
	return (TRUE);
}

t_bool	filleast(char *line, t_info *infos)
{
	int	i;
	int	fd;

	i = 2;
	if (!ft_strncmp("EA ", line, 3))
	{
		if (infos->ea || !infos->we || !infos->so || !infos->no)
			return (FALSE);
		while (line[i] == ' ')
			i++;
		if (!dotxpmcheck(&line[i]))
			return (FALSE);
		fd = open(&line[i], O_RDONLY);
		if (fd == -1)
			return (FALSE);
		infos->ea = ft_strdup(&line[i]);
		return (TRUE);
	}
	return (TRUE);
}
