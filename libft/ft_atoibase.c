/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoibase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 22:07:28 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/27 11:58:53 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	whichindex(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

size_t	ft_atoibase(char *str, char *base)
{
	unsigned int	ret;
	int				i;

	ret = 0;
	i = 0;
	while (str[i])
	{
		ret *= ft_strlen(base);
		if (whichindex(base, str[i]) == -1)
			return (0);
		ret += whichindex(base, str[i]);
		i++;
	}
	return (ret);
}
