/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:51:38 by flauer            #+#    #+#             */
/*   Updated: 2023/07/13 14:14:47 by flauer           ###   ########.fr       */
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
