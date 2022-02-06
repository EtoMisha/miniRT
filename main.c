/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 20:10:05 by fbeatris          #+#    #+#             */
/*   Updated: 2022/02/06 20:37:33 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	exit_error(char *message)
{
	printf("%s\n", message);
	exit(1);
}

int	exit_hook(int key_code, t_data *data)
{
	(void)key_code;
	(void)data;
	ft_putstr_fd("Exit\n", 1);
	exit(0);
}

void	make_window(t_img *img, t_data *data)
{
	data->mlx = mlx_init();
	data->mlx_window = mlx_new_window(data->mlx, \
		WIN_WIDTH, WIN_HEIGHT, "My beautiful miniRT window");
	img->ptr = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	img->address = mlx_get_data_addr(img->ptr, \
		&img->bpp, &img->line_len, &img->endian);
	draw_start(data);
	mlx_put_image_to_window(data->mlx, data->mlx_window, img->ptr, 0, 0);
	mlx_hook(data->mlx_window, 17, (1L << 0), exit_hook, data);
	mlx_loop(data->mlx);
}

void	default_values(t_data *data, t_img *img)
{
	data->mlx = NULL;
	data->mlx_window = NULL;
	data->img = img;
	data->ambient = NULL;
	data->camera = NULL;
	data->light = NULL;
	data->sphere = NULL;
	data->plane = NULL;
	data->cylinder = NULL;
}

void	print_objects(t_data *data)	//	delete
{
	if (data->ambient)
		printf("Ambient ratio %f, color %X\n", data->ambient->ratio, data->ambient->color);
	if (data->camera)
		printf("Camera x %f y %f z %f, nx %f ny %f nz %f, fov %d\n", \
			data->camera->point.x, data->camera->point.y, data->camera->point.z,\
			data->camera->norm.x, data->camera->norm.y, data->camera->norm.z, data->camera->fov);
	if (data->light)
		printf("Light x %f y %f z %f, brightness %f color %X\n", \
			data->light->point.x, data->light->point.y, data->light->point.z,\
			data->light->brightness, data->light->color);
	if (data->sphere)
		printf("Sphere x %f y %f z %f, diameter %f color %X\n", \
			data->sphere->point.x, data->sphere->point.y, data->sphere->point.z,\
			data->sphere->diameter, data->sphere->color);
	if (data->plane)
		printf("Plane x %f y %f z %f, nx %f ny %f nz %f, color %X\n", \
			data->plane->point.x, data->plane->point.y, data->plane->point.z,\
			data->plane->norm.x, data->plane->norm.y, data->plane->norm.z, data->plane->color);
	if (data->cylinder)
		printf("Cylinder x %f y %f z %f, nx %f ny %f nz %f, d %f, h %f, color %X\n", \
			data->cylinder->point.x, data->cylinder->point.y, data->cylinder->point.z,\
			data->cylinder->norm.x, data->cylinder->norm.y, data->cylinder->norm.z,\
			data->cylinder->diameter, data->cylinder->height, data->cylinder->color);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_img		img;

	if (argc == 2)
	{
		default_values(&data, &img);
		parser(argv[1], &data);
		// print_objects(&data);	//	delete
		make_window(&img, &data);
	}
}
