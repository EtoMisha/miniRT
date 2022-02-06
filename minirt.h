/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 20:09:56 by fbeatris          #+#    #+#             */
/*   Updated: 2022/02/06 20:44:37 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIN_WIDTH 1600
# define WIN_HEIGHT 1200

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include "libft/libft.h"
# include "mlx/mlx.h"
# include "vectors.h"
# include "objects.h"

typedef struct s_img
{
	void	*ptr;
	char	*address;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_window;
	t_img		*img;
	t_ambient	*ambient;
	t_camera	*camera;
	t_light		*light;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
}	t_data;

typedef struct s_pixel
{
	float	x;
	float	y;
	int		color;
}	t_pixel;

void	parser(char *file_name, t_data *data);
int		count_arr(char **arr);
int		create_rgb(int r, int g, int b);

void	create_ambient(char **arr, t_data *data);
void	create_camera(char **arr, t_data *data);
void	create_light(char **arr, t_data *data);
void	create_sphere(char **arr, t_data *data);
void	create_plane(char **arr, t_data *data);
void	create_cylinder(char **arr, t_data *data);

void	draw_start(t_data *data);

void	exit_error(char *function);

#endif