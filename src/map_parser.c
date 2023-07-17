/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:06:41 by flauer            #+#    #+#             */
/*   Updated: 2023/07/17 14:45:15 by flauer           ###   ########.fr       */
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
	(*num_lines)++;
	if (!read_map_line(file, num_lines, map))
		return (false);
	(*num_lines)--;
	(*map)[*num_lines] = ft_strtrim(line, "\n");
	free(line);
	return (true);
}

static void	check_start_count(t_instance *inst, t_point pos)
{
	static bool	found;

	if (inst->map[pos.y][pos.x] == PLAYER_CHAR && !found)
	{
		found = true;
		inst->ppos = (t_point){.x = pos.x, .y = pos.y};
	}
	else if (inst->map[pos.y][pos.x] == PLAYER_CHAR && found)
		ft_err(inst, MULT_START);
}

static void	check_exit_count(t_instance *inst, t_point pos)
{
	static bool	found;

	if (inst->map[pos.y][pos.x] == EXIT_CHAR && !found)
		found = true;
	else if (inst->map[pos.y][pos.x] == EXIT_CHAR && found)
		ft_err(inst, MULT_EXIT);
}

void	find_start_pos_and_check(t_instance *inst)
{
	t_point	pos;
	char	c;

	pos = (t_point){.x = 0, .y = 0};
	while (pos.y < inst->size.y)
	{
		pos.x = 0;
		while (pos.x < inst->size.x)
		{
			c = inst->map[pos.y][pos.x];
			if (!ft_strchr(VALID_CHARS, inst->map[pos.y][pos.x]))
				ft_err(inst, INV_CHAR);
			check_start_count(inst, pos);
			check_exit_count(inst, pos);
			if (inst->map[pos.y][pos.x] == COLL_CHAR)
				inst->num_c++;
			pos.x++;
		}
		pos.y++;
	}
	if (inst->num_c == 0)
		ft_err(inst, NO_COLL);
}

void	parse_map(const char *path, t_instance *inst)
{
	int		file;
	int		num_lines;

	num_lines = 0;
	if (path
		&& ft_strncmp(path + ft_strlen(path) - ft_strlen(".ber"), ".ber", 4))
		ft_err(inst, MAP_EXT);
	file = open(path, O_RDONLY);
	if (!read_map_line(file, &num_lines, &inst->map))
		ft_err(inst, strerror(errno));
	close(file);
	check_map(inst);
	free_map(&inst->map_cpy);
}
