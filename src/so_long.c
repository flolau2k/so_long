/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:46:40 by flauer            #+#    #+#             */
/*   Updated: 2023/07/21 08:58:16 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	game_over(t_instance *inst)
{
	inst->won = true;
	free_img(inst->mlx, &inst->img.coll_c);
	free_img(inst->mlx, &inst->img.coll_o);
	free_img(inst->mlx, &inst->img.exit_c);
	free_img(inst->mlx, &inst->img.exit_o);
	free_img(inst->mlx, &inst->img.floor);
	free_img(inst->mlx, &inst->img.wall);
	free_img(inst->mlx, &inst->img.info);
	free_img(inst->mlx, &inst->img.move_c);
	mlx_put_string(inst->mlx, "YOU WIN", 0, 0);
}

static void	ft_hook(void *param)
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

static void	init_mlx(t_instance *inst)
{
	inst->mlx = mlx_init(WIDTH, HEIGHT, "So long ...", false);
	set_window_size(inst);
	if (!inst->mlx)
		ft_err(inst, mlx_strerror(mlx_errno));
}

int32_t	main(int32_t argc, const char *argv[])
{
	t_instance	inst;

	init_t_instance(&inst);
	if (argc < 2)
		ft_err(&inst, NO_MAP);
	if (argc > 2)
		ft_err(&inst, TOO_MANY_ARGS);
	parse_map(argv[1], &inst);
	init_mlx(&inst);
	render_map(&inst);
	mlx_loop_hook(inst.mlx, &ft_hook, &inst);
	mlx_loop(inst.mlx);
	free_instance(&inst);
	mlx_terminate(inst.mlx);
	return (EXIT_SUCCESS);
}
