/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:08:15 by fbeatris          #+#    #+#             */
/*   Updated: 2022/02/12 16:36:51 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	specular_light(t_vector norm, t_vector dir, \
	t_vector inter_point, t_data *data)
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
		if (find_dist(data->objects[i], inter, dir) > 0 && obj->id != i && \
			data->objects[i]->type != 1) // костыль чтоб плоскость не отбрасывала тень
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
	float		drop;
	int			color;

	inter_point = v_sum(data->camera->point, v_muls(dir, dist));
	if (object->type == 0)
		norm = v_norm(v_sub(inter_point, object->point));
	if (object->type == 1)
		norm = v_norm(object->norm);
	if (object->type == 2)
		norm = cylinder_norm(object, inter_point); // нормаль для цилиндра неправильно считается
	drop = drop_shadow(inter_point, data, object);
	if (drop == 0)
		color = add_color(object->color, data->ambient->ratio * AMB_COEF \
			+ diff_light(norm, inter_point, data) * DIFF_COEF \
			+ specular_light(norm, dir, inter_point, data) * SPEC_COEF);
	else
		color = add_color(object->color, data->ambient->ratio * AMB_COEF \
			+ diff_light(norm, inter_point, data) * DIFF_COEF \
			+ drop * SHADOW_COEF * data->light->brightness);
	return (color);
}
