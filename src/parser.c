/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:06:41 by flauer            #+#    #+#             */
/*   Updated: 2023/07/11 14:30:56 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool	read_map_line(int file, int *num_lines, char ***map)
{
	char	*line;

	line = get_next_line(file);
	if (!line)
	{
		*map = malloc(sizeof(char *) * (*num_lines + 1));
		if (!*map)
			return (false);
		(*map)[*num_lines] = NULL;
		return (true);
	}
	++*num_lines;
	if (!read_map_line(file, num_lines, map))
		return (false);
	--*num_lines;
	(*map)[*num_lines] = line;
	return (true);
}

static void	find_start_pos(t_instance *inst)
{
	bool	found;
	t_point	pos;

	found = false;
	pos = (t_point){.x = 1, .y = 1};
	while (inst->map[pos.y])
	{
		while (inst->map[pos.y][pos.x])
		{
			if (inst->map[pos.y][pos.x] == 'P' && !found)
			{
				inst->map[pos.y][pos.x] = '0';
				inst->ppos = (t_point){.x = pos.x, .y = pos.y};
				found = true;
			}
			else if (inst->map[pos.y][pos.x] == 'P' && found)
				ft_err(inst, MULT_START);
			pos.x++;
		}
		pos.y++;
	}
}

static void	check_paths(t_instance *inst)
{
	t_point	pos;

	pos = (t_point){.x = 0, .y = 0};
	while (inst->map[pos.y])
	{
		while (inst->map[pos.y][pos.x])
		{
			if (inst->map[pos.y][pos.x] == 'C')
		}
	}
}

static bool	check_map(t_instance *inst)
{
	if (!inst->map[0])
		ft_err(inst, MAP_EMPTY);
	
	fill_rec(inst, '0', 'F', inst->ppos);
	check_paths(inst);
}

static bool	get_size(t_instance *inst)
{
	inst->size = (t_point){.x = 0, .y = 0};
	if (inst->map[0])
		ft_strlen(inst->map[0]);
	while (inst->map[inst->size.y])
	{
		if (ft_strlen(inst->map[inst->size.y]) != inst->size.x)
			ft_err(inst, MAP_INVALID);
	}
}

static void	fill_rec(t_instance *inst, char c1, char c2, t_point begin)
{
	if (inst->map[begin.y][begin.x] != c1)
		return ;
	inst->map[begin.y][begin.x] = c2;
	if (begin.y > 0)
		fill_rec(inst, c1, c2, (t_point){.x = begin.x, .y = begin.y - 1});
	if (begin.y < inst->size.y - 1)
		fill_rec(inst, c1, c2, (t_point){.x = begin.x, .y = begin.y + 1});
	if (begin.x > 0)
		fill_rec(inst, c1, c2, (t_point){.x = begin.x - 1, .y = begin.y});
	if (begin.x < inst->size.x - 1)
		fill_rec(inst, c1, c2, (t_point){.x = begin.x + 1, .y = begin.y});
}

void	parse_map(char *path, t_instance *inst)
{
	int		file;
	char	*line;
	int		num_lines;

	num_lines = 0;
	if (path
		&& ft_strncmp(path + ft_strlen(path) - ft_strlen(".ber"), ".ber", 4))
		ft_err(inst, MAP_EXT);
	file = open(path, O_RDONLY);
	read_map_line(file, &num_lines, &inst->map);
	close(file);
	check_map(inst);
}
