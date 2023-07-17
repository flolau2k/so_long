/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:53:27 by flauer            #+#    #+#             */
/*   Updated: 2023/07/17 13:12:02 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	fill_rec(t_instance *inst, t_point begin)
{
	if (!ft_strchr(MOVABLE_CHARS, inst->map_cpy[begin.y][begin.x]))
		return ;
	inst->map_cpy[begin.y][begin.x] = FILL_CHAR;
	if (begin.y > 0)
		fill_rec(inst, (t_point){.x = begin.x, .y = begin.y - 1});
	if (begin.y < inst->size.y - 1)
		fill_rec(inst, (t_point){.x = begin.x, .y = begin.y + 1});
	if (begin.x > 0)
		fill_rec(inst, (t_point){.x = begin.x - 1, .y = begin.y});
	if (begin.x < inst->size.x - 1)
		fill_rec(inst, (t_point){.x = begin.x + 1, .y = begin.y});
}

static void	check_borders(t_instance *inst)
{
	t_point	pos;

	pos = (t_point){.x = 0, .y = 0};
	while (pos.y < inst->size.y)
	{
		if (pos.y == 0 || pos.y == inst->size.y - 1)
		{
			pos.x = 0;
			while (pos.x < inst->size.x)
			{
				if (inst->map_cpy[pos.y][pos.x] == FILL_CHAR)
					ft_err(inst, MAP_NC);
				pos.x++;
			}
		}
		else
		{
			if (inst->map_cpy[pos.y][0] == FILL_CHAR
				|| inst->map_cpy[pos.y][inst->size.x - 1] == FILL_CHAR)
				ft_err(inst, MAP_NC);
		}
		pos.y++;
	}
}

static void	check_surrounding(t_instance *inst, t_point pos)
{
	if (!ft_strchr(CHECK_CHARS, inst->map_cpy[pos.y][pos.x]))
		return ;
	if (pos.y > 0 && inst->map_cpy[pos.y - 1][pos.x] == FILL_CHAR)
		return ;
	if (pos.y < inst->size.y - 1
		&& inst->map_cpy[pos.y + 1][pos.x] == FILL_CHAR)
		return ;
	if (pos.x > 0 && inst->map_cpy[pos.y][pos.x - 1] == FILL_CHAR)
		return ;
	if (pos.x < inst->size.x - 1
		&& inst->map_cpy[pos.y][pos.x + 1] == FILL_CHAR)
		return ;
	if (inst->map_cpy[pos.y][pos.x] == COLL_CHAR)
		ft_err(inst, NO_ROUTE_C);
	else
		ft_err(inst, NO_ROUTE_E);
}

static void	check_paths(t_instance *inst)
{
	t_point	pos;

	pos = (t_point){.x = 0, .y = 0};
	while (pos.y < inst->size.y)
	{
		pos.x = 0;
		while (pos.x < inst->size.x)
		{
			check_surrounding(inst, pos);
			pos.x++;
		}
		pos.y++;
	}
}

void	check_map(t_instance *inst)
{
	if (!inst->map[0])
		ft_err(inst, MAP_EMPTY);
	get_size(inst);
	find_start_pos_and_check(inst);
	inst->map_cpy = copy_map(inst);
	fill_rec(inst, inst->ppos);
	check_borders(inst);
	check_paths(inst);
}
