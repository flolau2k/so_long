/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:38:04 by flauer            #+#    #+#             */
/*   Updated: 2023/07/13 17:01:27 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	movable(t_instance *inst, t_point px)
{
	t_point	map_pos;

	map_pos = px_to_pos(px);
	if (!ft_strchr(MOVABLE_CHARS, inst->map[map_pos.y][map_pos.x]))
		return (false);
	return (true);
}

void	collect_item(t_instance *inst, t_point pos)
{
	int		i;
	t_point	px;

	i = 0;
	while (i < inst->img.coll_c->count)
	{
		px = (t_point){.x = inst->img.coll_c->instances[i].x,
						.y = inst->img.coll_c->instances[i].y};
		if (compare_points(px_to_pos(px), pos))
		{
			inst->img.coll_c->instances[i].enabled = false;
			inst->map[pos.y][pos.x] = '0';
		}
		i++;
	}
}

void	collectible(t_instance *inst, t_point px)
{
	t_point	map_pos;

	map_pos = px_to_pos(px);
	if (inst->map[map_pos.y][map_pos.x] == COLL_CHAR)
		collect_item(inst, map_pos);
	return ;
}

bool	check_bounds(t_instance *inst, t_point	pos)
{
	t_bounds	pb;

	pb.ul = (t_point){.x = pos.x, .y = pos.y};
	pb.ll = add_pos(pb.ul, (t_point){.x = 0, .y = inst->psize.y});
	pb.ur = add_pos(pb.ul, (t_point){.x = inst->psize.x, .y = 0});
	pb.lr = add_pos(pb.ul, inst->psize);
	if (movable(inst, pb.ul) && movable(inst, pb.ll)
		&& movable(inst, pb.ur) && movable(inst, pb.lr))
		return (true);
	return (false);
}

void	check_collectibles(t_instance *inst, t_point pos)
{
	t_bounds	pb;

	pb.ul = (t_point){.x = pos.x, .y = pos.y};
	pb.ll = add_pos(pb.ul, (t_point){.x = 0, .y = inst->psize.y});
	pb.ur = add_pos(pb.ul, (t_point){.x = inst->psize.x, .y = 0});
	pb.lr = add_pos(pb.ul, inst->psize);
	collectible(inst, pb.ul);
	collectible(inst, pb.ll);
	collectible(inst, pb.ur);
	collectible(inst, pb.lr);
}

void	move_player(t_instance *inst, t_point step)
{
	t_point	oldpos;
	t_point	newpos;

	oldpos.x = inst->img.player->instances[0].x;
	oldpos.y = inst->img.player->instances[0].y;
	newpos = add_pos(oldpos, step);
	if (check_bounds(inst, newpos))
	{
		inst->img.player->instances[0].x = newpos.x;
		inst->img.player->instances[0].y = newpos.y;
	}
	check_collectibles(inst, newpos);
}
