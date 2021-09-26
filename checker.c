/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 02:15:53 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/26 21:45:38 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	dotcubcheck(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!ft_strcmp(&str[i], ".cub"))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	dotxpmcheck(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!ft_strcmp(&str[i], ".xpm"))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	fullspacecheck(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] != ' ')
			return (FALSE);
		i++;
	}
	return (TRUE);
}
