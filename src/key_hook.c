/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 18:01:23 by osamoile          #+#    #+#             */
/*   Updated: 2018/07/24 18:01:35 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			move_with_mouse(int x, int y, t_view *view)
{
	return (0);
}

int			mouse_controls(int event, int x, int y, t_view *view)
{
	float	re_coord;
	float	im_coord;


	x = 0;
	y= 0;
	// x = WIN_WIDTH / 2;
	// y = WIN_HEIGHT / 2;
	if (event == MOUSE_UP || event == MOUSE_DOWN)
	{
		re_coord = view->re_min + ((float)x / WIN_WIDTH) * view->delta_re;
		im_coord = view->im_min + ((WIN_HEIGHT - (float)y) / WIN_HEIGHT) * view->delta_im;
		if (event == MOUSE_UP)
		{
			view->delta_re *= (float)9 / 10;
			view->delta_im *= (float)9 / 10;
		}
		else
		{
			view->delta_re *= (float)10 / 9;
			view->delta_im *= (float)10 / 9;
		}
		view->re_min = re_coord - ((float)x / WIN_WIDTH) * view->delta_re;
		view->im_min = im_coord - ((WIN_HEIGHT - (float)y) / WIN_HEIGHT) * view->delta_im;
		printf("re_min: %f im_min: %f\n", view->re_min, view->im_min);
		// view->min_re = view->min_re + x / WIN_WIDTH * 0.1;
	}
	ft_bzero(view->img.img, WIN_WIDTH * WIN_HEIGHT * view->img.bits_per_pixel);
	draw_mandelbrot(view);
	return (0);
}

int		key_hook(int key, void *v)
{
	t_view		*view;

	view = (t_view*)v;
	key == KEY_ESC ? exit(1) : 0;
	if (key == KEY_I)
	{
		view->depth++;
		printf("depth: %i\n", view->depth);
	}

	// float delta = view->re_max - view->re_min;

	if (key == KEY_LEFT)
		view->re_min -= 0.05 * view->delta_re;
	if (key == KEY_RIGHT)
		view->re_min += 0.05 * view->delta_re;
	if (key == KEY_UP)
		view->im_min += 0.05 * view->delta_im;
	if (key == KEY_DOWN)
		view->im_min -= 0.05 * view->delta_im;


	// key == KEY_PLUS ? view->zoom *= 2 : 0;
	// if (key == KEY_MINUS)
	// {
	// 	if (view->zoom != 1)
	// 		view->zoom /= 2;
	// }
	printf("re_min: %f im_min: %f\n", view->re_min, view->im_min);

	ft_bzero(view->img.img, WIN_WIDTH * WIN_HEIGHT * view->img.bits_per_pixel);
	draw_mandelbrot(view);

	return (0);
}
