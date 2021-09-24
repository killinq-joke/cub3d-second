/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 01:35:50 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/24 15:47:28 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include "libft.h"

typedef enum e_bool {
	FALSE,
	TRUE,
}				t_bool;

typedef struct s_info {
	int	no;
	int	so;
	int	we;
	int	ea;
	int	f;
	int c;
	char **map;
}				t_info;

t_bool	dotcubcheck(char *str);
t_info	parsinfo(int fd);

#endif