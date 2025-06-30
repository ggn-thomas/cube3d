/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:08:50 by thomas            #+#    #+#             */
/*   Updated: 2025/06/30 16:35:39 by thomas           ###   ########.fr       */
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
	if (!data->EA || !data->WE || !data->SO || !data->NO)
		error("Error: Image loading failed!", data);
	data->F[0] = 64;
	data->F[1] = 64;
	data->F[2] = 64;
	data->C[0] = 135;
	data->C[1] = 205;
	data->C[2] = 235;
	data->sprites_load = 1;
}

int	get_texture_pixel(void *texture, int x, int y)
{
	char	*data;
	int	bpp;
	int	size_line;
	int endian;

	bpp = 0;
	size_line = 0;
	endian = 0;
	data = mlx_get_data_addr(texture, &bpp, &size_line, &endian);
	return (*(int*)(data + (y * size_line + x * (bpp / 8))));
}

void    *get_wall_texture(t_data *data, t_ray *ray)
{
    if (ray->side == 0)
    {
        if (ray->dir_x > 0)
            return (data->EA);
        else
            return (data->WE);
    }
    else
    {
        if (ray->dir_y > 0)
            return (data->SO);
        else
            return (data->NO);
    }
}