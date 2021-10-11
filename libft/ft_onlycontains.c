/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_onlycontains.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:35:10 by ztouzri           #+#    #+#             */
/*   Updated: 2021/10/10 15:36:11 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_onlycontains(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] != c)
			return (0);
	}
	return (1);
}
