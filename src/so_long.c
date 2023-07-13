/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:46:40 by flauer            #+#    #+#             */
/*   Updated: 2023/07/13 10:55:14 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_point	px_to_pos(t_point px)
{
	t_point	pos;

	pos.x = px.x / TILE_S;
	pos.y = px.y / TILE_S;
	return (pos);
}

t_point	pos_to_px(t_point pos)
{
	t_point	px;

	px.x = pos.x * TILE_S;
	px.y = pos.y * TILE_S;
	return (px);
}

t_point	add_pos(t_point p1, t_point p2)
{
	t_point	ret;

	ret.x = p1.x + p2.x;
	ret.y = p1.y + p2.y;
	return (ret);
}

bool	movable(t_instance *inst, t_point px)
{
	t_point	map_pos;

	map_pos = px_to_pos(px);
	if (!ft_strchr(MOVABLE_CHARS, inst->map[map_pos.y][map_pos.x]))
		return (false);
	return (true);
}

bool	check_bounds(t_instance *inst, t_point	pos)
{
	t_bounds	pb;

	pb.ul = (t_point){.x = pos.x, .y = pos.y};
	pb.ll = add_pos(pb.ul, (t_point){.x = 0, .y = inst->psize.y});
	pb.ur = add_pos(pb.ul, (t_point){.x = inst->psize.x, .y = 0});
	pb.lr = add_pos(pb.ul, inst->psize);
	if (movable(inst, pb.ul) && movable(inst, pb.ll)
		&& movable(inst, pb.ur) && movable(inst, pb.lr))
		return (true);
	return (false);
}

void	get_psize(t_instance *inst)
{
	inst->psize.x = inst->img.player->width;
	inst->psize.y = inst->img.player->height;
}

void	move_player(t_instance *inst, t_point step)
{
	t_point	oldpos;
	t_point	newpos;

	oldpos.x = inst->img.player->instances[0].x;
	oldpos.y = inst->img.player->instances[0].y;
	newpos = add_pos(oldpos, step);
	if (check_bounds(inst, newpos))
	{
		inst->img.player->instances[0].x = newpos.x;
		inst->img.player->instances[0].y = newpos.y;
	}
}

void	ft_hook(void *param)
{
	t_instance	*inst;

	inst = param;
	if (mlx_is_key_down(inst->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(inst->mlx);
	if (mlx_is_key_down(inst->mlx, MLX_KEY_W))
		move_player(inst, (t_point){.x = 0, .y = -5});
	if (mlx_is_key_down(inst->mlx, MLX_KEY_S))
		move_player(inst, (t_point){.x = 0, .y = 5});
	if (mlx_is_key_down(inst->mlx, MLX_KEY_A))
		move_player(inst, (t_point){.x = -5, .y = 0});
	if (mlx_is_key_down(inst->mlx, MLX_KEY_D))
		move_player(inst, (t_point){.x = 5, .y = 0});
}

mlx_image_t	*png_to_image(t_instance *inst, char *path, uint32_t size)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	texture = mlx_load_png(path);
	if (!texture)
		ft_err(inst, mlx_strerror(mlx_errno));
	img = mlx_texture_to_image(inst->mlx, texture);
	if (!img)
		ft_err(inst, mlx_strerror(mlx_errno));
	mlx_delete_texture(texture);
	if (size > 0)
		mlx_resize_image(img, size, size);
	return (img);
}

void	load_images(t_instance *inst)
{
	inst->img.player	= png_to_image(inst, PLAYER, 0);
	inst->img.wall		= png_to_image(inst, WALL, TILE_S);
	inst->img.floor		= png_to_image(inst, FLOOR, TILE_S);
	inst->img.exit_c	= png_to_image(inst, EXIT_C, TILE_S);
	inst->img.exit_o	= png_to_image(inst, EXIT_O, TILE_S);
	inst->img.coll_c	= png_to_image(inst, COLL_C, TILE_S);
	inst->img.coll_o	= png_to_image(inst, COLL_O, TILE_S);
}

void	my_im_to_window(t_instance *inst, mlx_image_t *img, t_point pos)
{
	if (mlx_image_to_window(inst->mlx, img,
		pos.x * TILE_S, pos.y * TILE_S) == -1)
		ft_err(inst, mlx_strerror(mlx_errno));
}

void	put_image_to_window(t_instance *inst, t_point pos)
{
	char	c;

	c = inst->map[pos.y][pos.x];
	if (c == FLOOR_CHAR || c == PLAYER_CHAR)
		my_im_to_window(inst, inst->img.floor, pos);
	else if (c == WALL_CHAR)
		my_im_to_window(inst, inst->img.wall, pos);
	else if (c == COLL_CHAR)
	{
		my_im_to_window(inst, inst->img.floor, pos);
		my_im_to_window(inst, inst->img.coll_c, pos);
	}
	else if (c == EXIT_CHAR)
	{
		my_im_to_window(inst, inst->img.floor, pos);
		my_im_to_window(inst, inst->img.exit_c, pos);
	}
}

void	render_map(t_instance *inst)
{
	t_point	pos;

	pos = (t_point){.x = 0, .y = 0};
	while (pos.y < inst->size.y)
	{
		pos.x = 0;
		while (pos.x < inst->size.x)
		{
			put_image_to_window(inst, pos);
			pos.x++;
		}
		pos.y++;
	}
	my_im_to_window(inst, inst->img.player, inst->ppos);
}

void	init_mlx(t_instance *inst)
{
	inst->mlx = mlx_init(WIDTH, HEIGHT, "So long ...", true);
	if (!inst->mlx)
		ft_err(inst, mlx_strerror(mlx_errno));
}

void	render_info(t_instance *inst)
{
	static mlx_image_t	*info;

	if (info)
		mlx_delete_image(inst->mlx, info);
	info = mlx_put_string(inst->mlx, "hallo test", 0, 0);
}

int32_t	main(int32_t argc, const char *argv[])
{
	t_instance	inst;

	inst = (t_instance){.mlx = NULL, .map = NULL, .map_cpy = NULL};
	if (argc < 2)
		ft_err(&inst, NO_MAP);
	parse_map(argv[1], &inst);
	init_mlx(&inst);
	load_images(&inst);
	get_psize(&inst);
	render_map(&inst);
	render_info(&inst);
	mlx_loop_hook(inst.mlx, &ft_hook, &inst);
	mlx_loop(inst.mlx);
	mlx_terminate(inst.mlx);
	return (EXIT_SUCCESS);
}
