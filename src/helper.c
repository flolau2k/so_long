/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:51:38 by flauer            #+#    #+#             */
/*   Updated: 2023/07/21 10:36:00 by flauer           ###   ########.fr       */
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
	free_t_img(inst->mlx, &inst->img);
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
	if (inst->mlx)
		mlx_terminate(inst->mlx);
	exit(EXIT_FAILURE);
}
