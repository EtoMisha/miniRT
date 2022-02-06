/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 20:10:10 by fbeatris          #+#    #+#             */
/*   Updated: 2022/02/06 18:50:57 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	count_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

static void	clear_arr_line(char **arr, char *line)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	free(line);
}

static void	replace_delimeters(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\t' || line[i] == ',')
			line[i] = ' ';
		i++;
	}
}

static void	create_objects(char **arr, t_data *data)
{
	if (!ft_strcmp(arr[0], "A"))
		create_ambient(arr, data);
	else if (!ft_strcmp(arr[0], "C"))
		create_camera(arr, data);
	else if (!ft_strcmp(arr[0], "L"))
		create_light(arr, data);
	else if (!ft_strcmp(arr[0], "sp"))
		create_sphere(arr, data);
	else if (!ft_strcmp(arr[0], "pl"))
		create_plane(arr, data);
	else if (!ft_strcmp(arr[0], "cy"))
		create_cylinder(arr, data);
	else
		exit_error("Corrupted file");
}

void	parser(char *file_name, t_data *data)
{
	char	*line;
	int		fd;
	int		check_read;
	char	**arr;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		exit_error("Error while opening file");
	check_read = 1;
	while (check_read > 0)
	{
		check_read = get_next_line(fd, &line);
		if (check_read == -1)
			exit_error("Error while reading file");
		replace_delimeters(line);
		arr = ft_split(line, ' ');
		if (!arr)
			exit_error("Malloc error in split");
		if (arr[0])
			create_objects(arr, data);
		clear_arr_line(arr, line);
	}
	close (fd);
}
