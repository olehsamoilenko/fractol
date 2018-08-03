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
	// if (event == MOUSE_LEFT)
	// {
	// 	printf("left %i %i\n", x, y);
	// }
	// if (event == MOUSE_RIGHT)
	// {
	// 	printf("right\n");
	// }
	view->mouse_x = WIN_HEIGHT / ((float)WIN_HEIGHT / x);
	view->mouse_y = WIN_WIDTH / ((float)WIN_WIDTH / y);
	if (event == MOUSE_UP)
	{
		view->zoom *= 2;
		
	}
	if (event == MOUSE_DOWN)
	{
		if (view->zoom != 1)
			view->zoom /= 2;
	}
	// ft_bzero(view->img.img, WIN_WIDTH * WIN_HEIGHT * view->img.bits_per_pixel);
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
	key == KEY_LEFT ? view->move_x -= 0.1 / view->zoom : 0;
	key == KEY_RIGHT ? view->move_x += 0.1 / view->zoom : 0;
	key == KEY_UP ? view->move_y -= 0.1 / view->zoom : 0;
	key == KEY_DOWN ? view->move_y += 0.1 / view->zoom : 0;

	key == KEY_PLUS ? view->zoom *= 2 : 0;
	if (key == KEY_MINUS)
	{
		if (view->zoom != 1)
			view->zoom /= 2;
	}

	ft_bzero(view->img.img, WIN_WIDTH * WIN_HEIGHT * view->img.bits_per_pixel);
	draw_mandelbrot(view);

	return (0);
}
