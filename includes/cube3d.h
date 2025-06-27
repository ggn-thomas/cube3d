/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgaugai <thgaugai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:47:20 by thgaugai          #+#    #+#             */
/*   Updated: 2025/06/27 14:12:05 by thgaugai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../gnl/get_next_line.h"
# include "../minilibx-linux/mlx.h"
# include "X11/X.h"
# include "X11/Xlib.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

# define IMG_WIDTH 40
# define SIZE_X 800
# define SIZE_Y 600
# define ESC 65307
# define W 13
# define S 1
# define A 0
# define D 2
# define LEFT_ARR 123
# define RIGHT_ARR 124

typedef struct s_param_map
{
	char			**map;
	int				length;
	int				width;
}					t_param_map;

typedef struct s_map
{
	char			*line;
	struct s_map	*next;
}					t_map;

typedef struct s_player
{
	double 			x; // postion du joueur
	double			y;
	double 			dir_x; // vecteur direction
	double			dir_y;
	double 			plane_x; // plan de projection
	double			plane_y;
	int				move_speed;
}					t_player;

typedef struct s_ray
{
	double			dir_x;
	double			dir_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			side_dist_x;
	double			side_dist_y;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	double			perp_wall_dist;
	int				screen_heigth;
}					t_ray;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	t_map			**map;
	int				draw_start;
	int				draw_end;
	void			*NO;
	void			*SO;
	void			*WE;
	void			*EA;
	int				C[3];
	int				F[3];
	int				size_x;
	int				size_y;
	int				line_length;
	int				bits_per_pixel;
	char			*img_data;
	t_player		*player;
	t_ray			*ray;
}					t_data;

void				error(char *mess);
int					ft_keypress(int keycode, t_data *data);
t_map				*ft_new_node(char *line);
void				ft_lstadd_back(t_map **lst, t_map *new);
void				ray(t_ray *ray, t_player *player, t_data *data);
void				init(t_map **map);
void				draw_vertical_line(t_player *player, t_data *data, t_ray *ray, int x);
int 				render(t_data *data);
void				raycasting(t_ray *ray, t_data *data);
void				wall_heigth(t_ray *ray, t_data *data);
int					get_texture_pixel(void *texture, int x, int y);
void    			*get_wall_texture(t_data *data, t_ray *ray);
#endif