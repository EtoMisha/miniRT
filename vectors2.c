/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 19:51:22 by fbeatris          #+#    #+#             */
/*   Updated: 2022/02/06 20:02:20 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	v_scal(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

float	v_len(t_vector a)
{
	return(sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

float	v_dist(t_vector a, t_vector b)
{
	return (v_len(v_sub(a, b)));
}

t_vector	v_norm(t_vector a)
{
	t_vector	result;
	float		len;

	len = v_len(a);
	result.x = a.x / len;
	result.y = a.y / len;
	result.z = a.z / len;
	return (result);
}
