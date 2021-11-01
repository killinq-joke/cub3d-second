/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 01:35:32 by ztouzri           #+#    #+#             */
/*   Updated: 2021/10/31 19:42:33 by ztouzri          ###   ########.fr       */
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
	infos->player.speed = NSPEED;
}

void	initplayer(t_info *infos)
{
	int	y;
	int	x;

	y = 0;
	while (infos->map[y])
	{
		x = 0;
		while (infos->map[y][x])
		{
			if (ft_isin("NSWE", infos->map[y][x]))
			{
				infos->player.x = x * SIZE + SIZE / 2;
				infos->player.y = y * SIZE + SIZE / 2;
				infos->map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
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
			initplayer(infos);
			mlx_loop_hook(infos->mlx, printminimap, infos);
			mlx_loop(infos->mlx);
		}
		close(fd);
	}
	return (0);
}
