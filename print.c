/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 20:42:29 by ztouzri           #+#    #+#             */
/*   Updated: 2021/10/14 14:2 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_putpixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x <= 1920 && y >= 0 && y <= 1080)
	{
		dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

double	angletorad(double angle)
{
	return (angle * M_PI / 180);
}

// void	dda(double xdest, double ydest, t_info *infos)
// {
	
// }

void	continueline(t_ray *r, t_info *infos)
{
	int		x;
	int		y;

	x = r->x / infos->blockmeter;
	y = r->y / infos->blockmeter;
	while (y > -1 && y < infos->maxy && x > -1 && x < infos->maxx && infos->map[y][x] != '1')
	{
		r->x += r->xa;
		r->y += r->ya;
		x = r->x / infos->blockmeter;
		y = r->y / infos->blockmeter;
		ft_putpixel(&infos->img, r->x, r->y, 0xFF0000);
	}
}

void	printvertupright(t_info *infos)
{
	t_ray	r;

	r.x = infos->player.x;
	r.y = infos->player.y;
	r.adj = fmod(r.y, infos->blockmeter);
	r.op = tan(angletorad(infos->player.angle)) * r.adj;
	r.x += r.op;
	r.y -= r.adj;
	ft_putpixel(&infos->img, r.x, r.y, 0xFFFFFF);
	r.ya = -infos->blockmeter;
	r.xa = infos->blockmeter / tan(fabs(infos->player.angle - 90) * M_PI / 180);
	continueline(&r, infos);
	// dda(r.x, r.y, infos);
}

void	printhoriupright(t_info *infos)
{
	t_ray	r;

	r.x = infos->player.x;
	r.y = infos->player.y;
	r.adj = fabs(infos->blockmeter - fmod(r.x, infos->blockmeter));
	r.op = tan(fabs(90 - infos->player.angle) * M_PI / 180) * r.adj;
	r.x += r.adj;
	r.y -= r.op;
	ft_putpixel(&infos->img, r.x, r.y, 0x00FF00);
	r.xa = infos->blockmeter;
	r.ya = -infos->blockmeter / tan(infos->player.angle * M_PI / 180);
	continueline(&r, infos);
	// while (y > -1 && y < infos->maxy && x > -1 && x < infos->maxx && infos->map[y][x] != '1')
	// {
	// 	r.x += r.xa;
	// 	r.y += r.ya;
	// 	x = r.x / infos->blockmeter;
	// 	y = r.y / infos->blockmeter;
	// 	ft_putpixel(&infos->img, r.x, r.y, 0xFF0000);
	// }
	// dda(r.x, r.y, infos);
}

void	printvertdownright(t_info *infos)
{
	t_ray	r;

	r.x = infos->player.x;
	r.y = infos->player.y;
	r.adj = infos->blockmeter - fmod(r.y, infos->blockmeter);
	r.op = tan(fabs(180 - infos->player.angle) * M_PI / 180) * r.adj;
	r.x += r.op;
	r.y += r.adj;
	ft_putpixel(&infos->img, r.x, r.y, 0xFFFFFF);
	r.ya = infos->blockmeter;
	r.xa = infos->blockmeter / tan(fabs(90 - infos->player.angle) * M_PI / 180);
	continueline(&r, infos);
	// printf("adj == %f\n", r.adj);
}

void	printhoridownright(t_info *infos)
{
	t_ray	r;

	r.x = infos->player.x;
	r.y = infos->player.y;
	r.adj = infos->blockmeter - fmod(r.x, infos->blockmeter);
	r.op = tan(fabs((90 - infos->player.angle) * M_PI / 180)) * r.adj;
	r.x += r.adj;
	r.y += r.op;
	ft_putpixel(&infos->img, r.x, r.y, 0xFFFFFF);
	r.xa = infos->blockmeter;
	r.ya = -infos->blockmeter / tan(infos->player.angle * M_PI / 180);
	continueline(&r, infos);
	// printf("adj == %f\n", r.adj);
}
void	printvertdownleft(t_info *infos)
{
	t_ray	r;
	// int		x;
	// int		y;

	r.x = infos->player.x;
	r.y = infos->player.y;
	r.adj = infos->blockmeter - fmod(r.y, infos->blockmeter);
	r.op = tan(fabs((180 - infos->player.angle) * M_PI / 180)) * r.adj;
	r.x -= r.op;
	r.y += r.adj;
	ft_putpixel(&infos->img, r.x, r.y, 0xFFFFFF);
	r.ya = infos->blockmeter;
	r.xa = infos->blockmeter / tan(fabs(90 - infos->player.angle) * M_PI / 180);
	continueline(&r, infos);
}

void	printhoridownleft(t_info *infos)
{
	t_ray	r;
	// int		x;
	// int		y;

	r.x = infos->player.x;
	r.y = infos->player.y;
	r.adj = fmod(r.x, infos->blockmeter);
	r.op = tan(fabs((270 - infos->player.angle) * M_PI / 180)) * r.adj;
	r.x -= r.adj;
	r.y += r.op;
	ft_putpixel(&infos->img, r.x, r.y, 0xFFFFFF);
	r.xa = -infos->blockmeter;
	r.ya = infos->blockmeter / tan(fabs(180 - infos->player.angle) * M_PI / 180);
	continueline(&r, infos);
}

void	printvertupleft(t_info *infos)
{
	t_ray	r;
	// int		x;
	// int		y;

	r.x = infos->player.x;
	r.y = infos->player.y;
	r.adj = fmod(r.y, infos->blockmeter);
	r.op = tan(fabs((360 - infos->player.angle) * M_PI / 180)) * r.adj;
	r.x -= r.op;
	r.y -= r.adj;
	ft_putpixel(&infos->img, r.x, r.y, 0xFF0000);
	r.ya = -infos->blockmeter;
	r.xa = -infos->blockmeter / tan(fabs(270 - infos->player.angle) * M_PI / 180);
	continueline(&r, infos);
}

void	printhoriupleft(t_info *infos)
{
	t_ray	r;
	// int		x;
	// int		y;

	r.x = infos->player.x;
	r.y = infos->player.y;
	r.adj = fmod(r.x, infos->blockmeter);
	r.op = tan(fabs((270 - infos->player.angle) * M_PI / 180)) * r.adj;
	r.x -= r.adj;
	r.y -= r.op;
	ft_putpixel(&infos->img, r.x, r.y, 0xFFFFFF);
}

void	printminimapblock(int y, int x, t_info *infos)
{
	int			ystart;
	int			xstart;
	int			yend;
	int			xend;
	static int	isfirst = 1;

	ystart = y * infos->blockmeter;
	xstart = x * infos->blockmeter;
	yend = ystart + infos->blockmeter;
	xend = xstart + infos->blockmeter;
	while (ystart < yend)
	{
		xstart = x * infos->blockmeter;
		while (xstart < xend)
		{
			if (infos->map[y][x] == '1')
				ft_putpixel(&infos->img, xstart, ystart, 0xFF0000);
			else if (ft_isin("NSWE", infos->map[y][x]) && isfirst)
			{
				infos->player.y = y * infos->blockmeter + infos->blockmeter / 2;
				infos->player.x = x * infos->blockmeter + infos->blockmeter / 2;
				ft_putpixel(&infos->img, xstart, ystart, 0xFFFFFF);
				if (infos->map[y][x] == 'N')
					infos->player.angle = 0;
				if (infos->map[y][x] == 'S')
					infos->player.angle = 180;
				if (infos->map[y][x] == 'E')
					infos->player.angle = 90;
				if (infos->map[y][x] == 'W')
					infos->player.angle = 270;
				isfirst = 0;
			}
			else
				ft_putpixel(&infos->img, xstart, ystart, 0xFFFFFF);
			if (!(xstart % infos->blockmeter) || !(ystart % infos->blockmeter))
				ft_putpixel(&infos->img, xstart, ystart, 0x000000);
			xstart++;
		}
		ystart++;
	}
}

int	printplayer(t_info *infos)
{
	int	x;
	int	y;

	x = (int)infos->player.x / infos->blockmeter;
	y = (int)infos->player.y / infos->blockmeter;
	if (infos->player.w && infos->map[y][x] != '1')
		infos->player.y -= infos->player.speed;
	if (infos->player.s && infos->map[y][x] != '1')
		infos->player.y += infos->player.speed;
	if (infos->player.a && infos->map[y][x] != '1')
		infos->player.x -= infos->player.speed;
	if (infos->player.d && infos->map[y][x] != '1')
		infos->player.x += infos->player.speed;
		// {pa-=5; pa=FixAng(pa); pdx=cos(degToRad(pa)); pdy=-sin(degToRad(pa));}
	if (infos->player.left)
	{
		if (infos->player.angle <= 0)
			infos->player.angle = 360;
		infos->player.angle--;
	}
	if (infos->player.right)
	{
		if (infos->player.angle >= 360)
			infos->player.angle = -1;
		infos->player.angle++;
	}
	ft_putpixel(&infos->img, infos->player.x, infos->player.y, 0x00FF00);
	return (1);
}

int	printminimap(t_info *infos)
{
	int	x;
	int	y;

	y = 0;
	while (y < infos->maxy)
	{
		x = 0;
		while (x < infos->maxx)
		{
			printminimapblock(y, x, infos);
			x++;
		}
		y++;
	}
	printplayer(infos);
	if (infos->player.angle > 0 && infos->player.angle < 90)
	{
		printvertupright(infos);
		printhoriupright(infos);
	}
	else if (infos->player.angle > 90 && infos->player.angle < 180)
	{
		printvertdownright(infos);
		printhoridownright(infos);
	}
	else if (infos->player.angle > 180 && infos->player.angle < 270)
	{
		printvertdownleft(infos);
		printhoridownleft(infos);
	}
	else if (infos->player.angle > 270 && infos->player.angle < 360)
	{
		printvertupleft(infos);
		printhoriupleft(infos);
	}
	mlx_put_image_to_window(infos->mlx, infos->win, infos->img.img, 0, 0);
	return (1);
}
