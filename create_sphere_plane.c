/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sphere_plane.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 00:00:21 by fbeatris          #+#    #+#             */
/*   Updated: 2022/02/06 20:33:57 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_sphere	*add_sphere(char **arr)
{
	t_sphere	*new;

	new = malloc(sizeof(t_sphere));
	if (!new)
		exit_error("Malloc error");
	new->point.x = ft_atof(arr[1]);
	new->point.y = ft_atof(arr[2]);
	new->point.z = ft_atof(arr[3]);
	new->diameter = ft_atof(arr[4]);
	new->color = create_rgb(ft_atoi(arr[5]), \
		ft_atoi(arr[6]), ft_atoi(arr[7]));
	new->next = NULL;
	return (new);
}

void	create_sphere(char **arr, t_data *data)
{
	t_sphere	*temp;

	if (count_arr(arr) != 8)
		exit_error("Currupted file");
	if (data->sphere == NULL)
		data->sphere = add_sphere(arr);
	else
	{
		temp = data->sphere;
		while (temp)
			temp = data->sphere->next;
		temp = add_sphere(arr);
	}	
}

static t_plane	*add_plane(char **arr)
{
	t_plane	*new;

	new = malloc(sizeof(t_plane));
	if (!new)
		exit_error("Malloc error");
	new->point.x = ft_atof(arr[1]);
	new->point.y = ft_atof(arr[2]);
	new->point.z = ft_atof(arr[3]);
	new->norm.x = ft_atof(arr[4]);
	new->norm.y = ft_atof(arr[5]);
	new->norm.z = ft_atof(arr[6]);
	new->color = create_rgb(ft_atoi(arr[7]), \
		ft_atoi(arr[8]), ft_atoi(arr[9]));
	new->next = NULL;
	return (new);
}

void	create_plane(char **arr, t_data *data)
{
	t_plane	*temp;

	if (count_arr(arr) != 10)
		exit_error("Currupted file");
	if (data->plane == NULL)
		data->plane = add_plane(arr);
	else
	{
		temp = data->plane;
		while (temp)
			temp = data->plane->next;
		temp = add_plane(arr);
	}	
}
