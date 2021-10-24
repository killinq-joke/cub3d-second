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

double	distance(t_ray *r, t_info *infos)
{
	return (sqrt(fabs(r->x - infos->player.x) + fabs(r->y - infos->player.y)));
}

double	distance2(t_bool vert, t_info *infos)
{
	if (vert)
		return (sqrt(fabs(infos->player.x - infos->player.rayvx) + fabs(infos->player.y - infos->player.rayvy)));
	else
		return (sqrt(fabs(infos->player.x - infos->player.rayhx) + fabs(infos->player.y - infos->player.rayhy)));
}

void	dda(t_info *infos, double rayx, double rayy)
{
	double	deltax;
	double	deltay;
	double	xinc;
	double	yinc;
	int		steps;
	int		i = 0;

	deltax = rayx - infos->player.x;
	deltay = rayy - infos->player.y;
	if (fabs(deltax) > fabs(deltay))
	{
		//if negative xinc que faire
		steps = round(fabs(deltax));
		xinc = 1;
		yinc = deltay / deltax;
	}
	else
	{
		steps = round(fabs(deltay));
		yinc = 1;
		xinc = deltax / deltay;
	}
	while (i < steps)
	{
		rayx += xinc;
		rayy += yinc;
		ft_putpixel(&infos->img, rayx, rayy, 0x0000FF);
		i++;
	}
}

void	continueline(t_bool vert, t_ray *r, t_info *infos)
{
	int		x;
	int		y;

	x = floor(r->x + 1) / infos->blockmeter;
	y = floor(r->y - 1) / infos->blockmeter;
	while (y > -1 && y < infos->maxy && x > -1 && x < infos->maxx && infos->map[y][x] == '0')
	{
		r->x += r->xa;
		r->y += r->ya;
		x = r->x / infos->blockmeter;
		y = r->y / infos->blockmeter;
		ft_putpixel(&infos->img, r->x, r->y, 0xFF0000);
	}
	if (vert)
	{
		infos->player.rayvx = r->x;
		infos->player.rayvy = r->y;
	}
	else
	{
		infos->player.rayhx = r->x;
		infos->player.rayhy = r->y;
	}
}

void	printvertupright(double angle, t_info *infos)
{
	t_ray	r;

	r.x = infos->player.x;
	r.y = infos->player.y;
	r.adj = fmod(r.y, infos->blockmeter);
	r.op = tan(angletorad(angle)) * r.adj;
	r.x += r.op;
	r.y -= r.adj;
	ft_putpixel(&infos->img, r.x, r.y, 0xFFFFFF);
	r.ya = -infos->blockmeter;
	r.xa = infos->blockmeter / tan(angletorad(fabs(angle - 90)));
	continueline(TRUE, &r, infos);
}

void	printhoriupright(double angle, t_info *infos)
{
	t_ray	r;

	r.x = infos->player.x;
	r.y = infos->player.y;
	r.adj = fabs(infos->blockmeter - fmod(r.x, infos->blockmeter));
	r.op = tan(angletorad(fabs(90 - angle))) * r.adj;
	r.x += r.adj;
	r.y -= r.op;
	ft_putpixel(&infos->img, r.x, r.y, 0x00FF00);
	r.xa = infos->blockmeter;
	r.ya = -infos->blockmeter / tan(angletorad(angle));
	continueline(FALSE, &r, infos);
}

void	printvertdownright(double angle, t_info *infos)
{
	t_ray	r;

	r.x = infos->player.x;
	r.y = infos->player.y;
	r.adj = infos->blockmeter - fmod(r.y, infos->blockmeter);
	r.op = tan(angletorad(fabs(180 - angle))) * r.adj;
	r.x += r.op;
	r.y += r.adj;
	ft_putpixel(&infos->img, r.x, r.y, 0xFFFFFF);
	r.ya = infos->blockmeter;
	r.xa = infos->blockmeter / tan(angletorad(fabs(90 - angle)));
	continueline(TRUE, &r, infos);
}

void	printhoridownright(double angle, t_info *infos)
{
	t_ray	r;

	r.x = infos->player.x;
	r.y = infos->player.y;
	r.adj = infos->blockmeter - fmod(r.x, infos->blockmeter);
	r.op = tan(angletorad(fabs(90 - angle))) * r.adj;
	r.x += r.adj;
	r.y += r.op;
	ft_putpixel(&infos->img, r.x, r.y, 0xFFFFFF);
	r.xa = infos->blockmeter;
	r.ya = -infos->blockmeter / tan(angletorad(angle));
	continueline(FALSE, &r, infos);
}

