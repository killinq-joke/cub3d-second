/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 21:29:12 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/28 21:31:00 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_join(char **split, char *str)
{
	int		i;
	char	**join;

	join = ft_calloc(ft_splitlen(split) + 2, sizeof (char *));
	i = 0;
	while (split && split[i])
		i++;
	join[i] = str;
	return (join);
}
