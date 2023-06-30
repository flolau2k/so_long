/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:06:41 by flauer            #+#    #+#             */
/*   Updated: 2023/06/30 13:24:27 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	read_map_lines(char *path, t_list **map)
{
	int		file;
	char	*line;

	file = open(path, O_RDONLY);
	line = get_next_line(file);
	ft_lstadd_back(map, ft_lstnew(line));
	while (line)
	{
		line = get_next_line(file);
		ft_lstadd_back(map, ft_lstnew(line));
	}
	close(file);
}

t_list	*parse_map(char *path)
{
	t_list	*map;

	read_map_lines(path, &map);
	
}

void	check_map(t_list *map)
{
	
}
