/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:21:20 by thgaugai          #+#    #+#             */
/*   Updated: 2025/06/30 16:01:20 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	put_pixel_to_image(t_data *data, int x, int y, int color)
{
	char	*dst;
	int		offset;
	
	if (x < 0 || x >= data->size_x || y < 0 || y >= data->size_y)
		return ;
	offset = (y * data->line_length) + (x * (data->bits_per_pixel / 8));
	dst = data->img_data + offset;
	*(unsigned int*)dst = color;
}

int	create_color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	draw_vertical_line(t_player *player, t_data *data, t_ray *ray, int x)
{
	void	*texture;
	int	y;
	int tex_x;
	int	tex_y;
	int	color;
	double	wall_x;
	int	ceiling_color;
	int	floor_color;

	ceiling_color = create_color(data->C[0], data->C[1], data->C[2]);
	floor_color = create_color(data->F[0], data->F[1], data->F[2]);
	wall_heigth(ray, data);
	y = 0;
	tex_x = 0;
	tex_y = 0;
	color = 0;
	wall_x = 0;
	//dessiner le ciel
	while (y < data->draw_start)
	{
		put_pixel_to_image(data, x, y, ceiling_color);
		y++;
	}
	texture = get_wall_texture(data, ray);
	if (ray->side == 0)
		wall_x = player->y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = player->x + ray->perp_wall_dist * ray->dir_x;
	wall_x = wall_x - floor(wall_x);
	tex_x = (int)(wall_x * IMG_WIDTH);
	y = data->draw_start;
	while (y < data->draw_end)
	{
		tex_y = (int)((double)(y - data->draw_start) / (data->draw_end - data->draw_start) * IMG_WIDTH);
		color = get_texture_pixel(texture, tex_x, tex_y);
		put_pixel_to_image(data, x, y, color);
		y++;
	}
	//dessiner le sol
	y = data->draw_end;
	while (y < data->size_y)
	{
		put_pixel_to_image(data, x, y, floor_color);
		y++;
	}
}
