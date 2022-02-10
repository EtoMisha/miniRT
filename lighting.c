/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:08:15 by fbeatris          #+#    #+#             */
/*   Updated: 2022/02/10 17:18:47 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	specular_light(t_vector norm, t_vector dir, t_vector inter_point, t_data *data)
{
	float		coef_ref;
	float		bright;
	t_vector	reflect;
	t_vector	view;
	t_vector	spot;

	coef_ref = 0.05;
	bright = data->light->brightness;
	spot = v_sub(data->light->point, inter_point);
	view = v_sub(data->camera->point, inter_point);
	reflect = v_sub(dir, v_muls(norm, 2 * v_scal(norm, dir)));
	return (pow(fmax(v_scal(reflect, spot) * coef_ref, 0), 2) * bright);
}

float	diff_light(t_vector norm, t_vector inter_point, t_data *data)
{
	t_vector	spot;

	spot = v_sub(data->light->point, inter_point);
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
			return (-50);
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
		norm = v_norm(v_sub(inter_point, object->point)); // нормаль для сферы
	if (object->type == 1)
		norm = v_norm(object->norm); // нормаль для плоскости
	if (object->type == 2)
		norm = cylinder_norm(object, dir, inter_point, data); // нормаль для цилиндра (похоже неправильно считается)
	diff = diff_light(norm, inter_point, data);
	specular = specular_light(norm, dir, inter_point, data); //недостаточный блик почему-то
	drop = drop_shadow(inter_point, data, object);
	if (drop == 0)
		color = add_color(object->color, data->ambient->ratio + diff + specular);
	else
		color = add_color(object->color, diff + drop);
	return (color);
}