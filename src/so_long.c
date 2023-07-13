/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:46:40 by flauer            #+#    #+#             */
/*   Updated: 2023/07/13 13:57:42 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_psize(t_instance *inst)
{
	inst->psize.x = inst->img.player->width;
	inst->psize.y = inst->img.player->height;
}

void	render_info(t_instance *inst)
{
	static mlx_image_t	*info;
	char				*msg;
	char				*fps;

	fps = ft_itoa(1/inst->mlx->delta_time);
	msg = ft_strjoin(fps, " FPS");
	if (info)
		mlx_delete_image(inst->mlx, info);
	info = mlx_put_string(inst->mlx, msg, 0, 0);
	free(msg);
	free(fps);
}

void	ft_hook(void *param)
{
	t_instance	*inst;

	inst = param;
	render_info(inst);
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

	inst = (t_instance){.mlx = NULL, .map = NULL, .map_cpy = NULL};
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
