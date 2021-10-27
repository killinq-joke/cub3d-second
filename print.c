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
	return (sqrt(pow(r->x - infos->player.x, 2) + pow(r->y - infos->player.y, 2)));
}

double	distance2(t_bool vert, t_info *infos)
{
	if (vert)
		return (sqrt(pow(infos->player.x - infos->player.rayvx, 2) + pow(infos->player.y - infos->player.rayvy, 2)));
	else
		return (sqrt(pow(infos->player.x - infos->player.rayhx, 2) + pow(infos->player.y - infos->player.rayhy, 2)));
}

// void	dda(t_info *infos, double rayx, double rayy)
// {
// 	double	deltax;
// 	double	deltay;
// 	double	xinc;
// 	double	yinc;
// 	double	steps;
// 	int		i = 0;

// 	deltax = rayx - infos->player.x;
// 	deltay = rayy - infos->player.y;
// 	if (infos->player.angle >= 90 && infos->player.angle <= 270)
// 	{
// 		deltax = infos->player.x - rayx;
// 		deltay = infos->player.y - rayy;
// 	}
// 	if (fabs(deltax) > fabs(deltay))
// 	{
// 		//if negative xinc que faire
// 		steps = round(fabs(deltax));
// 		xinc = deltax / steps;
// 		yinc = deltay / deltax;
// 	}
// 	else
// 	{
// 		steps = round(fabs(deltay));
// 		yinc = deltay / steps;
// 		xinc = deltax / deltay;
// 	}
// 	while (i < steps)
// 	{
// 		rayx += xinc;
// 		rayy += yinc;
// 		ft_putpixel(&infos->img, rayx, rayy, 0x0000FF);
// 		i++;
// 	}
// }

void	dda(t_info *infos, double rayx, double rayy, t_bool vert)
{
	int i;

	infos->dx = rayx - infos->player.x;
	infos->dy = rayy - infos->player.y;
	infos->steps = fabs(infos->dx) > fabs(infos->dy) ? fabs(infos->dx) : fabs(infos->dy);
	infos->xinc = infos->dx / (double)infos->steps;
	infos->yinc = infos->dy / (double)infos->steps;
	infos->x = infos->player.x;
	infos->y = infos->player.y;
	i = 0;
    while (i <= infos->steps)
    {
		if (vert)
			ft_putpixel(&infos->img, round(infos->x), round(infos->y), 0x00FF00);
		else
			ft_putpixel(&infos->img, round(infos->x), round(infos->y), 0x0000FF);
        infos->x += infos->xinc;
        infos->y += infos->yinc;
		i++;
    }
}

void	printvertupright(double angle, t_info *infos)
{
	infos->r.x = infos->player.x;
	infos->r.y = infos->player.y;
	infos->r.adj = fmod(infos->r.y, infos->blockmeter);
	infos->r.op = tan(angletorad(angle)) * infos->r.adj;
	infos->r.x += infos->r.op;
	infos->r.y -= infos->r.adj;
	ft_putpixel(&infos->img, infos->r.x, infos->r.y, 0x00FF00);
	infos->r.ya = -infos->blockmeter;
	infos->r.xa = infos->blockmeter / tan(angletorad(fabs(angle - 90)));
	int	x;
	int	y;

	x = infos->r.x / infos->blockmeter;
	y = infos->r.y / infos->blockmeter;
	while (x > 0 && x < infos->mapx && y > 0 && y < infos->mapy)
	{
		ft_putpixel(&infos->img, x, y, 0x00FF00);
		infos->r.x += infos->r.xa;
		infos->r.y += infos->r.ya;
		x = infos->r.x / infos->blockmeter;
		y = infos->r.y / infos->blockmeter;
		printf("x == %d\n", x);
	}
}

