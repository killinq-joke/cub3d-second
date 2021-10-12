/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 20:42:29 by ztouzri           #+#    #+#             */
/*   Updated: 2021/10/12 14:52:25 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_putpixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

//CAH SOH TOA
// cos (angle) = adj / hyp
// sin (angle) = op / hyp
// tan (angle) = op / adj
void	printvert(t_info *infos)
{
	double	adj;
	double	op;

	adj = abs(infos->player.y - (infos->player.y - infos->player.y % infos->blockmeter));
	op = tan(infos->player.angle * M_PI / 180) * adj;
	ft_putpixel(&infos->img, infos->player.x + op, infos->player.y - infos->player.y % infos->blockmeter, 0x0000FF);
}

void	printhori(t_info *infos)
{
	double	adj;
	double	op;

	adj = abs(infos->blockmeter - infos->player.x % infos->blockmeter);
	op = tan(fabs(90 - infos->player.angle) * M_PI / 180) * adj;
	ft_putpixel(&infos->img, infos->player.x + adj, infos->player.y - op, 0x0000FF);
	printf("%d\n", infos->blockmeter - infos->player.x % infos->blockmeter);
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
				isfirst = 0;
			}
			else
				ft_putpixel(&infos->img, xstart, ystart, 0xFFFFFF);
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
		infos->player.y -= infos->player.speed;
	if (infos->player.s && infos->map[y][x] != '1')
		infos->player.y += infos->player.speed;
	if (infos->player.a && infos->map[y][x] != '1')
		infos->player.x -= infos->player.speed;
	if (infos->player.d && infos->map[y][x] != '1')
		infos->player.x += infos->player.speed;
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
	printvert(infos);
	printhori(infos);
	mlx_put_image_to_window(infos->mlx, infos->win, infos->img.img, 0, 0);
	return (1);
}
