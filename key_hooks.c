/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 21:14:38 by fbeatris          #+#    #+#             */
/*   Updated: 2022/02/13 20:38:32 by ogarthar         ###   ########.fr       */
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

t_vector	rotate_vector(t_vector vect, float alpha)
{
	float	new_y;
	float	new_z;

	new_y = vect.y * cos(alpha) + vect.z * sin(alpha);
	new_z = - vect.y * sin(alpha) + vect.z * cos(alpha);
	vect = v_norm(vector(vect.x, new_y, new_z));

	return (vect);
}

int	key_hook2(int key, t_object *obj)
{
	(void)obj;
	if (key == 69 && (obj->type == 0 || obj->type == 2))
	{
		obj->diameter += 10;
		obj->height += 10;
	}
	if (key == 78 && (obj->type == 0 || obj->type == 2) && obj->diameter > 10)
	{
		if (obj->type == 2 && obj->height > 10)
			obj->height -= 10;
		obj->diameter -= 10;
	}
	if (key == 85 && (obj->type == 1 || obj->type == 2))
		obj->norm = rotate_vector(obj->norm, 0.3);
	if (key == 92 && (obj->type == 1 || obj->type == 2))
		obj->norm = rotate_vector(obj->norm, -0.3);
	return 0;
}

int	key_hook(int key_code, t_object *obj)
{
	key_hook2(key_code, obj);
	if (key_code == 53)
		exit_hook(key_code, obj->data);
	else if (key_code == 256)
		obj->data->camera->fov += FOV_STEP;
	else if (key_code == 257)
		obj->data->camera->fov -= FOV_STEP;
	else if (key_code >= 123 && key_code <= 126)
		move_camera(key_code, obj->data);
	else if ((key_code >= 0 && key_code <= 2) || key_code == 13)
		rotate_camera(key_code, obj->data);

	if (key_code == 91)
		obj->point.x += 15;
	if (key_code == 84)
		obj->point.x -= 15;
	if (key_code == 86)
		obj->point.y -= 15;
	if (key_code == 88)
		obj->point.y += 15;
	if (key_code == 83)
		obj->point.z -= 15;
	if (key_code == 89)
		obj->point.z += 15;
	remake_image(obj->data);
	return (1);
}

