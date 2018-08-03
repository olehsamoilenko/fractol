/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 14:13:37 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/02 14:13:40 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		init_img(t_view *view)
{
	view->img.img_ptr = mlx_new_image(view->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	view->img.img = mlx_get_data_addr(view->img.img_ptr,
		&view->img.bits_per_pixel, &view->img.size_line, &view->img.endian);
	view->img.bits_per_pixel /= 8;
}

t_view			init(void)
{
	t_view	view;

	view.mlx_ptr = mlx_init();
	view.win_ptr = mlx_new_window(view.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "fractol");

	view.depth = 20;

	// view.move_x = 0;
	// view.move_y = 0;

	// view.mouse_x = 0.5 * WIN_HEIGHT;
	// view.mouse_y = 0.5 * WIN_WIDTH;

	view.re_min = -2;
	view.delta_re = 4;
	view.im_min = -1;
	view.delta_im = 2;
	init_img(&view);
	return (view);
}
