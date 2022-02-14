/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:35:10 by fbeatris          #+#    #+#             */
/*   Updated: 2022/02/14 12:32:54 by ogarthar         ###   ########.fr       */
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
	// ft_putstr_fd("Exit\n", 1);
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
