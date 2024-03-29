/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:23:21 by flauer            #+#    #+#             */
/*   Updated: 2023/07/17 13:25:52 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

mlx_image_t	*png_to_image(t_instance *inst, char *path, uint32_t size)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	texture = mlx_load_png(path);
	if (!texture)
		ft_err(inst, mlx_strerror(mlx_errno));
	img = mlx_texture_to_image(inst->mlx, texture);
	if (!img)
		ft_err(inst, mlx_strerror(mlx_errno));
	mlx_delete_texture(texture);
	if (size > 0)
		mlx_resize_image(img, size, size);
	return (img);
}

void	load_images(t_instance *inst)
{
	inst->img.player = png_to_image(inst, PLAYER, TILE_S * 0.8);
	inst->img.wall = png_to_image(inst, WALL, TILE_S);
	inst->img.floor = png_to_image(inst, FLOOR, TILE_S);
	inst->img.exit_c = png_to_image(inst, EXIT_C, TILE_S);
	inst->img.exit_o = png_to_image(inst, EXIT_O, TILE_S);
	inst->img.coll_c = png_to_image(inst, COLL_C, TILE_S);
	inst->img.coll_o = png_to_image(inst, COLL_O, TILE_S);
}

void	my_im_to_window(t_instance *inst, mlx_image_t *img, t_point pos)
{
	t_point	px;

	px = pos_to_px(inst->rel_map_pos, pos);
	if (mlx_image_to_window(inst->mlx, img, px.x, px.y) == -1)
		ft_err(inst, mlx_strerror(mlx_errno));
}

void	put_image_to_window(t_instance *inst, t_point pos)
{
	char	c;

	c = inst->map[pos.y][pos.x];
	if (c == FLOOR_CHAR || c == PLAYER_CHAR)
		my_im_to_window(inst, inst->img.floor, pos);
	else if (c == WALL_CHAR)
		my_im_to_window(inst, inst->img.wall, pos);
	else if (c == COLL_CHAR)
	{
		my_im_to_window(inst, inst->img.floor, pos);
		my_im_to_window(inst, inst->img.coll_o, pos);
		my_im_to_window(inst, inst->img.coll_c, pos);
	}
	else if (c == EXIT_CHAR)
	{
		my_im_to_window(inst, inst->img.floor, pos);
		my_im_to_window(inst, inst->img.exit_o, pos);
		my_im_to_window(inst, inst->img.exit_c, pos);
	}
}

void	render_map(t_instance *inst)
{
	t_point	pos;

	load_images(inst);
	inst->psize.x = inst->img.player->width;
	inst->psize.y = inst->img.player->height;
	pos = (t_point){.x = 0, .y = 0};
	while (pos.y < inst->size.y)
	{
		pos.x = 0;
		while (pos.x < inst->size.x)
		{
			put_image_to_window(inst, pos);
			pos.x++;
		}
		pos.y++;
	}
	my_im_to_window(inst, inst->img.player, inst->ppos);
}
