/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:08:15 by fbeatris          #+#    #+#             */
/*   Updated: 2022/02/08 22:23:34 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	specular(t_vector unit_l, t_vector norm, t_vector inter_point, t_data *data)
{
	float		coef_ref;
	float		bright;
	t_vector	unit_r;
	t_vector	reflect;

	coef_ref = 0.1;
	bright = data->light->brightness;
	reflect = v_sub(unit_l, v_mul(v_muls(v_mul(unit_l, norm), 2), norm));
	unit_r = v_sub(data->camera->point, inter_point);
	return (coef_ref * pow(fmax(v_scal(reflect, unit_r), 0), 16) * bright);
}

int	lighting(t_object *object, t_vector dir, t_data *data, float dist)
{
	int			color;
	t_vector	inter_point;
	t_vector	norm;
	t_vector	unit;
	float		coef;

	inter_point = v_sum(data->camera->point, v_muls(dir, dist));
	if (object->type == 0)
		norm = v_norm(v_sub(inter_point, object->point)); // нормаль для сферы
	if (object->type == 1)
		norm = v_norm(object->norm); // нормаль для плоскости
	unit = v_sub(data->light->point, inter_point);
	coef = v_scal(norm, unit) * data->light->brightness * LIGHT_COEF;
	color = add_color(object->color, coef);//, specular(unit, norm, inter_point, data));
	// color = specular(unit, norm, inter_point, data);
	return (color);
}
