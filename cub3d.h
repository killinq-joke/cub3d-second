/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 01:35:50 by ztouzri           #+#    #+#             */
/*   Updated: 2021/10/07 22:14:04 by ztouzri          ###   ########.fr       */
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

# define W 13
# define S 1
# define A 0
# define D 2
# define ESC 53

typedef enum e_bool {
	FALSE,
	TRUE,
}				t_bool;

typedef struct s_pl {
	int	x;
	int	y;
	int	speed;
}				t_pl;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_info {
	int		no;
	int		so;
	int		we;
	int		ea;
	int		f;
	int		c;
	char	**map;
	int		mapx;
	int		mapy;
	int		maxx;
	int		maxy;
	t_pl	player;
	void	*mlx;
	void	*win;
	t_img	img;
}				t_info;

//checker.c
t_bool	dotcubcheck(char *str);
t_bool	dotxpmcheck(char *str);
t_bool	fullspacecheck(char *str);
t_bool	ismapgood(char **map);
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