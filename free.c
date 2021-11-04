/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 15:57:14 by ztouzri           #+#    #+#             */
/*   Updated: 2021/11/04 11:42:36 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	freeinfo(t_info *infos)
{
	free(infos->no);
	free(infos->so);
	free(infos->we);
	free(infos->ea);
	free(infos);
}
