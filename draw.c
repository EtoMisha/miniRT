/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 19:07:28 by fbeatris          #+#    #+#             */
/*   Updated: 2022/02/12 21:25:02 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// void	draw_pixel(t_img *img, int x, int y, int color)
// {
// 	char	*dest;

// 	if (x < WIN_WIDTH && x > 0 && y < WIN_HEIGHT && y > 0)
// 	{
// 		dest = img->address + (y * img->line_len + x * img->bpp / 8);
// 		*(unsigned int *)dest = color;
// 	}
// }


float	find_dist(t_object *object, t_vector start, t_vector direction)
{
	float	distance;

	distance = 0;
	if (object->type == 0)
		distance = inter_sphere(start, direction, object);
	else if (object->type == 1)
		distance = inter_plane(start, direction, object);
	else if (object->type == 2)
		distance = inter_cylinder(start, direction, object);
	return (distance);
}



int	intersection(t_object **objects, t_vector direction, t_data *data)
{
	int		i;
	float	distance;
	float	min_dist;
	int		color;

	min_dist = MAXFLOAT;
	color = BG_COLOR;
	i = 0;
	while (i < data->qty)
	{
		distance = find_dist(objects[i], data->camera->point, direction);
		if (distance > 0 && distance < min_dist)
		{
			min_dist = distance;
			color = lighting(objects[i], direction, data, distance);
		}
		i++;
	}
	return (color);
}



t_vector	rotate_dir(t_vector dir, t_data *data)
{
	float	n_x;
	float	n_y;
	float	n_z;
	float	a;
	///поворот камеры относительно каждой оси (х у)

	a = data->camera->angle_y;// угол по н
	n_x = dir.x * cos(a) - dir.z * sin(a);
	n_z = dir.x * sin(a) + dir.z * cos(a);
	dir = v_norm(vector(n_x, dir.y, n_z));
	a = data->camera->angle_z;//угол по z
	n_x = dir.x * cos(a) - dir.y * sin(a);
	n_y = dir.x * sin(a) + dir.y * cos(a);
	dir = v_norm(vector(n_x, n_y, dir.z));
	return (dir);
}


void	draw_loop(t_data *data)
{
	int			x;
	int			y;
	int			color;
	t_vector	dir_pixel;
	t_vector	direction;
	float		dst;
	char	*dest;

	y = 0;
	dst = WIN_WIDTH / (2 * tanf(data->camera->fov * M_PI / 360));  //расст от камеры (по нормали (0,0,1)) до окна
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{

			dir_pixel = vector(dst, x - WIN_WIDTH / 2, -(y - WIN_HEIGHT / 2)); //вектор(до каждого пикселя) (x =(раст до окна)
			//, y =(х окна - 1/2окна), z = (- (y окна - 1/2 высоты окна)))


			// dir_pixel = rotate_dir(dir_pixel, data);
			// data->camera->norm = rotate_dir(data->camera->norm, data);

			direction = v_norm(v_sum(v_muls(data->camera->norm, dst), dir_pixel));//это вектор до пикселя!норм камеры( раст от кам до окн * нормаль камеры + вектор до пикселя)
			direction = rotate_dir(direction, data);//поворот камеры примен к каждому вектору до пикселя
			color = intersection(data->objects, direction, data);//цвет = пересечение
			// draw_pixel(data->img, x, y, color);
			if (x < WIN_WIDTH && x > 0 && y < WIN_HEIGHT && y > 0)
			{
				dest = data->img->address + (y * data->img->line_len + x * data->img->bpp / 8);
				*(unsigned int *)dest = color;
			}
			x++;
		}
		y++;
	}
}
