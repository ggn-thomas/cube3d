/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgaugai <thgaugai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:00:52 by thgaugai          #+#    #+#             */
/*   Updated: 2025/06/27 14:43:27 by thgaugai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int render(t_data *data)
{
    raycasting(data->ray, data);
    mlx_put_image_to_window(data->mlx, data->win, data->img_data, 0, 0);
    return 0;
}