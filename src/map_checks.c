/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:53:27 by flauer            #+#    #+#             */
/*   Updated: 2023/07/19 09:25:42 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_start_count(t_instance *inst, t_point pos)
{
	static int	count;

	if (inst->map[pos.y][pos.x] == PLAYER_CHAR && count == 0)
	{
		count++;
		inst->ppos = (t_point){.x = pos.x, .y = pos.y};
	}
	else if (inst->map[pos.y][pos.x] == PLAYER_CHAR && count > 0)
		ft_err(inst, MULT_START);
	return (count);
}

int	check_exit_count(t_instance *inst, t_point pos)
{
	static int	count;

	if (inst->map[pos.y][pos.x] == EXIT_CHAR && count == 0)
		count++;
	else if (inst->map[pos.y][pos.x] == EXIT_CHAR && count > 0)
		ft_err(inst, MULT_EXIT);
	return (count);
}

void	check_borders(t_instance *inst)
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

void	check_paths(t_instance *inst)
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
