/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgaugai <thgaugai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:57:11 by thgaugai          #+#    #+#             */
/*   Updated: 2025/06/27 14:08:08 by thgaugai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	load_sprites(t_data *data)
{
	int	w;

	w = IMG_WIDTH;
	data->EA = mlx_xpm_file_to_image(data->mlx, "textures/wood.xpm", &w, &w);
	data->WE = mlx_xpm_file_to_image(data->mlx, "textures/wood.xpm", &w, &w);
	data->SO = mlx_xpm_file_to_image(data->mlx, "textures/wall_3.xpm", &w, &w);
	data->NO = mlx_xpm_file_to_image(data->mlx, "textures/wall_3.xpm", &w, &w);
	data->F[0] = 255;
	data->F[1] = 255;
	data->F[2] = 0;
	data->C[0] = 255;
	data->C[1] = 255;
	data->C[2] = 0;
}

t_ray	*ray_init(void)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (!ray)
		exit(EXIT_FAILURE);
	ray->delta_dist_x = 0;
	ray->delta_dist_y = 0;
	ray->dir_x = 0;
	ray->dir_y = 0;
	ray->hit = 0;
	ray->side = 0;
	ray->perp_wall_dist = 0;
	ray->side_dist_x = 0;
	ray->side_dist_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->screen_heigth = 0;
	return (ray);
}

t_data	data_init(t_map **map)
{
	t_data	data;

	data.player  = malloc(sizeof(t_player));
	if (!data.player)
		exit(EXIT_FAILURE);
	data.size_x = SIZE_X;
	data.size_y = SIZE_Y;
	data.player->x = 0;
	data.player->y = 0;
	data.player->dir_x = -1;
	data.player->dir_y = 0;
	data.player->plane_x = 0;
	data.player->plane_y = 0.66;
	data.img_data = 0;
	data.bits_per_pixel = 0;
	data.line_length = 0;
	data.mlx = mlx_init();
	if (!data.mlx)
		error("Error: Minilibx: Initializing failed!");
	data.map = map;
	data.win = mlx_new_window(data.mlx, data.size_x, data.size_y, "Cube3d");
	if (!data.win)
		error("Error: Minilibx: Window creation failed!");
	data.ray = ray_init();
	return (data);
}

void	init(t_map **map)
{
	t_data	data;

	data = data_init(map);
	load_sprites(&data);
	mlx_hook(data.win, 2, 1L << 0, ft_keypress, &data);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
}
