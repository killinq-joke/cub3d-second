/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoabase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:58:49 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/27 12:12:47by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_joinfreechar(char *str, char c)
{
	char	*join;
	int		i;

	join = ft_calloc(ft_strlen(str) + 2, sizeof (char));
	i = 0;
	while (str && str[i])
	{
		join[i] = str[i];
		i++;
	}
	join[i++] = c;
	join[i] = 0;
	return (join);
}

char	*ft_itoabase(int nb, char *base)
{
	char	*res;
	char	*tmp;

	res = NULL;
	if (nb > (int)ft_strlen(base))
	{
		tmp = ft_itoabase(nb / ft_strlen(base), base);
		res = ft_joinchar(tmp, base[nb % ft_strlen(base)]);
		free(tmp);
		return (res);
	}
	tmp = res;
	res = ft_joinchar(tmp, base[nb % ft_strlen(base)]);
	free(tmp);
	return (res);
}
