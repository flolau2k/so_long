/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:46:59 by flauer            #+#    #+#             */
/*   Updated: 2023/07/14 11:53:44 by flauer           ###   ########.fr       */
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

# define TILE_S 48
# define SENSITIVITY 5
# define MARGIN 20

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

// for map points
typedef struct	s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_bounds
{
	t_point	ul;
	t_point	ll;
	t_point	ur;
	t_point	lr;
}	t_bounds;

typedef struct s_img
{
	mlx_image_t	*wall;
	mlx_image_t	*player;
	mlx_image_t	*floor;
	mlx_image_t	*exit_o;
	mlx_image_t	*exit_c;
	mlx_image_t	*coll_o;
	mlx_image_t	*coll_c;
	mlx_image_t	*info;
}	t_img;

typedef struct s_instance
{
	t_img	img;
	mlx_t	*mlx;
	char	**map;
	char	**map_cpy;
	t_point	size;
	t_point	ppos;
	t_point	psize;
	int		num_c;
	bool	won;
	t_point	rel_map_pos;
	t_point	window_size;
	size_t	moves;
}	t_instance;

// parser.c
void	parse_map(const char *path, t_instance *inst);

// helper.c
void	free_map(char ***map);
bool	is_valid_char(char c);
bool	compare_points(t_point p1, t_point p2);

//error.c
void	ft_err(t_instance *inst, const char *message);

// movements.c
bool	movable(t_instance *inst, t_point px);
bool	check_bounds(t_instance *inst, t_point pos,
					bool (*f)(t_instance *inst, t_point px));
void	move_player(t_instance *inst, t_point step);
void	move(t_instance *inst, t_point step);

// conversions.c
t_point	px_to_pos(t_point rel_map_pos, t_point px);
t_point	pos_to_px(t_point rel_map_pos, t_point pos);
t_point	add_pos(t_point p1, t_point p2);
t_point	substract_point(t_point p1, t_point p2);

// window.c
void		init_mlx(t_instance *inst);
mlx_image_t	*png_to_image(t_instance *inst, char *path, uint32_t size);
void		load_images(t_instance *inst);
void		my_im_to_window(t_instance *inst, mlx_image_t *img, t_point pos);
void		put_image_to_window(t_instance *inst, t_point pos);
bool	in_window(t_instance *inst, mlx_image_t *img, t_point px);

// so_long.c
void	game_over(t_instance *inst);

#endif