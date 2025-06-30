/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 10:46:57 by thgaugai          #+#    #+#             */
/*   Updated: 2025/06/30 16:00:54 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void	ray_direction(t_data *data, t_player *player, t_ray *ray, int x)
{
	double	camera_x;

	//calcul de la direction du rayon
	camera_x = 2 * x / (double)data->size_x - 1;
	ray->dir_x = player->dir_x + player->plane_x * camera_x;
	ray->dir_y = player->dir_y + player->plane_y * camera_x;
	//calculer la distance que le rayon doit parcourir pour passer d'une ligne
	// verticale à la suivante (x) ou d'une ligne horizontale à la suivante (y).
	ray->delta_dist_x = (ray->dir_x == 0) ? 1e30 : fabs(1 / ray->dir_x);
	ray->delta_dist_y = (ray->dir_y == 0) ? 1e30 : fabs(1 / ray->dir_y);
}

static void	ray_distance(t_ray	*ray, t_player *player, int *map_x, int *map_y)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->x - *map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (*map_x + 1.0 - player->x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->y - *map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (*map_y + 1.0 - player->y) * ray->delta_dist_y;
	}
}

static void	check_hit_wall(t_data *data, t_ray *ray, int *map_x, int *map_y)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			*map_x += ray->step_x;
			ray->side = 0;// mur vertical (est / ouest)
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			*map_y += ray->step_y;
			ray->side = 1;//mur horizontal (sud / nord)
		}
		if (data->map[*map_y][*map_x] == '1')
			ray->hit = 1;
	}
}

static void	perpendicular_distance(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
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

void	raycasting(t_ray *ray, t_data *data)
{
	int	x;
	int	map_x;
	int	map_y;

	x = -1;
	while (++x < data->size_x)
	{
		ray->hit = 0;
		map_x = (int)data->player->x;
		map_y = (int)data->player->y;
		ray_direction(data, data->player, ray, x);
		ray_distance(ray, data->player, &map_x, &map_y);
		check_hit_wall(data, ray, &map_x, &map_y);
		perpendicular_distance(ray);
		draw_vertical_line(data->player, data, ray, x);
	}
}
