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
	if (view->mouse_on)
	{
		view->mouse_x = x;
		view->mouse_y = y;
	}
	draw(view);
	return (0);
}

int			mouse_controls(int event, int x, int y, t_view *view)
{
	float	re_coord;
	float	im_coord;
	double	k;

	// x = 0;
	// y= 0;
	// x = WIN_WIDTH / 2;
	// y = WIN_HEIGHT / 2;
	if (event == MOUSE_UP || event == MOUSE_DOWN)
	{
		if (event == MOUSE_DOWN)
		{
			k = (float)10 / 9;

		}
		else
		{
			k = (float)9/ 10;

		}
		view->delta_im *= k;
		view->delta_re *= k;
		view->re_min = view->re_min + ((float)x / WIN_WIDTH) * view->delta_re / k * (1 - k);
		view->im_min = view->im_min - ((float)(WIN_HEIGHT - y) / WIN_HEIGHT) * view->delta_im / k * (1 - k);
		// printf("re_min: %f im_min: %f\n", view->re_min, view->im_min);

	}
	ft_bzero(view->img.img, WIN_WIDTH * WIN_HEIGHT * view->img.bits_per_pixel);
	draw(view);
	return (0);
}

int		key_hook(int key, void *v)
{
	t_view		*view;

	view = (t_view*)v;
	key == KEY_ESC ? exit(1) : 0;

	if (key == KEY_C)
		view->color = (view->color + 1) % 6;
	else if (key == KEY_SPACE)
		view->mouse_on = (view->mouse_on + 1) % 2;
	// float delta = view->re_max - view->re_min;

	if (key == KEY_LEFT)
		view->re_min -= 0.05 * view->delta_re;
	if (key == KEY_RIGHT)
		view->re_min += 0.05 * view->delta_re;
	if (key == KEY_UP)
		view->im_min -= 0.05 * view->delta_im;
	if (key == KEY_DOWN)
		view->im_min += 0.05 * view->delta_im;

	
	if (key == KEY_ONE)
		view->power = 1;
	if (key == KEY_TWO)
		view->power = 2;
	if (key == KEY_THREE)
		view->power = 3;
	if (key == KEY_FOUR)
		view->power = 4;
	if (key == KEY_FIVE)
		view->power = 5;

	key == KEY_PLUS ? view->depth += 1 : 0;
	if (key == KEY_MINUS)
	{
		if (view->depth != 0)
			view->depth -= 1;
	}
	// printf("re_min: %f im_min: %f\n", view->re_min, view->im_min);

	ft_bzero(view->img.img, WIN_WIDTH * WIN_HEIGHT * view->img.bits_per_pixel);
	draw(view);

	return (0);
}
