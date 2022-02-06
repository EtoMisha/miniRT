/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 00:01:18 by fbeatris          #+#    #+#             */
/*   Updated: 2022/02/06 20:33:41 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_cylinder	*add_cylinder(char **arr)
{
	t_cylinder	*new;

	new = malloc(sizeof(t_cylinder));
	if (!new)
		exit_error("Malloc error");
	new->point.x = ft_atof(arr[1]);
	new->point.y = ft_atof(arr[2]);
	new->point.z = ft_atof(arr[3]);
	new->norm.x = ft_atof(arr[4]);
	new->norm.y = ft_atof(arr[5]);
	new->norm.z = ft_atof(arr[6]);
	new->diameter = ft_atof(arr[7]);
	new->height = ft_atof(arr[8]);
	new->color = create_rgb(ft_atoi(arr[9]), \
		ft_atoi(arr[10]), ft_atoi(arr[11]));
	new->next = NULL;
	return (new);
}

void	create_cylinder(char **arr, t_data *data)
{
	t_cylinder	*temp;

	if (count_arr(arr) != 12)
		exit_error("Currupted file");
	if (data->cylinder == NULL)
		data->cylinder = add_cylinder(arr);
	else
	{
		temp = data->cylinder;
		while (temp)
			temp = data->cylinder->next;
		temp = add_cylinder(arr);
	}	
}
