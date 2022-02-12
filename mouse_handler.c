#include "minirt.h"

int	key_hook1(int key_code, t_object *obj)
{
	if (key_code == 91)
		obj->point.x += 5;
	// else if (key_code == 256)
	// 	data->camera->fov += FOV_STEP;
	// else if (key_code == 257)
	// 	data->camera->fov -= FOV_STEP;
	// else if (key_code >= 123 && key_code <= 126)
	// 	move_camera(key_code, data);
	// else if ((key_code >= 0 && key_code <= 2) || key_code == 13)
	// 	rotate_camera(key_code, data);
	// // printf("%d\n", key_code);
	// else
	// 	return (1);
	// remake_image(data);
	return (1);
}

int	ft_select(t_object **objects, t_vector direction, t_data *data)
{
	int		i;
	float	distance;
	float	min_dist;
	int		id;

	id = -1;
	min_dist = MAXFLOAT;
	i = 0;
	while (i < data->qty)
	{
		distance = find_dist(objects[i], data->camera->point, direction);
		if (distance > 0 && distance < min_dist)
		{
			min_dist = distance;
			id = i;
		}
		i++;
	}
	return (id);
}

int	mouse_handler(int button, int x, int y, void *data1)
{
	t_vector	dir_pixel;
	t_vector	direction;
	float		dst;
	t_data*		data;
	int id;


	data = (t_data*)data1;

	printf("%d	%d	%d\n", button, x, y);

	dst = WIN_WIDTH / (2 * tanf(data->camera->fov * M_PI / 360));  //расст от камеры (по нормали (0,0,1)) до окна
	dir_pixel = vector(dst, x - WIN_WIDTH / 2, -(y - WIN_HEIGHT / 2)); //вектор(до каждого пикселя) (x =(раст до окна)
	//, y =(х окна - 1/2окна), z = (- (y окна - 1/2 высоты окна)))

	direction = v_norm(v_sum(v_muls(data->camera->norm, dst), dir_pixel));//это вектор до пикселя!норм камеры( раст от кам до окн * нормаль камеры + вектор до пикселя)
	direction = rotate_dir(direction, data);//поворот камеры примен к каждому вектору до пикселя
	id = ft_select(data->objects, direction, data);
	if (id > -1)
	{
		data->objects[id]->color = add_color(data->objects[id]->color, SELECT_COEF);
		remake_image(data);
		data->objects[id]->color = add_color(data->objects[id]->color, -SELECT_COEF);
	}
	mlx_hook(data->mlx_window, 2, (1L << 0), key_hook1, data->objects[id]);

	return 0;
}
