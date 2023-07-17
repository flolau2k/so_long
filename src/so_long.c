/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:46:40 by flauer            #+#    #+#             */
/*   Updated: 2023/07/17 10:44:40 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	game_over(t_instance *inst)
{
	inst->won = true;
	mlx_delete_image(inst->mlx, inst->img.coll_c);
	mlx_delete_image(inst->mlx, inst->img.coll_o);
	mlx_delete_image(inst->mlx, inst->img.exit_c);
	mlx_delete_image(inst->mlx, inst->img.exit_o);
	mlx_delete_image(inst->mlx, inst->img.floor);
	mlx_delete_image(inst->mlx, inst->img.wall);
	mlx_delete_image(inst->mlx, inst->img.info);
	mlx_delete_image(inst->mlx, inst->img.move_c);
	mlx_put_string(inst->mlx, "YOU WIN", 0, 0);
	// mlx_delete_image(inst->mlx, inst->img.player);
}

void	render_fps(t_instance *inst)
{
	char	*msg;
	char	*fps;
	t_point	pos;

	fps = ft_itoa(1/inst->mlx->delta_time);
	msg = ft_strjoin(fps, " FPS");
	if (inst->img.info)
		mlx_delete_image(inst->mlx, inst->img.info);
	inst->img.info = mlx_put_string(inst->mlx, msg, 0, 0);
	pos.x = inst->window_s.x - inst->img.info->width;
	pos.y = inst->window_s.y - inst->img.info->height;
	inst->img.info->instances[0].x = pos.x;
	inst->img.info->instances[0].y = pos.y;
	inst->img.info->instances[0].z = 255;
	free(msg);
	free(fps);
}

void	render_movements(t_instance *inst)
{
	char	*msg;
	char	*mc;
	t_point	pos;

	mc = ft_itoa(inst->moves);
	msg = ft_strjoin("Move Count: ", mc);
	if (inst->img.move_c)
		mlx_delete_image(inst->mlx, inst->img.move_c);
	inst->img.move_c = mlx_put_string(inst->mlx, msg, 0, 0);
	pos.x = 0;
	pos.y = inst->window_s.y - inst->img.move_c->height;
	inst->img.move_c->instances[0].x = pos.x;
	inst->img.move_c->instances[0].y = pos.y;
	inst->img.move_c->instances[0].z = 255;
	free(msg);
	free(mc);
}

void	ft_hook(void *param)
{
	t_instance	*inst;

	inst = param;
	if (mlx_is_key_down(inst->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(inst->mlx);
	if (inst->won)
		return ;
	render_fps(inst);
	render_movements(inst);
	if (mlx_is_key_down(inst->mlx, MLX_KEY_W) && !inst->won)
		move(inst, (t_point){.x = 0, .y = -SENSITIVITY});
	if (mlx_is_key_down(inst->mlx, MLX_KEY_S) && !inst->won)
		move(inst, (t_point){.x = 0, .y = SENSITIVITY});
	if (mlx_is_key_down(inst->mlx, MLX_KEY_A) && !inst->won)
		move(inst, (t_point){.x = -SENSITIVITY, .y = 0});
	if (mlx_is_key_down(inst->mlx, MLX_KEY_D) && !inst->won)
		move(inst, (t_point){.x = SENSITIVITY, .y = 0});
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

int32_t	main(int32_t argc, const char *argv[])
{
	t_instance	inst;

	inst = (t_instance){.mlx = NULL, .map = NULL, .map_cpy = NULL, .num_c = 0,
						.won = false, .moves = 0};
	inst.img = (t_img){.wall = NULL, .player = NULL, .floor = NULL,
				.exit_o = NULL, .exit_c = NULL, .coll_o = NULL, .coll_c = NULL,
				.info = NULL, .move_c = NULL};
	if (argc < 2)
		ft_err(&inst, NO_MAP);
	parse_map(argv[1], &inst);
	init_mlx(&inst);
	load_images(&inst);
	inst.psize.x = inst.img.player->width;
	inst.psize.y = inst.img.player->height;
	render_map(&inst);
	mlx_loop_hook(inst.mlx, &ft_hook, &inst);
	mlx_loop(inst.mlx);
	mlx_terminate(inst.mlx);
	free_instance(&inst);
	return (EXIT_SUCCESS);
}
