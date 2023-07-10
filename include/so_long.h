/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:46:59 by flauer            #+#    #+#             */
/*   Updated: 2023/07/10 10:52:04 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <fcntl.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <MLX42/MLX42.h>
# include "libft.h"

# define WIDTH 1024
# define HEIGHT 768

static mlx_image_t *image;

typedef struct s_instance
{
	mlx_image_t *image;
}	t_instance;



#endif