void	printvertdownleft(double angle, t_info *infos)
{
	t_ray	r;

	r.x = infos->player.x;
	r.y = infos->player.y;
	r.adj = infos->blockmeter - fmod(r.y, infos->blockmeter);
	r.op = tan(angletorad(fabs(180 - angle))) * r.adj;
	r.x -= r.op;
	r.y += r.adj;
	ft_putpixel(&infos->img, r.x, r.y, 0xFFFFFF);
	r.ya = infos->blockmeter;
	r.xa = infos->blockmeter / tan(angletorad(fabs(90 - angle)));
	continueline(TRUE, &r, infos);
}

void	printhoridownleft(double angle, t_info *infos)
{
	t_ray	r;

	r.x = infos->player.x;
	r.y = infos->player.y;
	r.adj = fmod(r.x, infos->blockmeter);
	r.op = tan(angletorad(fabs(270 - angle))) * r.adj;
	r.x -= r.adj;
	r.y += r.op;
	ft_putpixel(&infos->img, r.x, r.y, 0xFFFFFF);
	r.xa = -infos->blockmeter;
	r.ya = infos->blockmeter / tan(angletorad(fabs(180 - angle)));
	continueline(FALSE, &r, infos);
}

void	printvertupleft(double angle, t_info *infos)
{
	t_ray	r;

	r.x = infos->player.x;
	r.y = infos->player.y;
	r.adj = fmod(r.y, infos->blockmeter);
	r.op = tan(angletorad(fabs(360 - angle))) * r.adj;
	r.x -= r.op;
	r.y -= r.adj;
	ft_putpixel(&infos->img, r.x, r.y, 0xFF0000);
	r.ya = -infos->blockmeter;
	r.xa = -infos->blockmeter / tan(angletorad(fabs(270 - angle)));
	continueline(TRUE, &r, infos);
}

void	printhoriupleft(double angle, t_info *infos)
{
	t_ray	r;

	r.x = infos->player.x;
	r.y = infos->player.y;
	r.adj = fmod(r.x, infos->blockmeter);
	r.op = tan(angletorad(fabs(270 - angle))) * r.adj;
	r.x -= r.adj;
	r.y -= r.op;
	ft_putpixel(&infos->img, r.x, r.y, 0xFFFFFF);
	r.xa = -infos->blockmeter;
	r.ya = -infos->blockmeter / tan(angletorad(fabs(360 - angle)));
	continueline(FALSE, &r, infos);
}

void	printminimapblock(int y, int x, t_info *infos)
{
	int			ystart;
	int			xstart;
	int			yend;
	int			xend;

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
			else if (ft_isin("NSWE", infos->map[y][x]))
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
				infos->map[y][x] = '0';
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

	x = infos->player.x / infos->blockmeter;
	y = infos->player.y / infos->blockmeter;
	if (infos->player.w && infos->map[y][x] != '1')
	{
		infos->player.y -= cos(angletorad(infos->player.angle)) * infos->player.speed;
		infos->player.x += sin(angletorad(infos->player.angle)) * infos->player.speed;
	}
	if (infos->player.s && infos->map[y][x] != '1')
	{
		infos->player.y += cos(angletorad(infos->player.angle)) * infos->player.speed;
		infos->player.x -= sin(angletorad(infos->player.angle)) * infos->player.speed;
	}
	if (infos->player.a && infos->map[y][x] != '1')
	{
		infos->player.y -= sin(angletorad(infos->player.angle)) * infos->player.speed;
		infos->player.x -= cos(angletorad(infos->player.angle)) * infos->player.speed;
	}
	if (infos->player.d && infos->map[y][x] != '1')
	{
		infos->player.y += sin(angletorad(infos->player.angle)) * infos->player.speed;
		infos->player.x += cos(angletorad(infos->player.angle)) * infos->player.speed;
	}
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

void	printpoints(double angle, t_info *infos)
{
	if (angle > 0 && angle < 90)
	{
		printvertupright(angle, infos);
		printhoriupright(angle, infos);
	}
	else if (angle > 90 && angle < 180)
	{
		printvertdownright(angle, infos);
		printhoridownright(angle, infos);
	}
	else if (angle > 180 && angle < 270)
	{
		printvertdownleft(angle, infos);
		printhoridownleft(angle, infos);
	}
	else if (angle > 270 && angle < 360)
	{
		printvertupleft(angle, infos);
		printhoriupleft(angle, infos);
	}
}

void	printview(t_info *infos)
{
	double	i;
	double	angle;

	i = -30;
	while (i < 30)
	{
		angle = infos->player.angle + i;
		if (angle < 0)
			angle = 360 + angle;
		if (angle > 360)
			angle = angle - 360;
		printpoints(angle, infos);
		if (distance2(TRUE, infos) <= distance2(FALSE, infos))
			dda(infos, infos->player.rayvx, infos->player.rayvy);
		else
			dda(infos, infos->player.rayhx, infos->player.rayhy);
		i++;
	}
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
	printview(infos);
	mlx_put_image_to_window(infos->mlx, infos->win, infos->img.img, 0, 0);
	return (1);
}
