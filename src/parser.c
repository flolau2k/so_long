/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:06:41 by flauer            #+#    #+#             */
/*   Updated: 2023/07/12 17:01:59 by flauer           ###   ########.fr       */
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

static bool	is_valid_char(char c)
{
	if (ft_strchr(VALID_CHARS, c))
		return (true);
	return (false);
}

static void	check_start(t_instance *inst, t_point pos)
{
	static bool	found;

	if (inst->map[pos.y][pos.x] == 'P' && !found)
	{
		found = true;
		inst->ppos = (t_point){.x = pos.x, .y = pos.y};
	}
	else if (inst->map[pos.y][pos.x] == 'P' && found)
		ft_err(inst, MULT_START);
}

static void	check_exit(t_instance *inst, t_point pos)
{
	static bool	found;

	if (inst->map[pos.y][pos.x] == 'E' && !found)
		found = true;
	else if (inst->map[pos.y][pos.x] == 'E' && found)
		ft_err(inst, MULT_EXIT);
}

static void	find_start_pos_and_check(t_instance *inst)
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
			check_start(inst, pos);
			check_exit(inst, pos);
			pos.x++;
		}
		pos.y++;
	}
}

static void	check_surrounding(t_instance *inst, t_point pos)
{
	if (!ft_strchr(CHECK_CHARS, inst->map_cpy[pos.y][pos.x]))
		return ;
	if (pos.y > 0 && inst->map_cpy[pos.y - 1][pos.x] == FILL_CHAR)
		return ;
	if (pos.y < inst->size.y - 1 && inst->map_cpy[pos.y + 1][pos.x] == FILL_CHAR)
		return ;
	if (pos.x > 0 && inst->map_cpy[pos.y][pos.x - 1] == FILL_CHAR)
		return ;
	if (pos.x < inst->size.x - 1 && inst->map_cpy[pos.y][pos.x + 1] == FILL_CHAR)
		return ;
	if (inst->map_cpy[pos.y][pos.x] == 'C')
		ft_err(inst, NO_ROUTE_C);
	else
		ft_err(inst, NO_ROUTE_E);
}

static void	check_paths(t_instance *inst)
{
	t_point	pos;

	pos = (t_point){.x = 0, .y = 0};
	while (pos.y < inst->size.y)
	{
		pos.x = 0;
		while (pos.x < inst->size.x)
		{
			check_surrounding(inst, pos);
			pos.x++;
		}
		pos.y++;
	}
}

static void	check_borders(t_instance *inst)
{
	t_point	pos;

	pos = (t_point){.x = 0, .y = 0};
	while (pos.y < inst->size.y)
	{
		if (pos.y == 0 || pos.y == inst->size.y - 1)
		{
			pos.x = 0;
			while (pos.x < inst->size.x)
			{
				if (inst->map_cpy[pos.y][pos.x] == FILL_CHAR)
					ft_err(inst, MAP_NC);
				pos.x++;
			}
		}
		else
		{
			if (inst->map_cpy[pos.y][0] == FILL_CHAR
				|| inst->map_cpy[pos.y][inst->size.x - 1] == FILL_CHAR)
				ft_err(inst, MAP_NC);
		}
		pos.y++;
	}
}

static void	get_size(t_instance *inst)
{
	inst->size = (t_point){.x = 0, .y = 0};
	inst->size.x = ft_strlen(inst->map[0]);
	inst->size.y++;
	while (inst->map[inst->size.y])
	{
		if (ft_strlen(inst->map[inst->size.y]) != inst->size.x)
			ft_err(inst, MAP_RECT);
		inst->size.y++;
	}
}

static char	**copy_map(t_instance *inst)
{
	char	**ret;
	int		i;

	i = 0;
	ret = malloc(sizeof(char *) * inst->size.y + 1);
	if (!ret)
		ft_err(inst, MALLOC_ERROR);
	ret[inst->size.y] = NULL;
	while (i < inst->size.y)
	{
		ret[i] = ft_strdup(inst->map[i]);
		if (!ret[i])
			ft_err(inst, MALLOC_ERROR);
		i++;
	}
	return (ret);
}

static void	check_map(t_instance *inst)
{
	if (!inst->map[0])
		ft_err(inst, MAP_EMPTY);
	get_size(inst);
	find_start_pos_and_check(inst);
	inst->map_cpy = copy_map(inst);
	fill_rec(inst, inst->ppos);
	check_borders(inst);
	check_paths(inst);
}

static void	fill_rec(t_instance *inst, t_point begin)
{
	if (!ft_strchr(MOVABLE_CHARS, inst->map_cpy[begin.y][begin.x]))
		return ;
	inst->map_cpy[begin.y][begin.x] = FILL_CHAR;
	if (begin.y > 0)
		fill_rec(inst, (t_point){.x = begin.x, .y = begin.y - 1});
	if (begin.y < inst->size.y - 1)
		fill_rec(inst, (t_point){.x = begin.x, .y = begin.y + 1});
	if (begin.x > 0)
		fill_rec(inst, (t_point){.x = begin.x - 1, .y = begin.y});
	if (begin.x < inst->size.x - 1)
		fill_rec(inst, (t_point){.x = begin.x + 1, .y = begin.y});
}

void	parse_map(const char *path, t_instance *inst)
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
	free_map(&inst->map_cpy);
}
