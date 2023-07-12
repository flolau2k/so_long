/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:46:40 by flauer            #+#    #+#             */
/*   Updated: 2023/07/12 15:09:04 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_hook(void *param)
{
	t_instance	*inst;

	inst = param;
	if (mlx_is_key_down(inst->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(inst->mlx);
	if (mlx_is_key_down(inst->mlx, MLX_KEY_W))
		inst->img.player->instances[0].y -= 5;
	if (mlx_is_key_down(inst->mlx, MLX_KEY_S))
		inst->img.player->instances[0].y += 5;
	if (mlx_is_key_down(inst->mlx, MLX_KEY_A))
		inst->img.player->instances[0].x -= 5;
	if (mlx_is_key_down(inst->mlx, MLX_KEY_D))
		inst->img.player->instances[0].x += 5;
}

mlx_image_t	*png_to_image(t_instance *inst, char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	texture = mlx_load_png(path);
	if (!texture)

	img = mlx_texture_to_image(inst->mlx, texture);
	if (!img)
	{
		mlx_close_window(inst->mlx);
		puts(mlx_strerror(mlx_errno));
		exit (EXIT_FAILURE);
	}
}

void	render_map(t_instance *inst)
{
	inst->texture = mlx_load_png(PLAYER);
	inst->image = mlx_texture_to_image(inst->mlx, inst->texture);
	if (!inst->image || mlx_image_to_window(inst->mlx, inst->image, 0, 0) == -1)
	{
		mlx_close_window(inst->mlx);
		puts(mlx_strerror(mlx_errno));
		exit (EXIT_FAILURE);
	}
	if (!inst->image || mlx_image_to_window(inst->mlx, inst->image, 32, 32) == -1)
	{
		mlx_close_window(inst->mlx);
		puts(mlx_strerror(mlx_errno));
		exit (EXIT_FAILURE);
	}
}

void	init_mlx(t_instance *inst)
{
	inst->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!inst->mlx)
	{
		puts(mlx_strerror(mlx_errno));
		exit (EXIT_FAILURE);
	}
}

int32_t	main(int32_t argc, const char *argv[])
{
	t_instance	inst;

	inst = (t_instance){.mlx = NULL, .texture = NULL,
						.map = NULL, .map_cpy = NULL};
	if (argc < 2)
		return (EXIT_FAILURE);
	parse_map(argv[1], &inst);
	init_mlx(&inst);
	render_map(&inst);

	mlx_loop_hook(inst.mlx, &ft_hook, &inst);
	mlx_loop(inst.mlx);
	mlx_terminate(inst.mlx);
	return (EXIT_SUCCESS);
}
