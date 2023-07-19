/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:06:41 by flauer            #+#    #+#             */
/*   Updated: 2023/07/19 09:28:57 by flauer           ###   ########.fr       */
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

static void	check_cell(t_instance *inst, t_point pos, int *num_p, int *num_e)
{
	if (!ft_strchr(VALID_CHARS, inst->map[pos.y][pos.x]))
		ft_err(inst, INV_CHAR);
	*num_p = check_start_count(inst, pos);
	*num_e = check_exit_count(inst, pos);
	if (inst->map[pos.y][pos.x] == COLL_CHAR)
		inst->num_c++;
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
			check_cell(inst, pos, &num_p, &num_e);
			pos.x++;
		}
		pos.y++;
	}
	if (num_p == 0)
		ft_err(inst, NO_START);
	if (num_e == 0)
		ft_err(inst, NO_EXIT);
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
	if (file == -1)
		ft_err(inst, strerror(errno));
	if (!read_map_line(file, &num_lines, &inst->map))
		ft_err(inst, strerror(errno));
	close(file);
	get_size(inst);
	find_start_pos_and_check(inst);
	inst->map_cpy = copy_map(inst);
	fill_rec(inst, inst->ppos);
	check_borders(inst);
	check_paths(inst);
	free_map(&inst->map_cpy);
}
