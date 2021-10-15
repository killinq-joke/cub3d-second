/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:28:16 by ztouzri           #+#    #+#             */
/*   Updated: 2021/10/15 17:17:52 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	destroy_window(t_info *infos)
{
	mlx_destroy_window(infos->mlx, infos->win);
	freeinfo(infos);
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
	if (key == LEFTARR)
	{
		infos->player.left = TRUE;
		// if (infos->player.angle <= 0)
		// 	infos->player.angle = 360;
		// infos->player.angle--;
	}
	if (key == RIGHTARR)
	{
		infos->player.right = TRUE;
		// if (infos->player.angle >= 360)
		// 	infos->player.angle = -1;
		// infos->player.angle++;
	}
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
	if (key == LEFTARR)
		infos->player.left = FALSE;
	if (key == RIGHTARR)
		infos->player.right = FALSE;
	return (1);
}

int	motion(int x, int y, t_info *infos)
{
	(void)infos;
	printf("x == %d y == %d\n", x, y);
	return (1);
}
