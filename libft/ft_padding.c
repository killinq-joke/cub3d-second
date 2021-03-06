/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_padding.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 14:54:07 by mout              #+#    #+#             */
/*   Updated: 2021/10/10 19:41:00 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_padding(char *str, int width, char c)
{
	int		i;
	char	*tmp;

	i = ft_strlen(str);
	str = ft_strdup(str);
	while (i < width)
	{
		tmp = str;
		str = ft_joinchar(str, c);
		free(tmp);
		i++;
	}
	return (str);
}
