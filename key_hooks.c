/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 21:14:38 by fbeatris          #+#    #+#             */
/*   Updated: 2022/02/12 17:43:38 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	remake_image(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img->ptr);
	data->img->ptr = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->img->address = mlx_get_data_addr(data->img->ptr, \
		&data->img->bpp, &data->img->line_len, &data->img->endian);
	draw_loop(data);
	mlx_put_image_to_window(data->mlx, data->mlx_window, data->img->ptr, 0, 0);
}

t_vector	rotate_z(t_vector dir, float a)
{
	float	n_x;
	float	n_y;

	n_x = dir.x * cos(a) - dir.y * sin(a);
	n_y = dir.x * sin(a) + dir.y * cos(a);
	dir = v_norm(vector(n_x, n_y, dir.z));
	return (dir);
}

t_vector	rotate_y(t_vector dir, float a)
{
	float	n_x;
	float	n_z;

	n_x = dir.x * cos(a) - dir.z * sin(a);
	n_z = dir.x * sin(a) + dir.z * cos(a);
	dir = v_norm(vector(n_x, dir.y, n_z));
	return (dir);
}

void	rotate_camera(int key_code, t_data *data)
{
	if (key_code == 13)
	{
		data->camera->angle_y += ROTATE_STEP;
		data->camera->dir = rotate_y(data->camera->dir, ROTATE_STEP);
	}
	else if (key_code == 1)
	{
		data->camera->angle_y -= ROTATE_STEP;
		data->camera->dir = rotate_y(data->camera->dir, -ROTATE_STEP);
	}
	else if (key_code == 0)
	{
		data->camera->angle_z -= ROTATE_STEP;
		data->camera->dir = rotate_z(data->camera->dir, -ROTATE_STEP);
	}
	else if (key_code == 2)
	{
		data->camera->angle_z += ROTATE_STEP;
		data->camera->dir = rotate_z(data->camera->dir, ROTATE_STEP);
	}
}

void	move_camera(int key_code, t_data *data)
{
	if (key_code == 126)
		data->camera->point = v_sum(data->camera->point, \
			v_muls(data->camera->dir, MOVE_STEP));
	else if (key_code == 125)
		data->camera->point = v_sub(data->camera->point, \
			v_muls(data->camera->dir, MOVE_STEP));
	else if (key_code == 123)
		data->camera->point = v_sub(data->camera->point, \
			v_muls(v_mulv(data->camera->dir, vector(0, 0, -1)), MOVE_STEP));
	else if (key_code == 124)
		data->camera->point = v_sub(data->camera->point, \
			v_muls(v_mulv(data->camera->dir, vector(0, 0, 1)), MOVE_STEP));
}

int	key_hook(int key_code, t_data *data)
{
	if (key_code == 53)
		exit_hook(key_code, data);
	else if (key_code == 256)
		data->camera->fov += FOV_STEP;
	else if (key_code == 257)
		data->camera->fov -= FOV_STEP;
	else if (key_code >= 123 && key_code <= 126)
		move_camera(key_code, data);
	else if ((key_code >= 0 && key_code <= 2) || key_code == 13)
		rotate_camera(key_code, data);
	// printf("%d\n", key_code);
	else
		return (1);
	remake_image(data);
	return (1);
}