#include "minirt.h"


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

void	mouse_left(t_data* data, int x, int y, int id)
{
	t_vector	dir_pixel;
	t_vector	direction;
	float		dst;


	dst = WIN_WIDTH / (2 * tanf(data->camera->fov * M_PI / 360));  //расст от камеры (по нормали (0,0,1)) до окна
	dir_pixel = vector(dst, x - WIN_WIDTH / 2, -(y - WIN_HEIGHT / 2)); //вектор(до каждого пикселя) (x =(раст до окна)
	//, y =(х окна - 1/2окна), z = (- (y окна - 1/2 высоты окна)))

	direction = v_norm(v_sum(v_muls(data->camera->norm, dst), dir_pixel));//это вектор до пикселя!норм камеры( раст от кам до окн * нормаль камеры + вектор до пикселя)
	direction = rotate_dir(direction, data);//поворот камеры примен к каждому вектору до пикселя
	id = ft_select(data->objects, direction, data);
	if (id > -1)
	{
		if (data->select_obj > -1)
			data->objects[data->select_obj]->color = add_color(data->objects[data->select_obj]->color, -SELECT_COEF);
		data->objects[id]->color = add_color(data->objects[id]->color, SELECT_COEF);
		data->select_obj = id;
		remake_image(data);
		mlx_hook(data->mlx_window, 2, (1L << 0), key_hook, data->objects[id]);
	}
	else
		mlx_hook(data->mlx_window, 2, (1L << 0), key_hook, data->objects[0]);
}

void	mouse_right(t_data *data)
{
	// printf("data->light->id: %d\n", data->light->id);
	// printf("data->light->type: %d\n", data->light->type);
	// printf("data->select_obj: %d\n", data->select_obj);
	if (data->select_obj > -1)
		data->objects[data->select_obj]->color = add_color(data->objects[data->select_obj]->color, -SELECT_COEF);
	data->select_obj = data->light->id;
	// printf("data->select_obj: %d\n", data->select_obj);
	remake_image(data);
	mlx_hook(data->mlx_window, 2, (1L << 0), key_hook, data->light);

}

int	mouse_handler(int button, int x, int y, void *data1)
{
	t_data*		data;
	int			id = 0;

	data = (t_data*)data1;


	if (button == 1)
	{
		mouse_left(data, x, y, id);

	}
	if (button == 2)
		mouse_right(data);


	return 0;
}
