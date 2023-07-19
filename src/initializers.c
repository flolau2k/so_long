/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:34:25 by flauer            #+#    #+#             */
/*   Updated: 2023/07/19 09:53:33 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_if_not_null(mlx_t *mlx, mlx_image_t **img)
{
	if (*img)
		mlx_delete_image(mlx, *img);
	*img = NULL;
}

void	init_t_img(t_img *img)
{
	img->coll_c = NULL;
	img->coll_o = NULL;
	img->exit_c = NULL;
	img->exit_o = NULL;
	img->floor = NULL;
	img->info = NULL;
	img->move_c = NULL;
	img->player = NULL;
	img->wall = NULL;
}

void	init_t_point(t_point *pt)
{
	pt->x = 0;
	pt->y = 0;
}

void	init_t_instance(t_instance *inst)
{
	init_t_img(&inst->img);
	inst->mlx = NULL;
	inst->map = NULL;
	inst->map_cpy = NULL;
	init_t_point(&inst->size);
	init_t_point(&inst->ppos);
	init_t_point(&inst->psize);
	inst->num_c = 0;
	inst->won = false;
	init_t_point(&inst->rel_map_pos);
	init_t_point(&inst->window_s);
	inst->moves = 0;
}
