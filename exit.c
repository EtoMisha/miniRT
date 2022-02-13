/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:35:10 by fbeatris          #+#    #+#             */
/*   Updated: 2022/02/12 21:44:05 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	exit_error(char *message)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(message, 1);
	ft_putstr_fd("\n", 1);
	exit(1);
}

int	exit_hook(int key_code, t_data *data)
{
	(void)key_code;
	(void)data;
	ft_putstr_fd("Exit\n", 1);
	exit(0);
}

// int	exit_hook_esc(int key_code, t_data *data)
// {
// 	(void)data;
// 	if (key_code == 53)
// 	{
// 		ft_putstr_fd("Exit\n", 1);
// 		exit(0);
// 	}
// 	return (1);
// }
