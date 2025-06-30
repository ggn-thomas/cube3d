/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:07:40 by thgaugai          #+#    #+#             */
/*   Updated: 2025/06/30 16:50:36 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	error(char *mess, t_data *data)
{
	printf("%s\n", mess);
	if (data)
		ft_exit(data);
	exit(EXIT_FAILURE);
}

void	destroy_sprites(t_data *data)
{
	mlx_destroy_image(data->mlx, data->NO);
	mlx_destroy_image(data->mlx, data->SO);
	mlx_destroy_image(data->mlx, data->EA);
	mlx_destroy_image(data->mlx, data->WE);
	//free(data->C);
	//free(data->F);
}

void	ft_free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i++])
		free(map[i]);
	free(map);
}

void	ft_exit(t_data *data)
{
	if (data->map)
		ft_free_map(data->map);
	if (data->player)
		free(data->player);
	if (data->mlx)
		free(data->mlx);
	if (data->ray)
		free(data->ray);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	if (data->sprites_load == 1)
		destroy_sprites(data);
	exit(EXIT_SUCCESS);
}

int	close_window(t_data *data)
{
	ft_exit(data);
	exit(EXIT_SUCCESS);
	return (0);
}



