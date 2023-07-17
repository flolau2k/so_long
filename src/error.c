/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:18:58 by flauer            #+#    #+#             */
/*   Updated: 2023/07/17 10:47:59 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_err(t_instance *inst, const char *message)
{
	free_instance(inst);
	if (message)
		ft_printf("Error\n%s\n", message);
	exit(EXIT_FAILURE);
}
