/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:14:25 by flauer            #+#    #+#             */
/*   Updated: 2023/07/17 13:14:52 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_size(t_instance *inst)
{
	inst->size = (t_point){.x = 0, .y = 0};
	inst->size.x = ft_strlen(inst->map[0]);
	inst->size.y++;
	while (inst->map[inst->size.y])
	{
		if (ft_strlen(inst->map[inst->size.y]) != inst->size.x)
			ft_err(inst, MAP_RECT);
		inst->size.y++;
	}
}

char	**copy_map(t_instance *inst)
{
	char	**ret;
	int		i;

	i = 0;
	ret = malloc(sizeof(char *) * inst->size.y + 1);
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
