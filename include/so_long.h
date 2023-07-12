/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:46:59 by flauer            #+#    #+#             */
/*   Updated: 2023/07/12 17:21:27 by flauer           ###   ########.fr       */
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

# define TILE_S 32

# define MULT_START "Multiple starting positions not allowed!"
# define MULT_EXIT "Multiple exits are not allowed!"
# define NO_ROUTE_E "No route to exit!"
# define NO_ROUTE_C "No route to all collectibles!"
# define INV_CHAR "Map contains invalid chars!"
# define MAP_RECT "Map is not rectangular!"
# define MAP_EMPTY "Map is empty!"
# define NO_MAP "No map file given!"
# define MAP_NC "Map is not closed!"
# define MAP_EXT "Map file is not a .ber file!"
# define MALLOC_ERROR "Malloc error occured!"
# define VALID_CHARS "01CEP"
# define CHECK_CHARS "CE"
# define MOVABLE_CHARS "P0CE"
# define FILL_CHAR 'F'
# define FLOOR_CHAR '0'
# define WALL_CHAR '1'
# define COLL_CHAR 'C'
# define EXIT_CHAR 'E'
# define PLAYER_CHAR 'P'

# define PLAYER "./assets/Player.png"
# define WALL "./assets/walls.png"
# define FLOOR "./assets/wooden.png"
# define EXIT_O "./assets/wooden_door_open.png"
# define EXIT_C "./assets/wooden_door_closed.png"
# define COLL_O "./assets/chest_open.png"
# define COLL_C "./assets/chest_closed.png"

typedef struct	s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_img
{
	mlx_image_t	*wall;
	mlx_image_t	*player;
	mlx_image_t	*floor;
	mlx_image_t	*exit_o;
	mlx_image_t	*exit_c;
	mlx_image_t	*coll_o;
	mlx_image_t	*coll_c;
}	t_img;

typedef struct s_instance
{
	t_img			img;
	mlx_t			*mlx;
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
void	ft_err(t_instance *inst, const char *message);

#endif