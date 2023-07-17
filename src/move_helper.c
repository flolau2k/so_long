/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:20:14 by flauer            #+#    #+#             */
/*   Updated: 2023/07/17 13:21:19 by flauer           ###   ########.fr       */
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
