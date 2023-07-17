/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:38:04 by flauer            #+#    #+#             */
/*   Updated: 2023/07/17 13:21:29 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	collect_item(t_instance *inst, t_point pos)
{
	size_t		i;
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

bool	check_bounds(t_instance *inst, t_point pos,
					bool (*f)(t_instance *inst, t_point px))
{
	t_bounds	pb;

	pb.ul = (t_point){.x = pos.x, .y = pos.y};
	pb.ll = add_pos(pb.ul, (t_point){.x = 0, .y = inst->psize.y});
	pb.ur = add_pos(pb.ul, (t_point){.x = inst->psize.x, .y = 0});
	pb.lr = add_pos(pb.ul, inst->psize);
	if (f(inst, pb.ul) && f(inst, pb.ll)
		&& f(inst, pb.ur) && f(inst, pb.lr))
		return (true);
	return (false);
}

void	move_player(t_instance *inst, t_point step)
{
	inst->img.player->instances[0].x += step.x;
	inst->img.player->instances[0].y += step.y;
}

void	move(t_instance *inst, t_point step)
{
	t_point	oldpos;
	t_point	newpos;

	oldpos.x = inst->img.player->instances[0].x;
	oldpos.y = inst->img.player->instances[0].y;
	newpos = add_pos(oldpos, step);
	if (check_bounds(inst, newpos, &movable))
	{
		move_player(inst, step);
		inst->moves++;
	}
	check_collectibles(inst, newpos);
	check_exit(inst, newpos);
	ft_printf("Move count: %u\n", inst->moves);
}
