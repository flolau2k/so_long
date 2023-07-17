/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:38:04 by flauer            #+#    #+#             */
/*   Updated: 2023/07/17 15:11:51 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	collect_item(t_instance *inst, t_point pos)
{
	size_t	i;
	t_point	px;

	i = 0;
	while (i < inst->img.coll_c->count)
	{
		px = (t_point){.x = inst->img.coll_c->instances[i].x,
			.y = inst->img.coll_c->instances[i].y};
		if (compare_points(px_to_pos(inst->rel_map_pos, px), pos))
		{
			inst->img.coll_c->instances[i].enabled = false;
			inst->map[pos.y][pos.x] = FLOOR_CHAR;
			inst->num_c--;
		}
		i++;
	}
}

static t_bounds	get_bounds(mlx_image_t *img, t_point pos)
{
	t_bounds	ret;

	ret.ul = (t_point){.x = pos.x, .y = pos.y};
	ret.ll = add_pos(ret.ul, (t_point){.x = 0, .y = img->height});
	ret.ur = add_pos(ret.ul, (t_point){.x = img->width, .y = 0});
	ret.lr = add_pos(ret.ul, (t_point){.x = img->width, .y = img->height});
	return (ret);
}

t_point	check_bounds(t_instance *inst, t_point step,
					bool (*f)(t_instance *inst, t_point px))
{
	t_bounds	pb;
	t_point		newpos;
	t_point		oldpos;

	oldpos.x = inst->img.player->instances[0].x;
	oldpos.y = inst->img.player->instances[0].y;
	newpos = add_pos(oldpos, step);
	pb = get_bounds(inst->img.player, newpos);
	if (f(inst, pb.ul) && f(inst, pb.ll)
		&& f(inst, pb.ur) && f(inst, pb.lr))
		return (step);
	else if (step.x != 0 || step.y != 0)
		return (check_bounds(inst, scalar_multiply(step, 0.5), f));
	return (step);
}

void	move(t_instance *inst, t_point step)
{
	t_point	newstep;
	t_point	newpos;

	newstep = check_bounds(inst, step, &movable);
	if (newstep.x != 0 || newstep.y != 0)
	{
		inst->img.player->instances[0].x += newstep.x;
		inst->img.player->instances[0].y += newstep.y;
		inst->moves++;
		newpos.x = inst->img.player->instances[0].x;
		newpos.y = inst->img.player->instances[0].y;
		check_collectibles(inst, newpos);
		check_exit(inst, newpos);
		ft_printf("Move count: %u\n", inst->moves);
	}
}
