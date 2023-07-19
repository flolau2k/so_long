/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:51:38 by flauer            #+#    #+#             */
/*   Updated: 2023/07/19 09:56:23 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char ***map)
{
	int	i;

	i = 0;
	while ((*map)[i])
	{
		free((*map)[i]);
		++i;
	}
	free(*map);
	*map = NULL;
}

bool	is_valid_char(char c)
{
	if (ft_strchr(VALID_CHARS, c))
		return (true);
	return (false);
}

bool	compare_points(t_point p1, t_point p2)
{
	if (p1.x == p2.x && p1.y == p2.y)
		return (true);
	return (false);
}

void	free_instance(t_instance *inst)
{
	free_if_not_null(inst->mlx, &inst->img.coll_c);
	free_if_not_null(inst->mlx, &inst->img.coll_o);
	free_if_not_null(inst->mlx, &inst->img.wall);
	free_if_not_null(inst->mlx, &inst->img.player);
	free_if_not_null(inst->mlx, &inst->img.floor);
	free_if_not_null(inst->mlx, &inst->img.exit_c);
	free_if_not_null(inst->mlx, &inst->img.exit_o);
	free_if_not_null(inst->mlx, &inst->img.info);
	free_if_not_null(inst->mlx, &inst->img.move_c);
	if (inst->map)
	{
		free_map(&inst->map);
		inst->map = NULL;
	}
	if (inst->map_cpy)
	{
		free_map(&inst->map_cpy);
		inst->map_cpy = NULL;
	}
}

void	ft_err(t_instance *inst, const char *message)
{
	free_instance(inst);
	if (message)
		ft_printf("Error\n%s\n", message);
	exit(EXIT_FAILURE);
}
