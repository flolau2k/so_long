/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:46:59 by flauer            #+#    #+#             */
/*   Updated: 2023/07/12 12:40:45 by flauer           ###   ########.fr       */
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
# define MULT_EXIT "Multiple exits are not allowed!"
# define NO_ROUTE_E "No route to exit!"
# define NO_ROUTE_C "No route to all collectibles!"
# define INV_CHAR "Map contains invalid chars!"
# define MAP_RECT "Map is not rectangular!"
# define MAP_EMPTY "Map is empty!"
# define MAP_NC "Map is not closed!"
# define MAP_EXT "Map file is not a .ber file!"
# define MALLOC_ERROR "Malloc error occured!"
# define VALID_CHARS "01CEP"
# define CHECK_CHARS "CE"
# define MOVABLE_CHARS "0CE"
# define FILL_CHAR 'F'

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
	char			**map_cpy;
	t_point			size;
	t_point			ppos;
}	t_instance;

// parser.c
void	parse_map(const char *path, t_instance *inst);
static void	fill_rec(t_instance *inst, t_point begin);


// helper.c
void	free_map(char ***map);

//error.c
void	ft_err(t_instance *inst, char *message);

#endif