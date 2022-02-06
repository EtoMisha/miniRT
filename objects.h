/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 19:56:13 by fbeatris          #+#    #+#             */
/*   Updated: 2022/02/06 20:32:50 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "minirt.h"

typedef struct s_ambient
{
	float	ratio;
	int		color;
}	t_ambient;

typedef struct s_camera
{
	// float		x;
	// float		y;
	// float		z;
	t_vector	point;
	t_vector	norm;
	int			fov;
}	t_camera;

typedef struct s_light
{
	// float			x;
	// float			y;
	// float			z;
	t_vector		point;
	float			brightness;
	int				color;
	struct s_light	*next;
}	t_light;

typedef struct s_sphere
{
	// float			x;
	// float			y;
	// float			z;
	t_vector		point;
	float			diameter;
	int				color;
	struct s_sphere	*next;
}	t_sphere;

typedef struct s_plane
{
	// float			x;
	// float			y;
	// float			z;
	t_vector		point;
	t_vector		norm;
	int				color;
	struct s_plane	*next;
}	t_plane;

typedef struct s_cylinder
{
	// float				x;
	// float				y;
	// float				z;
	t_vector			point;
	t_vector			norm;
	float				diameter;
	float				height;
	int					color;
	struct s_cylinder	*next;
}	t_cylinder;

#endif