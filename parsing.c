/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 02:26:48 by ztouzri           #+#    #+#             */
/*   Updated: 2021/11/01 15:06:06 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_info	*initinfo(void)
{
	t_info	*infos;

	infos = ft_calloc(1, sizeof (t_info));
	infos->no = 0;
	infos->so = 0;
	infos->we = 0;
	infos->ea = 0;
	infos->f = 0;
	infos->c = 0;
	infos->map = NULL;
	infos->scale = 0.5;
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

void	printinfo(t_info *infos)
{
	printf("no == %s, so == %d, we == %d, ea == %d\n f == %d, c == %d\n", infos->no, infos->so, infos->we, infos->ea, infos->f, infos->c);
}

int	goline(int fd, int nbline, char *filename)
{
	int		i;
	char	*tmp;
	int		ret;

	close(fd);
	fd = open(filename, O_RDONLY);
	ret = get_next_line(fd, &tmp);
	i = 1;
	while (ret > 0 && i < nbline)
	{
		ret = get_next_line(fd, &tmp);
		i++;
	}
	return (fd);
}

t_info	*parsinfo(int fd, char *filename, t_info *infos)
{
	char	*line;
	char	**tmp;
	int		ret;
	int		nbline;

	nbline = 0;
	ret = get_next_line(fd, &line);
	while (ret > 0 && !ismapstart(line))
	{
		if (!fillnorth(line, infos)
			|| !fillsouth(line, infos)
			|| !fillwest(line, infos)
			|| !filleast(line, infos)
			|| !fillfloor(line, infos)
			|| !fillceil(line, infos))
			return (infos);
		free(line);
		ret = get_next_line(fd, &line);
		nbline++;
	}
	infos->maxx = 0;
	while (ret > 0)
	{
		if ((int)ft_strlen(line) > infos->maxx)
			infos->maxx = ft_strlen(line);
		free(line);
		ret = get_next_line(fd, &line);
	}
	free(line);
	close(fd);
	fd = open(filename, O_RDONLY);
	ret = get_next_line(fd, &line);
	int i = 0;
	while (ret > 0 && i < nbline)
	{
		free(line);
		ret = get_next_line(fd, &line);
		i++;
	}
	//add spaces so that every line in map is equally sized
	while (ret > 0)
	{
		// free(line);
		tmp = infos->map;
		infos->map = ft_join(infos->map, ft_padding(line, infos->maxx, ' '));
		freesplit(tmp);
		ret = get_next_line(fd, &line);
	}
	ft_printsplit(infos->map);
	tmp = infos->map;
	infos->map = ft_join(tmp, ft_padding(line, infos->maxx, ' '));
	freesplit(tmp);
	free(line);
	if (!ismapgood(infos->map))
	{
		printf("Error\nInvalid Map\n");
		exit(1);
	}
	infos->maxy = ft_splitlen(infos->map);
	return (infos);
}
