/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 02:26:48 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/29 19:38:34 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_info	initinfo(void)
{
	t_info	infos;

	infos.no = 0;
	infos.so = 0;
	infos.we = 0;
	infos.ea = 0;
	infos.f = 0;
	infos.c = 0;
	infos.map = NULL;
	return (infos);
}

int	ismapstart(char *line)
{
	int	i;

	i = 0;
	if (ft_isin("NSWEFC", line[0]))
		return (0);
	while (line && line[i])
	{
		if (ft_isin("10", line[i]))
			return (1);
		i++;
	}
	return (0);
}

void	printinfo(t_info infos)
{
	printf("no == %d, so == %d, we == %d, ea == %d\n f == %d, c == %d\n", infos.no, infos.so, infos.we, infos.ea, infos.f, infos.c);
}

t_info	parsinfo(int fd)
{
	t_info	infos;
	char	*line;
	char	**tmp;
	int		ret;

	infos = initinfo();
	ret = get_next_line(fd, &line);
	while (ret > 0 && !ismapstart(line))
	{
		fillnorth(line, &infos);
		fillsouth(line, &infos);
		fillwest(line, &infos);
		filleast(line, &infos);
		fillfloor(line, &infos);
		fillceil(line, &infos);
		printinfo(infos);
		free(line);
		ret = get_next_line(fd, &line);
	}
	while (ret > 0)
	{
		tmp = infos.map;
		infos.map = ft_join(infos.map, line);
		freesplit(tmp);
		ret = get_next_line(fd, &line);
	}
	// free(line);
	ft_printsplit(infos.map);
	return (infos);
}
