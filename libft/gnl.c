/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 14:24:35 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/24 15:19:37 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_next_line(int fd, char **line)
{
	int		ret;
	char	buf;
	char	*tmp;

	*line = ft_calloc(1, sizeof (char));
	ret = 1;
	while (ret > 0)
	{
		ret = read(fd, &buf, 1);
		if (buf == '\n')
			return (ret);
		if (ret < 1)
			return (ret);
		tmp = *line;
		*line = ft_joinchar(tmp, buf);
		free(tmp);
	}
	return (ret);
}
