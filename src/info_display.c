/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:09:53 by flauer            #+#    #+#             */
/*   Updated: 2023/07/17 11:10:22 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
