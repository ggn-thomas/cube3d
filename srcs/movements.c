/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:45:18 by thgaugai          #+#    #+#             */
/*   Updated: 2025/06/30 16:31:16 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	ft_forward(t_player *player, t_data *data)
{
	if (data->map[(int)player->y][(int)(player->x + player->dir_x * player->move_speed)] != '1')
		player->x += player->dir_x * player->move_speed;	
	if (data->map[(int)(player->y + player->dir_y * player->move_speed)][(int)player->x] != '1')
		player->y += player->dir_y * player->move_speed;
}

void	ft_backward(t_player *player, t_data *data)
{
	if (data->map[(int)player->y][(int)(player->x - player->dir_x * player->move_speed)] != '1')
		player->x -= player->dir_x * player->move_speed;
	if (data->map[(int)(player->y - player->dir_y * player->move_speed)][(int)player->x] != '1')
		player->y -= player->dir_y * player->move_speed;
}

void	ft_leftward(t_player *player, t_data *data)
{
	double	left_x = -player->dir_y;
	double	left_y = player->dir_x;

	if (data->map[(int)player->y][(int)(player->x + left_x * player->move_speed)] != '1')
		player->x += left_x * player->move_speed;
	if (data->map[(int)(player->y + left_y * player->move_speed)][(int)player->x] != '1')
		player->y += left_y * player->move_speed;
}

void	ft_rightward(t_player *player, t_data *data)
{
	double right_x = player->dir_y;
	double right_y = -player->dir_x;

	if (data->map[(int)player->y][(int)(player->x + right_x * player->move_speed)] != '1')
		player->x += right_x * player->move_speed;
	if (data->map[(int)(player->y + right_y * player->move_speed)][(int)player->x] != '1')
		player->y += right_y * player->move_speed;
}

void	rotate_left(t_player *player)
{
	double	speed_rot;
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	speed_rot = 0.1;
	player->dir_x = player->dir_x * cos(speed_rot) - player->dir_y * sin(speed_rot);
	player->dir_y = old_dir_x * sin(speed_rot) + player->dir_y * cos(speed_rot);
	player->plane_x = player->plane_x * cos(speed_rot) - player->plane_y * sin(speed_rot);
	player->plane_y = old_plane_x * sin(speed_rot) + player->plane_y * cos(speed_rot); 
}

void	rotate_right(t_player *player)
{
	double	speed_rot;
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	speed_rot = 0.1;
	player->dir_x = player->dir_x * cos(-speed_rot) - player->dir_y * sin(-speed_rot);
	player->dir_y = old_dir_x * sin(-speed_rot) + player->dir_y * cos(-speed_rot);
	player->plane_x = player->plane_x * cos(-speed_rot) - player->plane_y * sin(-speed_rot);
	player->plane_y = old_plane_x * sin(-speed_rot) + player->plane_y * cos(-speed_rot); 
}

int	ft_keypress(int keycode, t_data *data)
{
	if (keycode == ESC)
		ft_exit(data);
	else if (keycode == W)
		ft_forward(data->player, data);
	else if (keycode == S)
		ft_backward(data->player, data);
	else if (keycode == A)
		ft_leftward(data->player, data);
	else if (keycode == D)
		ft_rightward(data->player, data);
	else if (keycode == LEFT_ARR)
		rotate_left(data->player);
	else if (keycode == RIGHT_ARR)
		rotate_right(data->player);
	return (0);
}




