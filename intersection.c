/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 20:40:15 by fbeatris          #+#    #+#             */
/*   Updated: 2022/02/10 21:39:20 by fbeatris         ###   ########.fr       */
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
	t = -(v_scal(v_sub(camera, plane->point), plane->norm)) \
		/ v_scal(dir, plane->norm);
	return (t);
}

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

float	inter_cylinder(t_vector ro, t_vector rd, t_object *cyl)
{
	float	ra = cyl->diameter / 2;
	t_vector pa = cyl->point;
	t_vector pb = v_sum(cyl->point, v_muls(cyl->norm, cyl->height)); 
	t_vector ca = v_sub(pb,pa);
    t_vector oc = v_sub(ro,pa);
    float caca = v_scal(ca,ca);
    float card = v_scal(ca,rd);
    float caoc = v_scal(ca,oc);
    float a = caca - card*card;
    float b = caca*v_scal( oc, rd) - caoc*card;
    float c = caca*v_scal( oc, oc) - caoc*caoc - ra*ra*caca;
    float h = b*b - a*c;
    if( h<0.0 ) return (0); //no intersection
    h = sqrt(h);
    float t = (-b-h)/a;
    // body
    float y = caoc + t*card;
    if( y>0.0 && y<caca ) return ( t);
    // caps
    t = (((y<0.0)?0.0:caca) - caoc)/card;
    if( fabs(b+a*t)<h ) return ( t);
    return (0); //no intersection
}
