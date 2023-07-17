/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:46:40 by flauer            #+#    #+#             */
/*   Updated: 2023/07/17 09:52:41 by flauer           ###   ########.fr       */
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
	mlx_delete_image(inst->mlx, inst->img.player);
	mlx_delete_image(inst->mlx, inst->img.floor);
	mlx_delete_image(inst->mlx, inst->img.wall);
	mlx_delete_image(inst->mlx, inst->img.info);
	mlx_put_string(inst->mlx, "YOU WIN", 0, 0);
}

void	get_psize(t_instance *inst)
{
	inst->psize.x = inst->img.player->width;
	inst->psize.y = inst->img.player->height;
}

void	render_info(t_instance *inst)
{
	char	*msg;
	char	*fps;

	fps = ft_itoa(1/inst->mlx->delta_time);
	msg = ft_strjoin(fps, " FPS");
	if (inst->img.info)
		mlx_delete_image(inst->mlx, inst->img.info);
	inst->img.info = mlx_put_string(inst->mlx, msg, 0, 0);
	free(msg);
	free(fps);
}

void	ft_hook(void *param)
{
	t_instance	*inst;

	inst = param;
	if (inst->won)
		return ;
	render_info(inst);
	if (mlx_is_key_down(inst->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(inst->mlx);
	if (mlx_is_key_down(inst->mlx, MLX_KEY_W))
		move(inst, (t_point){.x = 0, .y = -SENSITIVITY});
	if (mlx_is_key_down(inst->mlx, MLX_KEY_S))
		move(inst, (t_point){.x = 0, .y = SENSITIVITY});
	if (mlx_is_key_down(inst->mlx, MLX_KEY_A))
		move(inst, (t_point){.x = -SENSITIVITY, .y = 0});
	if (mlx_is_key_down(inst->mlx, MLX_KEY_D))
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
	if (argc < 2)
		ft_err(&inst, NO_MAP);
	parse_map(argv[1], &inst);
	init_mlx(&inst);
	load_images(&inst);
	get_psize(&inst);
	render_map(&inst);
	mlx_loop_hook(inst.mlx, &ft_hook, &inst);
	mlx_loop(inst.mlx);
	mlx_terminate(inst.mlx);
	return (EXIT_SUCCESS);
}
