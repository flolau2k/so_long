/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:41:12 by flauer            #+#    #+#             */
/*   Updated: 2023/07/17 11:24:29 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	set_window_size(t_instance *inst)
{
	t_point	monitor_size;
	t_point	map_size;

	mlx_get_monitor_size(0, &monitor_size.x, &monitor_size.y);
	map_size = scalar_multiply(inst->size, TILE_S);
	if (map_size.x > monitor_size.x)
		ft_err(inst, MAP_TOO_LARGE);
	if (map_size.y > monitor_size.y)
		ft_err(inst, MAP_TOO_LARGE);
	inst->window_s =(t_point){.x = map_size.x, .y = map_size.y};
	mlx_set_window_size(inst->mlx, map_size.x, map_size.y);
}


