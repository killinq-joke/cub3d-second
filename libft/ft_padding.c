/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_padding.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mout <mout@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 14:54:07 by mout              #+#    #+#             */
/*   Updated: 2021/10/02 15:05:46 by mout             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_padding(char *str, int width, char c)
{
	int		i;
	// char	*tmp;

	i = ft_strlen(str);
	str = ft_strdup(str);
	while (i < width)
	{
		// tmp = str;
		str = ft_joinchar(str, c);
		// free(str);
		i++;
	}
	return (str);
}