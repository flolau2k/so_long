/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:46:40 by flauer            #+#    #+#             */
/*   Updated: 2023/07/17 14:42:16 by flauer           ###   ########.fr       */
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

void	init_mlx(t_instance *inst)
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
	parse_map(argv[1], &inst);
	init_mlx(&inst);
	render_map(&inst);
	mlx_loop_hook(inst.mlx, &ft_hook, &inst);
	mlx_loop(inst.mlx);
	mlx_terminate(inst.mlx);
	free_instance(&inst);
	return (EXIT_SUCCESS);
}
