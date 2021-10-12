/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 15:57:14 by ztouzri           #+#    #+#             */
/*   Updated: 2021/10/12 17:50:40 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	freeinfo(t_info *infos)
{
	close(infos->no);
	close(infos->so);
	close(infos->we);
	close(infos->ea);
	free(infos);
}
