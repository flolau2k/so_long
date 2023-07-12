/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:46:40 by flauer            #+#    #+#             */
/*   Updated: 2023/07/12 19:46:28 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_player(t_instance *inst, t_point pos)
{
	if (!ft_strchr(MOVABLE_CHARS, inst->map[inst->ppos.y + pos.y][inst->ppos.x + pos.x]))
		return ;
	inst->ppos.y = inst->ppos.y + pos.y;
	inst->ppos.x = inst->ppos.x + pos.x;
	inst->img.player->instances[0].x += pos.x * TILE_S;
	inst->img.player->instances[0].y += pos.y * TILE_S;
}

void	ft_hook(void *param)
{
	t_instance	*inst;

	inst = param;
	if (mlx_is_key_down(inst->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(inst->mlx);
	if (mlx_is_key_down(inst->mlx, MLX_KEY_W))
		//inst->img.player->instances[0].y -= 5;
		move_player(inst, (t_point){.x = 0, .y = -1});
	if (mlx_is_key_down(inst->mlx, MLX_KEY_S))
		// inst->img.player->instances[0].y += 5;
		move_player(inst, (t_point){.x = 0, .y = 1});
	if (mlx_is_key_down(inst->mlx, MLX_KEY_A))
		// inst->img.player->instances[0].x -= 5;
		move_player(inst, (t_point){.x = -1, .y = 0});
	if (mlx_is_key_down(inst->mlx, MLX_KEY_D))
		// inst->img.player->instances[0].x += 5;
		move_player(inst, (t_point){.x = 1, .y = 0});
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

void	my_image_to_window(t_instance *inst, mlx_image_t *img, t_point pos)
{
	if (mlx_image_to_window(inst->mlx, img, pos.x * TILE_S, pos.y * TILE_S) == -1)
		ft_err(inst, mlx_strerror(mlx_errno));
}

void	put_image_to_window(t_instance *inst, t_point pos)
{
	char	c;

	c = inst->map[pos.y][pos.x];
	if (c == FLOOR_CHAR || c == PLAYER_CHAR)
		my_image_to_window(inst, inst->img.floor, pos);
	else if (c == WALL_CHAR)
		my_image_to_window(inst, inst->img.wall, pos);
	else if (c == COLL_CHAR)
	{
		my_image_to_window(inst, inst->img.floor, pos);
		my_image_to_window(inst, inst->img.coll_c, pos);
	}
	else if (c == EXIT_CHAR)
	{
		my_image_to_window(inst, inst->img.floor, pos);
		my_image_to_window(inst, inst->img.exit_c, pos);
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
	my_image_to_window(inst, inst->img.player, inst->ppos);
}

void	init_mlx(t_instance *inst)
{
	inst->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!inst->mlx)
		ft_err(inst, mlx_strerror(mlx_errno));
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
	render_map(&inst);
	mlx_loop_hook(inst.mlx, &ft_hook, &inst);
	mlx_loop(inst.mlx);
	mlx_terminate(inst.mlx);
	return (EXIT_SUCCESS);
}
