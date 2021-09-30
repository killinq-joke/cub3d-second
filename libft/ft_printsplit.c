/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printsplit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 13:28:13 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/29 13:51:35 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printsplit(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
	{
		ft_putstr(split[i]);
		ft_putchar('\n');
		i++;
	}
}
