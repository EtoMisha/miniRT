/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 21:14:38 by fbeatris          #+#    #+#             */
/*   Updated: 2022/02/11 19:35:24 by fbeatris         ###   ########.fr       */
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

void	move_camera(int key_code, t_data *data)
{
	if (key_code == 126)
		data->camera->point = v_sum(data->camera->point, \
			v_muls(data->camera->norm, MOVE_STEP));
	else if (key_code == 125)
		data->camera->point = v_sub(data->camera->point, \
			v_muls(data->camera->norm, MOVE_STEP));
	else if (key_code == 123)
		data->camera->point = v_sub(data->camera->point, \
			v_muls(v_mulv(data->camera->norm, vector(0, 0, -1)), MOVE_STEP));
	else if (key_code == 124)
		data->camera->point = v_sub(data->camera->point, \
			v_muls(v_mulv(data->camera->norm, vector(0, 0, 1)), MOVE_STEP));
}

void	change_camera(int key_code, t_data *data)
{
	if (key_code == 256)
		data->camera->fov += FOV_STEP;
	else if (key_code == 257)
		data->camera->fov -= FOV_STEP;
	else if (key_code == 13)
		data->angle_y += ROTATE_STEP;
	else if (key_code == 1)
		data->angle_y -= ROTATE_STEP;
	else if (key_code == 0)
		data->angle_z += ROTATE_STEP;
	else if (key_code == 2)
		data->angle_z -= ROTATE_STEP;
	else if (key_code >= 123 && key_code <= 126)
		move_camera(key_code, data);
	remake_image(data);
}

int	key_hook(int key_code, t_data *data)
{
	if (key_code == 53)
		exit_hook(key_code, data);
	else
		change_camera(key_code, data);
	// printf("%d\n", key_code);
	return (1);
}