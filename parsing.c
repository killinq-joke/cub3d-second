/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 02:26:48 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/24 16:02:47 by ztouzri          ###   ########.fr       */
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
	infos.map = 0;
	return (infos);
}

t_info	parsinfo(int fd)
{
	t_info	infos;
	char	*line;
	int		ret;

	infos = initinfo();
	ret = get_next_line(fd, &line);
	while (ret > 0)
	{
		fillnorth(line, &infos);
		fillsouth(line, &infos);
		fillwest(line, &infos);
		filleast(line, &infos);
		free(line);
		ret = get_next_line(fd, &line);
	}
	free(line);
	return (infos);
}
