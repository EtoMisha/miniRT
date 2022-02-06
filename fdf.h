/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 16:12:36 by fbeatris          #+#    #+#             */
/*   Updated: 2021/10/16 21:20:15 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define DEF_COLOR0 0x00FFFFFF
# define DEF_COLOR1 0x00FF0000
# define DEF_COLOR2 0x000000FF
# define DEF_COLOR_BG 0x00212121

# define DEF_ANGLE 0.523599
# define DEF_ROTATE_Z 0
# define Z_HEIGHT 5

# define SHIFT_STEP 20
# define ZOOM_STEP 0.1
# define ROTATE_STEP 0.1

# define WIN_WIDTH 1600
# define WIN_HEIGHT 1200

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include "get_next_line.h"
# include "libft/libft.h"
# include "mlx/mlx.h"

typedef struct s_point
{
	float		x;
	float		y;
	float		z;
	int			color;
}	t_point;

typedef struct s_map
{
	int		width;
	int		height;
	t_point	**vertex;
	int		shift_x;
	int		shift_y;
	float	angle;
	float	rotate_z;
	float	def_zoom;
	float	zoom;
	int		iso_flag;
}	t_map;

typedef struct s_img
{
	void	*ptr;
	char	*address;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_mlx_vars
{
	void	*mlx;
	void	*mlx_window;
	t_img	*img;
	t_map	*map;

}	t_mlx_vars;

void	free_map(t_map *map);
int		exit_w_error(char *msg, t_map *map, int need_free);
int		exit_w_free(char **map_str, t_map *map);
float	ft_abs(float x);
float	ft_max(float x1, float x2);

int		count_size(char *filename, t_map *map);
int		read_map(char *filename, t_map *map);

void	set_zoom(t_map *map, t_point *point0, t_point *point1);
void	set_isometry(t_map *map, t_point *point0, t_point *point1);
void	set_shift(t_map *map, t_point *point0, t_point *point1);
void	set_rotation_x(t_map *map, t_point *point0, t_point *point1);
void	set_rotation_y(t_map *map, t_point *point0, t_point *point1);
void	set_rotation_z(t_map *map, t_point *point0, t_point *point1);

void	draw(t_map *map, t_img *img, t_mlx_vars *vars);
void	draw_lines(t_map *map, t_img *img);

int		key_hook(int key_code, t_mlx_vars *vars);
void	hook_exit(t_mlx_vars *vars);
void	hook_move(int key_code, t_mlx_vars *vars);
void	hook_zoom_rotate(int key_code, t_mlx_vars *vars);
void	hook_views(int key_code, t_mlx_vars *vars);
void	remake_image(t_mlx_vars *vars);

#endif