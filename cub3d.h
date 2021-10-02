/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mout <mout@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 01:35:50 by ztouzri           #+#    #+#             */
/*   Updated: 2021/10/02 12:56:01 by mout             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include "libft.h"

typedef enum e_bool {
	FALSE,
	TRUE,
}				t_bool;

typedef struct s_info {
	int		no;
	int		so;
	int		we;
	int		ea;
	int		f;
	int		c;
	char	**map;
}				t_info;

//checker.c
t_bool	dotcubcheck(char *str);
t_bool	dotxpmcheck(char *str);
t_bool	fullspacecheck(char *str);
//parsing.c
t_info	parsinfo(int fd, char *filename);
//fill.c
t_bool	fillnorth(char *line, t_info *infos);
t_bool	fillsouth(char *line, t_info *infos);
t_bool	fillwest(char *line, t_info *infos);
t_bool	filleast(char *line, t_info *infos);
t_bool	fillfloor(char *line, t_info *infos);
t_bool	fillceil(char *line, t_info *infos);
void	freeinfo(t_info infos);

#endif