void	printhoriupright(double angle, t_info *infos)
{
	infos->r.x = infos->player.x;
	infos->r.y = infos->player.y;
	infos->r.adj = fabs(infos->blockmeter - fmod(infos->r.x, infos->blockmeter));
	infos->r.op = tan(angletorad(fabs(90 - angle))) * infos->r.adj;
	infos->r.x += infos->r.adj;
	infos->r.y -= infos->r.op - 1;
	ft_putpixel(&infos->img, infos->r.x, infos->r.y, 0xFFFF00);
	infos->r.xa = infos->blockmeter;
	infos->r.ya = -infos->blockmeter / tan(angletorad(angle));
}

void	printvertdownright(double angle, t_info *infos)
{
	infos->r.x = infos->player.x;
	infos->r.y = infos->player.y;
	infos->r.adj = infos->blockmeter - fmod(infos->r.y, infos->blockmeter);
	infos->r.op = tan(angletorad(fabs(180 - angle))) * infos->r.adj;
	infos->r.x += infos->r.op;
	infos->r.y += infos->r.adj;
	ft_putpixel(&infos->img, infos->r.x, infos->r.y, 0x00FF00);
	infos->r.ya = infos->blockmeter;
	infos->r.xa = infos->blockmeter / tan(angletorad(fabs(90 - angle)));
}

void	printhoridownright(double angle, t_info *infos)
{
	infos->r.x = infos->player.x;
	infos->r.y = infos->player.y;
	infos->r.adj = infos->blockmeter - fmod(infos->r.x, infos->blockmeter);
	infos->r.op = tan(angletorad(fabs(90 - angle))) * infos->r.adj;
	infos->r.x += infos->r.adj;
	infos->r.y += infos->r.op;
	ft_putpixel(&infos->img, infos->r.x, infos->r.y, 0xFFFF00);
	infos->r.xa = infos->blockmeter;
	infos->r.ya = -infos->blockmeter / tan(angletorad(angle));
}

void	printvertdownleft(double angle, t_info *infos)
{
	infos->r.x = infos->player.x;
	infos->r.y = infos->player.y;
	infos->r.adj = infos->blockmeter - fmod(infos->r.y, infos->blockmeter);
	infos->r.op = tan(angletorad(fabs(180 - angle))) * infos->r.adj;
	infos->r.x -= infos->r.op;
	infos->r.y += infos->r.adj;
	ft_putpixel(&infos->img, infos->r.x, infos->r.y, 0x00FF00);
	infos->r.ya = infos->blockmeter;
	infos->r.xa = infos->blockmeter / tan(angletorad(fabs(90 - angle)));
}

void	printhoridownleft(double angle, t_info *infos)
{
	infos->r.x = infos->player.x;
	infos->r.y = infos->player.y;
	infos->r.adj = fmod(infos->r.x, infos->blockmeter);
	infos->r.op = tan(angletorad(fabs(270 - angle))) * infos->r.adj;
	infos->r.x -= infos->r.adj;
	infos->r.y += infos->r.op;
	ft_putpixel(&infos->img, infos->r.x, infos->r.y, 0xFFFF00);
	infos->r.xa = -infos->blockmeter;
	infos->r.ya = infos->blockmeter / tan(angletorad(fabs(180 - angle)));
}

void	printvertupleft(double angle, t_info *infos)
{
	infos->r.x = infos->player.x;
	infos->r.y = infos->player.y;
	infos->r.adj = fmod(infos->r.y, infos->blockmeter);
	infos->r.op = tan(angletorad(fabs(360 - angle))) * infos->r.adj;
	infos->r.x -= infos->r.op;
	infos->r.y -= infos->r.adj;
	ft_putpixel(&infos->img, infos->r.x, infos->r.y, 0x00FF00);
	infos->r.ya = -infos->blockmeter;
	infos->r.xa = -infos->blockmeter / tan(angletorad(fabs(270 - angle)));
}

