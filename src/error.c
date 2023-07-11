/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:18:58 by flauer            #+#    #+#             */
/*   Updated: 2023/07/11 13:29:40 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_err(t_instance *inst, char *message)
{
	if (inst->mlx)
		mlx_terminate(inst->mlx);
	if (inst->map)
		free_map(&inst->map);
	ft_printf("%s\n", message);
	exit(EXIT_FAILURE);
}
