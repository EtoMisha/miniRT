/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 20:40:15 by fbeatris          #+#    #+#             */
/*   Updated: 2022/02/06 20:46:33 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pixel	inter_sphere(t_vector camera, t_vector direction, \
	t_vector center, float radius)
{
	float		b;
	float		c;
	float		h;
	t_pixel		result;

	b = v_scal(camera, direction);
	c = v_scal(camera, camera) - radius * radius;
	h = b * b - c;
	if (h < 0)
	{
		result.x = -1;
		result.y = 0;
		return (result);
	} 
	h = sqrt(h);
	result.x = -b - h;
	result.y = -b + h;
	return (result);
}