/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 01:35:32 by ztouzri           #+#    #+#             */
/*   Updated: 2021/10/07 22:12:30 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	destroy_window(t_info *infos)
{
	mlx_destroy_window(infos->mlx, infos->win);
	freeinfo(*infos);
	exit(0);
	return (1);
}

int	keypress(int key, t_info *infos)
{
	if (key == W)
	{
		infos->player.speed = 1;
	}
	if (key == S)
	{
		infos->player.speed = 1;
	}
	if (key == A)
	{
		infos->player.speed = 1;
	}
	if (key == D)
	{
		infos->player.speed = 1;
	}
	if (key == ESC)
		destroy_window(infos);
	return (1);
}

void	ft_putpixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	printminimapblock(int y, int x)
{
	int	ymax;
	int	xmax;

	ymax = y + 50;
	xmax = x + 50;
	while (y < ymax)
	{
		while (x < xmax)
		{
			ft_putpixel(&infos->img, x, y, 0xFFFFFF);
			x++;
		}
		y++;
	}
}

int	printminimap(t_info *infos)
{
	int	x;
	int	y;

	while (y < infos->)
	{
		while (x < infos->)
		{
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(infos->mlx, infos->win, infos->img.img, 0, 0);
	return (1);
}

int	main(int ac, char **av)
{
	int		fd;
	t_info	infos;
	t_img	img;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd != -1)
		{
			infos = parsinfo(fd, av[1]);
			if (!infos.c || !infos.ea
				|| !infos.f || !infos.map
				|| !infos.no || !infos.so
				|| !infos.we)
			{
				printf("Error life\n");
				return (0);
			}
			infos.mlx = mlx_init();
			infos.win = mlx_new_window(infos.mlx, 1920, 1080, "cub3D");
			mlx_hook(infos.win, 17, 0L, destroy_window, &infos);
			mlx_hook(infos.win, 02, 1L<<0, keypress, &infos);
			img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
					&img.line_length, &img.endian);
			img.img = mlx_new_image(infos.mlx, 1920, 1080);
			infos.img = img;
			mlx_loop_hook(infos.mlx, printminimap, &infos);
			mlx_loop(infos.mlx);
		}
		close(fd);
	}
	return (0);
}
