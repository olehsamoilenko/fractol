/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 11:37:35 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/02 11:37:36 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	exit_func(void)
{
	exit(1);
}

void	usage(void)
{
	ft_putstr("usage: ./fractol [fractal]\nAvaliable fractals:	mandelbrot,\n\
			julia,\n			burning_ship,\n			mandelbar\n");
	exit(0);
}



int		main(int args, char **argv)
{
	t_view	view;

	if (args != 2)
	{
		usage();
	}
	view = init(argv[1]);
	draw(&view);
	mlx_hook(view.win_ptr, EVENT_KEYS, 0, key_hook, &view);
	mlx_hook(view.win_ptr, EVENT_CLOSE, 0, exit_func, 0);

	mlx_hook(view.win_ptr, EVENT_MOUSE, 0, move_with_mouse, &view); // ?
	mlx_mouse_hook(view.win_ptr, mouse_controls, &view);
	mlx_loop(view.mlx_ptr);
	return (0);
}
