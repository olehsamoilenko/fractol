/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 15:10:52 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/02 15:10:53 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	pixel_put_img(t_view *view, int x, int y, int color)
{
	if (x <= 0 || x >= WIN_WIDTH || y <= 0 || y >= WIN_HEIGHT)
		return ;
	*(int *)(view->img.img + x * view->img.bits_per_pixel +
		y * view->img.size_line) = mlx_get_color_value(view->mlx_ptr, color);
}

int		rgb_to_color(unsigned char r, unsigned char g, unsigned char b)
{
	return (r << 16 | g << 8 | b);
}

void	draw(t_view *view)
{
	int		x;
	int		y;

	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			if (view->values[y][x].z_re * view->values[y][x].z_re -
				view->values[y][x].z_im * view->values[y][x].z_im < 4)
				pixel_put_img(view, x, y, rgb_to_color(200, 0, 0));
		}
	}
	mlx_put_image_to_window(view->mlx_ptr, view->win_ptr,
		view->img.img_ptr, 0, 0);
}
