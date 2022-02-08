/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 20:40:15 by fbeatris          #+#    #+#             */
/*   Updated: 2022/02/08 22:40:47 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	inter_sphere2(float b, float d)
{
	float	t1;
	float	t2;
	float	min_t;
	float	max_t;
	float	t;

	t1 = -b + sqrtf(d);
	t2 = -b - sqrtf(d);
	min_t = fminf(t1, t2);
	max_t = fmaxf(t1, t2);
	if (min_t >= 0)
		t = min_t;
	else
		t = max_t;
	return (t);
}

float	inter_sphere(t_vector camera, t_vector dir, t_object *sphere)
{
	float		radius;
	float		b;
	float		c;
	float		d;
	t_vector	k;

	radius = sphere->diameter / 2;
	k = v_sub(camera, sphere->point);
	b = v_scal(k, dir);
	c = v_scal(k, k) - radius * radius;
	d = b * b - c;
	if (d >= 0)
		return (inter_sphere2(b, d));
	else
		return (0);
}

float	inter_plane(t_vector camera, t_vector dir, t_object *plane)
{
	float	t;
	float	dist;

	dist = v_dist(camera, plane->point);
	t = -(v_scal(camera, plane->norm) + dist) / v_scal(dir, plane->norm);
	return (t);
}

float	inter_cylinder(t_vector camera, t_vector dir, t_object *cyl)
{
	t_vector	oc;
	t_vector	ca;
	t_vector	pa;
	t_vector	pb;
	float		radius;
	float		caca;
	float		card;
	float		caoc;
	float		a;
	float		b;
	float		c;
	float		h;
	float		t;
	float		y;

	radius = cyl->diameter / 2;
	pa = cyl->point;
	pb = v_sum(cyl->point, v_muls(cyl->norm, cyl->height));
	
	ca = v_sub(pb, pa);
	oc = v_sub(camera, pa);
	caca = v_scal(ca, ca);
	card = v_scal(cyl->norm, dir);
	caoc = v_scal(cyl->norm, oc);
	
	a = caca - card * card;
	b = caca * v_scal(oc, dir) - caoc * card;
	c = caca * v_scal(oc, oc) - caoc * caoc - radius * radius * caca;
	h = b * b - a * c;
	if (h < 0)
		return (0);
	h = sqrtf(h);
	t = (-b - h) / a;
	y = caoc + t * card;
	if (y > 0 && y < caca)
		return (t);
	if (y < 0)
		return ((0 - caoc) / card);
	else
		return ((caca - caoc) / card);
	if (fabsf(b + a * t) < h)
		return (t);
	return (0);

}

// vec2 cylIntersect( in vec3 ro, in vec3 rd, in vec3 cb, in vec3 ca, float cr )
// {
//     vec3  oc = ro - cb;
//     float card = dot(ca,rd);
//     float caoc = dot(ca,oc);
//     float a = 1.0 - card*card;
//     float b = dot( oc, rd) - caoc*card;
//     float c = dot( oc, oc) - caoc*caoc - cr*cr;
//     float h = b*b - a*c;
//     if( h<0.0 ) return vec2(-1.0); //no intersection
//     h = sqrt(h);
//     return vec2(-b-h,-b+h)/a;
// }