void	printhoriupleft(double angle, t_info *infos)
{
	infos->r.x = infos->player.x;
	infos->r.y = infos->player.y;
	infos->r.adj = fmod(infos->r.x, infos->blockmeter);
	infos->r.op = tan(angletorad(fabs(270 - angle))) * infos->r.adj;
	infos->r.x -= infos->r.adj;
	infos->r.y -= infos->r.op - 1;
	ft_putpixel(&infos->img, infos->r.x, infos->r.y, 0xFFFF00);
	infos->r.xa = -infos->blockmeter;
	infos->r.ya = -infos->blockmeter / tan(angletorad(fabs(360 - angle)));
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
				ft_putpixel(&infos->img, xstart, ystart, 0x555555);
			else if (ft_isin("NSWE", infos->map[y][x]))
			{
				infos->player.y = y * infos->blockmeter + infos->blockmeter / 2;
				infos->player.x = x * infos->blockmeter + infos->blockmeter / 2;
				ft_putpixel(&infos->img, xstart, ystart, 0xAA5500);
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
				ft_putpixel(&infos->img, xstart, ystart, 0xFF0000);
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
		x = infos->player.x / infos->blockmeter;
		y = infos->player.y / infos->blockmeter;
		if (infos->map[y][x] == '1')
		{
			infos->player.y += cos(angletorad(infos->player.angle)) * infos->player.speed;
			infos->player.x -= sin(angletorad(infos->player.angle)) * infos->player.speed;
		}
	}
	if (infos->player.s && infos->map[y][x] != '1')
	{
		infos->player.y += cos(angletorad(infos->player.angle)) * infos->player.speed;
		infos->player.x -= sin(angletorad(infos->player.angle)) * infos->player.speed;
		x = infos->player.x / infos->blockmeter;
		y = infos->player.y / infos->blockmeter;
		if (infos->map[y][x] == '1')
		{
			infos->player.y -= cos(angletorad(infos->player.angle)) * infos->player.speed;
			infos->player.x += sin(angletorad(infos->player.angle)) * infos->player.speed;
		}
	}
	if (infos->player.a && infos->map[y][x] != '1')
	{
		infos->player.y -= sin(angletorad(infos->player.angle)) * infos->player.speed;
		infos->player.x -= cos(angletorad(infos->player.angle)) * infos->player.speed;
		x = infos->player.x / infos->blockmeter;
		y = infos->player.y / infos->blockmeter;
		if (infos->map[y][x] == '1')
		{
			infos->player.y += sin(angletorad(infos->player.angle)) * infos->player.speed;
			infos->player.x += cos(angletorad(infos->player.angle)) * infos->player.speed;
		}
	}
	if (infos->player.d && infos->map[y][x] != '1')
	{
		infos->player.y += sin(angletorad(infos->player.angle)) * infos->player.speed;
		infos->player.x += cos(angletorad(infos->player.angle)) * infos->player.speed;
		x = infos->player.x / infos->blockmeter;
		y = infos->player.y / infos->blockmeter;
		if (infos->map[y][x] == '1')
		{
			infos->player.y -= sin(angletorad(infos->player.angle)) * infos->player.speed;
			infos->player.x -= cos(angletorad(infos->player.angle)) * infos->player.speed;
		}
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

	i = -180;
	while (i < 180)
	{
		angle = infos->player.angle + i;
		if (angle < 0)
			angle = 360 + angle;
		if (angle > 360)
			angle = angle - 360;
		printpoints(angle, infos);
		if (distance2(TRUE, infos) <= distance2(FALSE, infos))
			dda(infos, infos->player.rayvx, infos->player.rayvy, TRUE);
		else
			dda(infos, infos->player.rayhx, infos->player.rayhy, FALSE);
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
	printpoints(infos->player.angle, infos);
	// if (distance2(TRUE, infos) <= distance2(FALSE, infos))
	// 	dda(infos, infos->player.rayvx, infos->player.rayvy);
	// else
	// 	dda(infos, infos->player.rayhx, infos->player.rayhy);
	mlx_put_image_to_window(infos->mlx, infos->win, infos->img.img, 0, 0);
	return (1);
}
