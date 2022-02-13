/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 19:07:28 by fbeatris          #+#    #+#             */
/*   Updated: 2022/02/13 17:19:09 by fbeatris         ###   ########.fr       */
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

t_vector	cylinder_norm(t_object *cyl, t_vector inter)
{
	t_vector	norm;
	t_vector	top_center;
	float		t;
	t_vector	pt;

	top_center = v_sum(cyl->point, v_muls(cyl->norm, cyl->height));
	if (v_len(v_sub(inter, cyl->point)) < cyl->diameter / 2)
		norm = v_muls(cyl->norm, -1);
	else if (v_len(v_sub(inter, top_center)) < cyl->diameter / 2)
		norm = cyl->norm;
	else
	{
		t = v_scal(v_sub(inter, cyl->point), cyl->norm);
		pt = v_sum(cyl->point, v_muls(cyl->norm, t));
		norm = v_norm(v_sub(inter, pt));
	}
	return (norm);
}

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

t_vector find_dir(float dst, float x, float y, t_vector norm)
{
	t_vector	a;
	t_vector	b;
	t_vector	c;
	t_vector	dir;

	a = vector(dst, x - WIN_WIDTH / 2, -(y - WIN_HEIGHT / 2));
	b = vector(-(x - WIN_WIDTH / 2), dst, -(y - WIN_HEIGHT / 2));
	c = vector(-(y - WIN_HEIGHT / 2), x - WIN_WIDTH / 2, dst);
	dir = v_sum3(v_muls(a, norm.x), v_muls(b, norm.y), v_muls(c, norm.z));
	return (dir);
}

void	draw_loop(t_data *data)
{
	int			x;
	int			y;
	int			color;
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
			direction = find_dir(dst, x, y, data->camera->norm);//это вектор до пикселя!норм камеры( раст от кам до окн * нормаль камеры + вектор до пикселя)
			//, y =(х окна - 1/2окна), z = (- (y окна - 1/2 высоты окна)))
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
