/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:08:15 by fbeatris          #+#    #+#             */
/*   Updated: 2022/02/10 20:50:16 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	specular_light(t_vector norm, t_vector dir, t_vector inter_point, t_data *data)
{
	float		bright;
	t_vector	reflect;
	t_vector	spot;

	bright = data->light->brightness;
	spot = v_norm(v_sub(data->light->point, inter_point));
	reflect = v_norm(v_sub(dir, v_muls(norm, 2 * v_scal(norm, dir))));
	return (pow(fmax(v_scal(reflect, spot), 0), 32) * bright);
}

float	diff_light(t_vector norm, t_vector inter_point, t_data *data)
{
	t_vector	spot;

	spot = v_norm(v_sub(data->light->point, inter_point));
	return (v_scal(norm, spot) * data->light->brightness);
}

float	drop_shadow(t_vector inter, t_data *data, t_object *obj)
{
	int			i;
	t_vector	dir;

	dir = v_norm(v_sub(data->light->point, inter));
	i = 0;
	while (i < data->qty)
	{
		if (find_dist(data->objects[i], inter, dir) > 0 && obj->id != i)
		{
			return (-1);
		}
		i++;
	}
	return (0);
}

int	lighting(t_object *object, t_vector dir, t_data *data, float dist)
{
	t_vector	inter_point;
	t_vector	norm;
	float		diff;
	float		specular;
	float		drop;
	int			color;

	inter_point = v_sum(data->camera->point, v_muls(dir, dist));
	if (object->type == 0)
		norm = v_norm(v_sub(inter_point, object->point));
	if (object->type == 1)
		norm = v_norm(object->norm);
	if (object->type == 2)
		norm = cylinder_norm(object, dir, inter_point, data); // нормаль для цилиндра неправильно считается
	diff = diff_light(norm, inter_point, data);
	specular = specular_light(norm, dir, inter_point, data);
	drop = drop_shadow(inter_point, data, object);
	if (drop == 0)
		color = add_color(object->color, data->ambient->ratio * 10 + diff * 200 + specular * 70);
	else
		color = add_color(object->color, data->ambient->ratio * 10 + drop * data->light->brightness);
	return (color);
}