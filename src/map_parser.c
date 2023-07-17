/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:06:41 by flauer            #+#    #+#             */
/*   Updated: 2023/07/17 18:18:59 by flauer           ###   ########.fr       */
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

static int	check_start_count(t_instance *inst, t_point pos)
{
	static int	count;

	if (inst->map[pos.y][pos.x] == PLAYER_CHAR && count == 0)
	{
		count++;
		inst->ppos = (t_point){.x = pos.x, .y = pos.y};
	}
	else if (inst->map[pos.y][pos.x] == PLAYER_CHAR && count > 0)
		ft_err(inst, MULT_START);
	return (count);
}

static int	check_exit_count(t_instance *inst, t_point pos)
{
	static int	count;

	if (inst->map[pos.y][pos.x] == EXIT_CHAR && count == 0)
		count++;
	else if (inst->map[pos.y][pos.x] == EXIT_CHAR && count > 0)
		ft_err(inst, MULT_EXIT);
	return (count);
}

void	find_start_pos_and_check(t_instance *inst)
{
	t_point	pos;
	int		num_e;
	int		num_p;

	pos = (t_point){.x = 0, .y = 0};
	while (pos.y < inst->size.y)
	{
		pos.x = 0;
		while (pos.x < inst->size.x)
		{
			if (!ft_strchr(VALID_CHARS, inst->map[pos.y][pos.x]))
				ft_err(inst, INV_CHAR);
			num_p = check_start_count(inst, pos);
			num_e = check_exit_count(inst, pos);
			if (inst->map[pos.y][pos.x] == COLL_CHAR)
				inst->num_c++;
			pos.x++;
		}
		pos.y++;
	}
	if (num_p == 0)
		ft_err(inst, NO_START);
	if (num_e == 0)
		ft_err(inst, NO_EXIT);
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
	if (file == -1)
		ft_err(inst, strerror(errno));
	if (!read_map_line(file, &num_lines, &inst->map))
		ft_err(inst, strerror(errno));
	close(file);
	check_map(inst);
	free_map(&inst->map_cpy);
}
