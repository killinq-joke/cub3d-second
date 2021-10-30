/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 01:35:32 by ztouzri           #+#    #+#             */
/*   Updated: 2021/10/30 17:05:18 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init(int fd, char *windowname, t_info *infos)
{
	infos = parsinfo(fd, windowname, infos);
	if (!infos->c || !infos->ea
		|| !infos->f || !infos->map
		|| !infos->no || !infos->so
		|| !infos->we)
	{
		printf("Error\nInvalid Infos\n");
		exit(1);
	}
	infos->mlx = mlx_init();
	infos->win = mlx_new_window(infos->mlx, WIDTH, HEIGHT, "cub3D");
	mlx_hook(infos->win, 17, 0L, destroy_window, infos);
	mlx_hook(infos->win, 02, 1L << 0, keypress, infos);
	mlx_hook(infos->win, 03, 1L << 1, keyrelease, infos);
	mlx_hook(infos->win, 06, 1L << 6, motion, infos);
	infos->img.img = mlx_new_image(infos->mlx, WIDTH, HEIGHT);
	infos->img.addr = mlx_get_data_addr(infos->img.img,
			&infos->img.bits_per_pixel, &infos->img.line_length,
			&infos->img.endian);
	infos->player.speed = 1;
}

int	main(int ac, char **av)
{
	int		fd;
	t_info	*infos;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd != -1)
		{
			infos = initinfo();
			init(fd, av[1], infos);
			mlx_loop_hook(infos->mlx, printminimap, infos);
			mlx_loop(infos->mlx);
		}
		close(fd);
	}
	return (0);
}
