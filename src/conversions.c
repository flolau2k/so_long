/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:39:35 by flauer            #+#    #+#             */
/*   Updated: 2023/07/17 14:11:11 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_point	px_to_pos(t_point rel_map_pos, t_point px)
{
	t_point	pos;
	t_point	rel_px;

	rel_px = add_pos(px, rel_map_pos);
	pos.x = rel_px.x / TILE_S;
	pos.y = rel_px.y / TILE_S;
	return (pos);
}

t_point	pos_to_px(t_point rel_map_pos, t_point pos)
{
	t_point	px;
	t_point	rel_pos;

	px.x = pos.x * TILE_S;
	px.y = pos.y * TILE_S;
	rel_pos = substract_point(px, rel_map_pos);
	return (rel_pos);
}

t_point	add_pos(t_point p1, t_point p2)
{
	t_point	ret;

	ret.x = p1.x + p2.x;
	ret.y = p1.y + p2.y;
	return (ret);
}

t_point	substract_point(t_point p1, t_point p2)
{
	t_point	ret;

	ret.x = p1.x - p2.x;
	ret.y = p1.y - p2.y;
	return (ret);
}

t_point	scalar_multiply(t_point p1, double scale)
{
	t_point	ret;

	ret.x = p1.x * scale;
	ret.y = p1.y * scale;
	return (ret);
}
