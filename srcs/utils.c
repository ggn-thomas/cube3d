/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgaugai <thgaugai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:57:22 by thgaugai          #+#    #+#             */
/*   Updated: 2025/07/01 16:58:36 by thgaugai         ###   ########.fr       */
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

void	wall_heigth(t_ray *ray, t_data *data)
{
	int	line_heigth;

	// Protection contre division par zéro
	if (ray->perp_wall_dist <= 0.001)
		ray->perp_wall_dist = 0.001;
		
	line_heigth = (int)(data->size_y / ray->perp_wall_dist);
	data->draw_start = -line_heigth / 2 + data->size_y / 2;
	data->draw_end = line_heigth / 2 + data->size_y / 2;
	
	if (data->draw_start < 0)
		data->draw_start = 0;
	if (data->draw_end >= data->size_y)
		data->draw_end = data->size_y - 1;
		
	// DEBUG temporaire
	if (line_heigth <= 0)
		printf("ERROR: line_heigth=%d perp_dist=%.3f\n", line_heigth, ray->perp_wall_dist);
}