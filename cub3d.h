/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 01:35:50 by ztouzri           #+#    #+#             */
/*   Updated: 2021/10/27 16:52:47 by ztouzri          ###   ########.fr       */
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
# define LEFTARR 123
# define RIGHTARR 124
# define ESC 53
# define SHIFT 257
# define WIDTH 1920
# define HEIGHT 1080

typedef enum e_bool {
	FALSE,
	TRUE,
}				t_bool;

typedef struct s_ray {
	double	x;
	double	y;
	double	adj;
	double	op;
	double	xa;
	double	ya;
}				t_ray;

typedef struct s_pl {
	double	x;
	double	y;
	double	rayhx;
	double	rayhy;
	double	rayvx;
	double	rayvy;
	double	angle;
	t_ray	r;
	t_bool	left;
	t_bool	right;
	t_bool	w;
	t_bool	a;
	t_bool	s;
	t_bool	d;
	double	speed;
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
	int		blockmeter;
	t_pl	player;
	void	*mlx;
	void	*win;
	t_img	img;
	double	dx;
	double	dy;
	int		steps;
	double	xinc;
	double	yinc;
	double	x;
	double	y;
	t_ray	r;
}				t_info;

//checker.c
t_bool	dotcubcheck(char *str);
t_bool	dotxpmcheck(char *str);
t_bool	fullspacecheck(char *str);
t_bool	ismapgood(char **map);
//parsing.c
t_info	*initinfo(void);
t_info	*parsinfo(int fd, char *filename, t_info *infos);
//fill.c;
t_bool	fillnorth(char *line, t_info *infos);
t_bool	fillsouth(char *line, t_info *infos);
t_bool	fillwest(char *line, t_info *infos);
t_bool	filleast(char *line, t_info *infos);
t_bool	fillfloor(char *line, t_info *infos);
t_bool	fillceil(char *line, t_info *infos);
void	freeinfo(t_info *infos);
//print.c
void	ft_putpixel(t_img *img, int x, int y, int color);
void	printminimapblock(int y, int x, t_info *infos);
int		printplayer(t_info *infos);
int		printminimap(t_info *infos);
//events.c
int		destroy_window(t_info *infos);
int		keypress(int key, t_info *infos);
int		keyrelease(int key, t_info *infos);
int		motion(int x, int y, t_info *infos);

#endif