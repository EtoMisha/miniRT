/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 19:07:28 by fbeatris          #+#    #+#             */
/*   Updated: 2022/02/06 20:47:29 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	draw_pixel(t_img *img, float x, float y, int color)
{
	char	*dest;

	if (x < WIN_WIDTH && x > 0 && y < WIN_HEIGHT && y > 0)
	{
		dest = img->address + ((int)y * img->line_len + (int)x * img->bpp / 8);
		*(unsigned int *)dest = color;
	}
}

void	draw_start(t_data *data)
{
	draw_pixel(data->img, 100, 100, 0xFFFFFF);
	
}