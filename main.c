/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 01:35:32 by ztouzri           #+#    #+#             */
/*   Updated: 2021/10/11 14:16:26 by ztouzri          ###   ########.fr       */
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
		infos->player.w = TRUE;
	}
	if (key == S)
	{
		infos->player.s = TRUE;
	}
	if (key == A)
	{
		infos->player.a = TRUE;
	}
	if (key == D)
	{
		infos->player.d = TRUE;
	}
	if (key == SHIFT)
		infos->player.speed = 2;
	if (key == ESC)
		destroy_window(infos);
	return (1);
}

int	keyrelease(int key, t_info *infos)
{
	if (key == W)
	{
		infos->player.w = FALSE;
	}
	if (key == S)
	{
		infos->player.s = FALSE;
	}
	if (key == A)
	{
		infos->player.a = FALSE;
	}
	if (key == D)
	{
		infos->player.d = FALSE;
	}
	if (key == SHIFT)
		infos->player.speed = 1;
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
			mlx_hook(infos.win, 02, 1L << 0, keypress, &infos);
			mlx_hook(infos.win, 03, 1L << 1, keyrelease, &infos);
			img.img = mlx_new_image(infos.mlx, 1920, 1080);
			img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
					&img.line_length, &img.endian);
			infos.img = img;
			infos.blockmeter = 50;
			infos.player.speed = 1;
			printminimap(&infos);
			mlx_loop_hook(infos.mlx, printminimap, &infos);
			mlx_loop(infos.mlx);
		}
		close(fd);
	}
	return (0);
}
