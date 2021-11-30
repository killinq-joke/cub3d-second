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

	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
		dst = (char *)img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

// void	ft_putimgpixel(unsigned int src, t_img *to, int x, int y)
// {
// 	char	*dst;

// 	if (x >= 0 && x < to->width && y >= 0 && y < to->height)
// 	{
// 		dst = (char *)to->addr + (y * to->line_length + x * (to->bits_per_pixel / 8));
// 		*(unsigned int *)dst = src;
// 	}
// }

double	angletorad(double angle)
{
	return (angle * M_PI / 180.0);
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

void	dda(t_info *infos, double rayx, double rayy, t_bool vert)
{
	int i;

	infos->dx = rayx - infos->player.x;
	infos->dy = rayy - infos->player.y;
	infos->steps = fabs(infos->dx) > fabs(infos->dy) ? fabs(infos->dx) : fabs(infos->dy);
	infos->xinc = infos->dx / infos->steps;
	infos->yinc = infos->dy / infos->steps;
	infos->x = infos->player.x;
	infos->y = infos->player.y;
	i = 0;
    while (i <= infos->steps)
    {
		if (vert)
			ft_putpixel(&infos->minimap, round(infos->x) * infos->scale, round(infos->y) * infos->scale, 0x00FF00);
		else
			ft_putpixel(&infos->minimap, round(infos->x) * infos->scale, round(infos->y) * infos->scale, 0x0000FF);
        infos->x += infos->xinc;
        infos->y += infos->yinc;
		i++;
    }
	if (vert)
		infos->offset = fmod(rayy, SIZE);
        // infos->offset = fmod(rayy / SIZE, 1.0) * 64.0;
	else
		infos->offset = fmod(rayx, SIZE);
}

void	printvertupright(double angle, t_info *infos)
{
	infos->r.x = infos->player.x;
	infos->r.y = infos->player.y;
	infos->r.adj = fmod(infos->r.y, SIZE);
	infos->r.op = tan(angletorad(angle)) * infos->r.adj;
	infos->r.x += infos->r.op;
	infos->r.y -= infos->r.adj;
	infos->r.ya = -SIZE;
	infos->r.xa = SIZE / tan(angletorad(fabs(angle - 90)));
	infos->mapx = infos->r.x / SIZE;
	infos->mapy = infos->r.y / SIZE - 0.000001;
	while (infos->mapx > 0 && infos->mapx < infos->maxx && infos->mapy > 0 && infos->mapy < infos->maxy && infos->map[infos->mapy][infos->mapx] == '0')
	{
		infos->r.x += infos->r.xa;
		infos->r.y += infos->r.ya;
		infos->mapx = infos->r.x / SIZE;
		infos->mapy = infos->r.y / SIZE - 0.000001;
	}
	infos->player.rayvx = infos->r.x;
	infos->player.rayvy = infos->r.y;
}

void	printhoriupright(double angle, t_info *infos)
{
	infos->r.x = infos->player.x;
	infos->r.y = infos->player.y;
	infos->r.adj = fabs(SIZE - fmod(infos->r.x, SIZE));
	infos->r.op = tan(angletorad(fabs(90 - angle))) * infos->r.adj;
	infos->r.x += infos->r.adj;
	infos->r.y -= infos->r.op;
	infos->r.xa = SIZE;
	infos->r.ya = -SIZE / tan(angletorad(angle));
	infos->mapx = infos->r.x / SIZE + 0.000002;
	infos->mapy = infos->r.y / SIZE + 0.000002;
	while (infos->mapx > 0 && infos->mapx < infos->maxx && infos->mapy > 0 && infos->mapy < infos->maxy && infos->map[infos->mapy][infos->mapx] == '0')
	{
		infos->r.x += infos->r.xa;
		infos->r.y += infos->r.ya;
		infos->mapx = infos->r.x / SIZE + 0.000002;
		infos->mapy = infos->r.y / SIZE + 0.000002;
	}
	infos->player.rayhx = infos->r.x;
	infos->player.rayhy = infos->r.y;
}

void	printvertdownright(double angle, t_info *infos)
{
	infos->r.x = infos->player.x;
	infos->r.y = infos->player.y;
	infos->r.adj = SIZE - fmod(infos->r.y, SIZE);
	infos->r.op = tan(angletorad(fabs(180 - angle))) * infos->r.adj;
	infos->r.x += infos->r.op;
	infos->r.y += infos->r.adj;
	infos->r.ya = SIZE;
	infos->r.xa = SIZE / tan(angletorad(fabs(90 - angle)));
	infos->mapx = infos->r.x / SIZE - 0.000001;
	infos->mapy = infos->r.y / SIZE;
	while (infos->mapx > 0 && infos->mapx < infos->maxx && infos->mapy > 0 && infos->mapy < infos->maxy && infos->map[infos->mapy][infos->mapx] == '0')
	{
		infos->r.x += infos->r.xa;
		infos->r.y += infos->r.ya;
		infos->mapx = infos->r.x / SIZE - 0.000001;
		infos->mapy = infos->r.y / SIZE;
	}
	infos->player.rayvx = infos->r.x;
	infos->player.rayvy = infos->r.y;
}

void	printhoridownright(double angle, t_info *infos)
{
	infos->r.x = infos->player.x;
	infos->r.y = infos->player.y;
	infos->r.adj = SIZE - fmod(infos->r.x, SIZE);
	infos->r.op = tan(angletorad(fabs(90 - angle))) * infos->r.adj;
	infos->r.x += infos->r.adj;
	infos->r.y += infos->r.op;
	infos->r.xa = SIZE;
	infos->r.ya = -SIZE / tan(angletorad(angle));
	infos->mapx = infos->r.x / SIZE + 0.000001;
	infos->mapy = infos->r.y / SIZE + 0.000001;
	while (infos->mapx > 0 && infos->mapx < infos->maxx && infos->mapy > 0 && infos->mapy < infos->maxy && infos->map[infos->mapy][infos->mapx] == '0')
	{
		infos->r.x += infos->r.xa;
		infos->r.y += infos->r.ya;
		infos->mapx = infos->r.x / SIZE + 0.000001;
		infos->mapy = infos->r.y / SIZE + 0.000001;
	}
	infos->player.rayhx = infos->r.x;
	infos->player.rayhy = infos->r.y;
}

void	printvertdownleft(double angle, t_info *infos)
{
	infos->r.x = infos->player.x;
	infos->r.y = infos->player.y;
	infos->r.adj = SIZE - fmod(infos->r.y, SIZE);
	infos->r.op = tan(angletorad(fabs(180 - angle))) * infos->r.adj;
	infos->r.x -= infos->r.op;
	infos->r.y += infos->r.adj;
	infos->r.ya = SIZE;
	infos->r.xa = SIZE / tan(angletorad(fabs(90 - angle)));
	infos->mapx = infos->r.x / SIZE;
	infos->mapy = infos->r.y / SIZE;
	while (infos->mapx > 0 && infos->mapx < infos->maxx && infos->mapy > 0 && infos->mapy < infos->maxy && infos->map[infos->mapy][infos->mapx] == '0')
	{
		infos->r.x += infos->r.xa;
		infos->r.y += infos->r.ya;
		infos->mapx = infos->r.x / SIZE;
		infos->mapy = infos->r.y / SIZE;
	}
	infos->player.rayvx = infos->r.x;
	infos->player.rayvy = infos->r.y;
}

void	printhoridownleft(double angle, t_info *infos)
{
	infos->r.x = infos->player.x;
	infos->r.y = infos->player.y;
	infos->r.adj = fmod(infos->r.x, SIZE);
	infos->r.op = tan(angletorad(fabs(270 - angle))) * infos->r.adj;
	infos->r.x -= infos->r.adj;
	infos->r.y += infos->r.op;
	infos->r.xa = -SIZE;
	infos->r.ya = SIZE / tan(angletorad(fabs(180 - angle)));
	infos->mapx = infos->r.x / SIZE - 1.0;
	infos->mapy = infos->r.y / SIZE;
	while (infos->mapx > 0 && infos->mapx < infos->maxx && infos->mapy > 0 && infos->mapy < infos->maxy && infos->map[infos->mapy][infos->mapx] == '0')
	{
		infos->r.x += infos->r.xa;
		infos->r.y += infos->r.ya;
		infos->mapx = infos->r.x / SIZE - 1.0;
		infos->mapy = infos->r.y / SIZE;
	}
	infos->player.rayhx = infos->r.x;
	infos->player.rayhy = infos->r.y;
}

void	printvertupleft(double angle, t_info *infos)
{
	infos->r.x = infos->player.x;
	infos->r.y = infos->player.y;
	infos->r.adj = fmod(infos->r.y, SIZE);
	infos->r.op = tan(angletorad(fabs(360 - angle))) * infos->r.adj;
	infos->r.x -= infos->r.op;
	infos->r.y -= infos->r.adj;
	infos->r.ya = -SIZE;
	infos->r.xa = -SIZE / tan(angletorad(fabs(270 - angle)));
	infos->mapx = infos->r.x / SIZE;
	infos->mapy = infos->r.y / SIZE - 0.000001;
	while (infos->mapx > 0 && infos->mapx < infos->maxx && infos->mapy > 0 && infos->mapy < infos->maxy && infos->map[infos->mapy][infos->mapx] == '0')
	{
		infos->r.x += infos->r.xa;
		infos->r.y += infos->r.ya;
		infos->mapx = infos->r.x / SIZE;
		infos->mapy = infos->r.y / SIZE - 0.000001;
	}
	infos->player.rayvx = infos->r.x;
	infos->player.rayvy = infos->r.y;
}

void	printhoriupleft(double angle, t_info *infos)
{
	infos->r.x = infos->player.x;
	infos->r.y = infos->player.y;
	infos->r.adj = fmod(infos->r.x, SIZE);
	infos->r.op = tan(angletorad(fabs(270 - angle))) * infos->r.adj;
	infos->r.x -= infos->r.adj;
	infos->r.y -= infos->r.op;
	infos->r.xa = -SIZE;
	infos->r.ya = -SIZE / tan(angletorad(fabs(360 - angle)));
	infos->mapx = infos->r.x / SIZE - 0.000001;
	infos->mapy = infos->r.y / SIZE - 0.000001;
	while (infos->mapx > 0 && infos->mapx < infos->maxx && infos->mapy > 0 && infos->mapy < infos->maxy && infos->map[infos->mapy][infos->mapx] == '0')
	{
		infos->r.x += infos->r.xa;
		infos->r.y += infos->r.ya;
		infos->mapx = infos->r.x / SIZE - 0.000001;
		infos->mapy = infos->r.y / SIZE - 0.000001;
	}
	infos->player.rayhx = infos->r.x;
	infos->player.rayhy = infos->r.y;
}

void	printup(t_info *infos)
{
	infos->r.x = infos->player.x;
	infos->r.y = infos->player.y;
	infos->r.adj = fmod(infos->r.y, SIZE);
	infos->r.y -= infos->r.adj;
	infos->r.ya = -SIZE;
	infos->mapx = infos->r.x / SIZE;
	infos->mapy = infos->r.y / SIZE - 0.000001;
	while (infos->mapx > 0 && infos->mapx < infos->maxx && infos->mapy > 0 && infos->mapy < infos->maxy && infos->map[infos->mapy][infos->mapx] == '0')
	{
		infos->r.y += infos->r.ya;
		infos->mapy = infos->r.y / SIZE - 0.000001;
	}
	infos->player.rayvx = infos->r.x;
	infos->player.rayvy = infos->r.y;
}

void	printright(t_info *infos)
{
	infos->r.x = infos->player.x;
	infos->r.y = infos->player.y;
	infos->r.adj = SIZE - fmod(infos->r.x, SIZE);
	infos->r.x += infos->r.adj;
	infos->r.xa = SIZE;
	infos->mapx = infos->r.x / SIZE;
	infos->mapy = infos->r.y / SIZE;
	while (infos->mapx > 0 && infos->mapx < infos->maxx && infos->mapy > 0 && infos->mapy < infos->maxy && infos->map[infos->mapy][infos->mapx] == '0')
	{
		infos->r.x += infos->r.xa;
		infos->mapx = infos->r.x / SIZE;
		infos->mapy = infos->r.y / SIZE;
	}
	infos->player.rayhx = infos->r.x;
	infos->player.rayhy = infos->r.y;
}

void	printdown(t_info *infos)
{
	infos->r.x = infos->player.x;
	infos->r.y = infos->player.y;
	infos->r.adj = SIZE - fmod(infos->r.y, SIZE);
	infos->r.y += infos->r.adj;
	infos->r.ya = SIZE;
	infos->mapx = infos->r.x / SIZE;
	infos->mapy = infos->r.y / SIZE;
	while (infos->mapx > 0 && infos->mapx < infos->maxx && infos->mapy > 0 && infos->mapy < infos->maxy && infos->map[infos->mapy][infos->mapx] == '0')
	{
		infos->r.y += infos->r.ya;
		infos->mapy = infos->r.y / SIZE;
	}
	infos->player.rayvx = infos->r.x;
	infos->player.rayvy = infos->r.y;
}

void	printleft(t_info *infos)
{
	infos->r.x = infos->player.x;
	infos->r.y = infos->player.y;
	infos->r.adj = fmod(infos->r.x, SIZE);
	infos->r.x -= infos->r.adj;
	infos->r.xa = -SIZE;
	infos->mapx = infos->r.x / SIZE - 0.000001;
	infos->mapy = infos->r.y / SIZE;
	while (infos->mapx > 0 && infos->mapx < infos->maxx && infos->mapy > 0 && infos->mapy < infos->maxy && infos->map[infos->mapy][infos->mapx] == '0')
	{
		infos->r.x += infos->r.xa;
		infos->mapx = infos->r.x / SIZE - 0.000001;
		infos->mapy = infos->r.y / SIZE;
	}
	infos->player.rayhx = infos->r.x;
	infos->player.rayhy = infos->r.y;
}

void	printminimapblock(int y, int x, t_info *infos)
{
	int			ystart;
	int			xstart;
	int			yend;
	int			xend;

	ystart = y * SIZE * infos->scale;
	xstart = x * SIZE * infos->scale;
	yend = ystart + SIZE * infos->scale;
	xend = xstart + SIZE * infos->scale;
	while (ystart < yend)
	{
		xstart = x * SIZE * infos->scale;
		while (xstart < xend)
		{
			if (ft_isin("1 ", infos->map[y][x]))
				ft_putpixel(&infos->minimap, xstart, ystart, 0x555555);
			else
				ft_putpixel(&infos->minimap, xstart, ystart, 0xFF0000);
			if (!(fmod(xstart, SIZE * infos->scale)) || !(fmod(ystart, SIZE * infos->scale)))
				ft_putpixel(&infos->minimap, xstart, ystart, 0x000000);
			xstart++;
		}
		ystart++;
	}
}

int	printplayer(t_info *infos)
{
	int	x;
	int	y;

	x = infos->player.x / SIZE;
	y = infos->player.y / SIZE;
	if (infos->player.w)
	{
		y = (infos->player.y - cos(angletorad(infos->player.angle)) * infos->player.speed) / SIZE;
		x = (infos->player.x + sin(angletorad(infos->player.angle)) * infos->player.speed) / SIZE;
		if (infos->map[y][x] == '0')
		{
			infos->player.y -= cos(angletorad(infos->player.angle)) * infos->player.speed;
			infos->player.x += sin(angletorad(infos->player.angle)) * infos->player.speed;
		}
	}
	if (infos->player.s)
	{
		y = (infos->player.y + cos(angletorad(infos->player.angle)) * infos->player.speed) / SIZE;
		x = (infos->player.x - sin(angletorad(infos->player.angle)) * infos->player.speed) / SIZE;
		if (infos->map[y][x] == '0')
		{
			infos->player.y += cos(angletorad(infos->player.angle)) * infos->player.speed;
			infos->player.x -= sin(angletorad(infos->player.angle)) * infos->player.speed;
		}
	}
	if (infos->player.a)
	{
		y = (infos->player.y - sin(angletorad(infos->player.angle)) * infos->player.speed) / SIZE;
		x = (infos->player.x - cos(angletorad(infos->player.angle)) * infos->player.speed) / SIZE;
		if (infos->map[y][x] == '0')
		{
			infos->player.y -= sin(angletorad(infos->player.angle)) * infos->player.speed;
			infos->player.x -= cos(angletorad(infos->player.angle)) * infos->player.speed;
		}
	}
	if (infos->player.d)
	{
		y = (infos->player.y + sin(angletorad(infos->player.angle)) * infos->player.speed) / SIZE;
		x = (infos->player.x + cos(angletorad(infos->player.angle)) * infos->player.speed) / SIZE;
		if (infos->map[y][x] == '0')
		{
			infos->player.y += sin(angletorad(infos->player.angle)) * infos->player.speed;
			infos->player.x += cos(angletorad(infos->player.angle)) * infos->player.speed;
		}
	}
	if (infos->player.left)
	{
		if (infos->player.angle <= 0)
			infos->player.angle = 360;
		infos->player.angle -= 3;
	}
	if (infos->player.right)
	{
		if (infos->player.angle >= 360)
			infos->player.angle = -1;
		infos->player.angle += 3;
	}
	// ft_putpixel(&infos->img, infos->player.x, infos->player.y, 0x00FF00);
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
	else if (angle == 0)
		printup(infos);
	else if (angle == 90)
		printright(infos);
	else if (angle == 180)
		printdown(infos);
	else if (angle == 270)
		printleft(infos);
}

void	showvertline(t_info *infos, double i, double distance)
{
	double	x;
	int		y;
	double	start;
	double	j;
	double	end;

	distance *= cos(angletorad(30 - i));
	start = HEIGHT / 2 - (SIZE / distance * WIDTH / 2 / tan(angletorad(30)) / 2);
	end = HEIGHT / 2 + (SIZE / distance * WIDTH / 2 / tan(angletorad(30)) / 2);
	x = round(i * WIDTH / 60.0);
	y = 0;
	while (y < start)
	{
		ft_putpixel(&infos->img, x, y, infos->c);
		y++;
	}
	j = 0;
	while (j < end - start)
	{
		if (infos->side == NORTH)
		{
			int *a = (int *)infos->xpmno.addr;
			ft_putpixel(&infos->img, x, j + start, a[(int)(j / (end - start) * infos->xpmno.height * infos->xpmno.width + infos->offset / SIZE * infos->xpmno.height)]);
			printf("o/s*h == %f width == %d height == %d\n", infos->offset / SIZE * infos->xpmno.height, infos->xpmno.width, infos->xpmno.height);
		}
		else if (infos->side == SOUTH)
			ft_putpixel(&infos->img, x, j + start, 0xFFFFFF);
		else if (infos->side == WEST)
			ft_putpixel(&infos->img, x, j + start, 0xFFFFFF);
		else
			ft_putpixel(&infos->img, x, j + start, 0xFFFFFF);
		j++;
	}
	y = end;
	while (y < HEIGHT)
	{
		ft_putpixel(&infos->img, x, y, infos->f);
		y++;
	}
}

void	showfps(t_info *infos)
{
	double	i;
	double	angle;

	i = 29;
	while (i < 30)
	{
		angle = infos->player.angle + i - 30;
		if (angle < 0.0)
			angle = 360 + angle;
		if (angle >= 360)
			angle = angle - 360;
		printpoints(angle, infos);
		if (distance2(TRUE, infos) < distance2(FALSE, infos))
		{
			if ((angle > 270 && angle <= 360) || (angle >= 0 && angle < 90))
				infos->side = NORTH;
			else
				infos->side = SOUTH;
			dda(infos, infos->player.rayvx, infos->player.rayvy, TRUE);
			infos->offset = fmod(infos->player.rayvx, SIZE);
			showvertline(infos, i, distance2(TRUE, infos));
		}
		else
		{
			if (angle > 0 && angle < 180)
				infos->side = EAST;
			else
				infos->side = WEST;
			dda(infos, infos->player.rayhx, infos->player.rayhy, FALSE);
			infos->offset = fmod(infos->player.rayhy, SIZE);
			showvertline(infos, i, distance2(FALSE, infos));
		}
		i += 60.0 / WIDTH;
	}
}

int	printminimap(t_info *infos)
{
	int	x;
	int	y;

	printplayer(infos);
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
	showfps(infos);
	mlx_put_image_to_window(infos->mlx, infos->win, infos->img.img, 0, 0);
	mlx_put_image_to_window(infos->mlx, infos->win, infos->minimap.img, 0, 0);
	// printf("\n", infos->xpmno.img);
	mlx_put_image_to_window(infos->mlx, infos->win, infos->xpmno.img, 0, 0);
	return (1);
}
