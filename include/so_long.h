/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:46:59 by flauer            #+#    #+#             */
/*   Updated: 2023/07/19 09:34:49 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <fcntl.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <stdlib.h>
# include <MLX42/MLX42.h>
# include "libft.h"

# define WIDTH 480
# define HEIGHT 320

# define TILE_S 48
# define SENSITIVITY 8

# define MULT_START "Multiple starting positions not allowed"
# define MULT_EXIT "Multiple exits are not allowed"
# define NO_ROUTE_E "No route to exit"
# define NO_ROUTE_C "No route to all collectibles"
# define INV_CHAR "Map contains invalid chars"
# define MAP_RECT "Map is not rectangular"
# define MAP_EMPTY "Map is empty"
# define NO_COLL "No Collectibles in the Map"
# define NO_MAP "No map file given"
# define MAP_NC "Map is not closed"
# define NO_START "No Player start position defined"
# define NO_EXIT "Map has no Exit"
# define MAP_TOO_LARGE "Map is too large"
# define MAP_EXT "Map file is not a .ber file"
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
typedef struct s_point
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
	mlx_image_t	*move_c;
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
	t_point	window_s;
	size_t	moves;
}	t_instance;

// map_parser.c
void		parse_map(const char *path, t_instance *inst);
void		find_start_pos_and_check(t_instance *inst);

// map_helper.c
void		fill_rec(t_instance *inst, t_point begin);
void		check_surrounding(t_instance *inst, t_point pos);
void		get_size(t_instance *inst);
char		**copy_map(t_instance *inst);

// map_checks.c
int			check_start_count(t_instance *inst, t_point pos);
int			check_exit_count(t_instance *inst, t_point pos);
void		check_borders(t_instance *inst);
void		check_paths(t_instance *inst);

// helper.c
void		free_map(char ***map);
bool		is_valid_char(char c);
bool		compare_points(t_point p1, t_point p2);
void		free_instance(t_instance *inst);
void		ft_err(t_instance *inst, const char *message);

// movements.c
void		collect_item(t_instance *inst, t_point pos);
t_point		check_bounds(t_instance *inst, t_point pos,
				bool (*f)(t_instance *inst, t_point px));
void		move(t_instance *inst, t_point step);

// move_helper.c
bool		movable(t_instance *inst, t_point px);
void		collectible(t_instance *inst, t_point px);
void		is_exit(t_instance *inst, t_point px);
void		check_collectibles(t_instance *inst, t_point pos);
void		check_exit(t_instance *inst, t_point pos);

// conversions.c
t_point		px_to_pos(t_point rel_map_pos, t_point px);
t_point		pos_to_px(t_point rel_map_pos, t_point pos);
t_point		add_pos(t_point p1, t_point p2);
t_point		substract_point(t_point p1, t_point p2);
t_point		scalar_multiply(t_point p1, double scale);

// window.c
void		set_window_size(t_instance *inst);

// textures.c
mlx_image_t	*png_to_image(t_instance *inst, char *path, uint32_t size);
void		load_images(t_instance *inst);
void		my_im_to_window(t_instance *inst, mlx_image_t *img, t_point pos);
void		put_image_to_window(t_instance *inst, t_point pos);
void		render_map(t_instance *inst);

// info_display.c
void		render_fps(t_instance *inst);
void		render_movements(t_instance *inst);

// so_long.c
void		game_over(t_instance *inst);

// initializers.c
void		init_t_img(t_img *img);
void		init_t_point(t_point *pt);
void		init_t_instance(t_instance *inst);

#endif