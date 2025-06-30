/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:00:52 by thgaugai          #+#    #+#             */
/*   Updated: 2025/06/30 16:52:15 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int render(t_data *data)
{
    mlx_clear_window(data->mlx, data->win);
    raycasting(data->ray, data);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    return (0);
}