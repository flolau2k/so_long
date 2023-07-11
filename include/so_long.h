/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:46:59 by flauer            #+#    #+#             */
/*   Updated: 2023/07/11 13:51:50 by flauer           ###   ########.fr       */
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

# define MULT_START "Multiple starting positions not allowed!"
# define NO_ROUTE_E "No route to exit!"
# define NO_ROUTE_C "No route to all collectibles!"
# define MAP_INVALID "Map is not valid!"
# define MAP_EMPTY "Map is empty!"
# define MAP_EXT "Map file is not a .ber file!"

typedef struct	s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_instance
{
	mlx_image_t		*image;
	mlx_t			*mlx;
	mlx_texture_t	*texture;
	char			**map;
	t_point			size;
	t_point			ppos;
}	t_instance;

void	parse_map(char *path, t_instance *inst);

// helper.c
void	free_map(char ***map);

//error.c
void	ft_err(t_instance *inst, char *message);

#endif