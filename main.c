/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 20:10:05 by fbeatris          #+#    #+#             */
/*   Updated: 2022/02/16 13:56:01 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_usage(void)
{
	char	*buffer;
	int		fd;

	fd = open("usage.txt", O_RDONLY);
	while (get_next_line(fd, &buffer))
	{
		ft_putstr_fd(buffer, 1);
		ft_putchar_fd('\n', 1);
	}
}

void	make_window(t_img *img, t_data *data)
{
	data->mlx = mlx_init();
	data->mlx_window = mlx_new_window(data->mlx, \
		WIN_WIDTH, WIN_HEIGHT, "My beautiful miniRT window");
	img->ptr = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	img->address = mlx_get_data_addr(img->ptr, \
		&img->bpp, &img->line_len, &img->endian);
	draw_loop(data);
	mlx_put_image_to_window(data->mlx, data->mlx_window, img->ptr, 0, 0);
	mlx_hook(data->mlx_window, 17, (1L << 0), exit_hook, data);
	mlx_hook(data->mlx_window, 2, (1L << 0), key_hook, data->objects[0]);
	mlx_mouse_hook(data->mlx_window, mouse_handler, data);
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
	data->objects = NULL;
	data->qty = 0;
	data->select_obj = -1;
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_img		img;

	if (argc == 2)
	{
		default_values(&data, &img);
		parser(argv[1], &data);
		if (!data.ambient || !data.camera || !data.light)
			exit_error("Corrupted file");
		print_usage();
		make_window(&img, &data);
	}
}
