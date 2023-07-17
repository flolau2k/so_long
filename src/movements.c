/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:38:04 by flauer            #+#    #+#             */
/*   Updated: 2023/07/17 09:28:50 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	movable(t_instance *inst, t_point px)
{
	t_point	map_pos;

	map_pos = px_to_pos(inst->rel_map_pos, px);
	if (!ft_strchr(MOVABLE_CHARS, inst->map[map_pos.y][map_pos.x]))
		return (false);
	return (true);
}

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

void	collectible(t_instance *inst, t_point px)
{
	t_point	map_pos;

	map_pos = px_to_pos(inst->rel_map_pos, px);
	if (inst->map[map_pos.y][map_pos.x] == COLL_CHAR)
		collect_item(inst, map_pos);
}

void	is_exit(t_instance *inst, t_point px)
{
	t_point	map_pos;

	map_pos = px_to_pos(inst->rel_map_pos, px);
	if (inst->map[map_pos.y][map_pos.x] == EXIT_CHAR)
		game_over(inst);
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

void	check_exit(t_instance *inst, t_point pos)
{
	t_bounds	pb;

	if (inst->num_c > 0)
		return ;
	inst->img.exit_c->instances[0].enabled = false;
	pb.ul = (t_point){.x = pos.x, .y = pos.y};
	pb.ll = add_pos(pb.ul, (t_point){.x = 0, .y = inst->psize.y});
	pb.ur = add_pos(pb.ul, (t_point){.x = inst->psize.x, .y = 0});
	pb.lr = add_pos(pb.ul, inst->psize);
	is_exit(inst, pb.ul);
	is_exit(inst, pb.ll);
	is_exit(inst, pb.ur);
	is_exit(inst, pb.lr);
}

void	move_player(t_instance *inst, t_point step)
{
	inst->img.player->instances[0].x += step.x;
	inst->img.player->instances[0].y += step.y;
}

void	put_moves(t_instance *inst)
{
	ft_printf("Move count: %u\n", inst->moves);
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
	put_moves(inst);
}
