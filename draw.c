/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 19:07:28 by fbeatris          #+#    #+#             */
/*   Updated: 2022/02/09 19:14:26 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	draw_pixel(t_img *img, int x, int y, int color)
{
	char	*dest;

	if (x < WIN_WIDTH && x > 0 && y < WIN_HEIGHT && y > 0)
	{
		dest = img->address + (y * img->line_len + x * img->bpp / 8);
		*(unsigned int *)dest = color;
	}
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

void	draw_loop(t_data *data)
{
	int			x;
	int			y;
	int			color;
	t_vector	direction;
	float		dst;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH) // надо еще учесть направление камеры
		{
			dst = WIN_WIDTH / (2 * tanf(data->camera->fov / 2));
			direction = v_norm(vector(dst, \
				x - WIN_WIDTH / 2, -(y - WIN_HEIGHT / 2)));
			color = intersection(data->objects, direction, data);
			draw_pixel(data->img, x, y, color);
			x++;
		}
		y++;
	}
}
