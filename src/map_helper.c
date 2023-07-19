/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:14:25 by flauer            #+#    #+#             */
/*   Updated: 2023/07/19 09:19:33 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	fill_rec(t_instance *inst, t_point begin)
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

void	check_surrounding(t_instance *inst, t_point pos)
{
	if (!ft_strchr(CHECK_CHARS, inst->map[pos.y][pos.x]))
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

void	get_size(t_instance *inst)
{
	inst->size = (t_point){.x = 0, .y = 0};
	if (!inst->map[0])
		ft_err(inst, MAP_EMPTY);
	inst->size.x = ft_strlen(inst->map[0]);
	inst->size.y++;
	while (inst->map[inst->size.y])
	{
		if ((int) ft_strlen(inst->map[inst->size.y]) != inst->size.x)
			ft_err(inst, MAP_RECT);
		inst->size.y++;
	}
	if (inst->size.x < 1 || inst->size.y < 1)
		ft_err(inst, MAP_EMPTY);
}

char	**copy_map(t_instance *inst)
{
	char	**ret;
	int		i;

	i = 0;
	ret = malloc(sizeof(char *) * (inst->size.y + 1));
	if (!ret)
		ft_err(inst, strerror(errno));
	ret[inst->size.y] = NULL;
	while (i < inst->size.y)
	{
		ret[i] = ft_strdup(inst->map[i]);
		if (!ret[i])
			ft_err(inst, strerror(errno));
		i++;
	}
	return (ret);
}
