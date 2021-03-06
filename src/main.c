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

int			exit_func(void)
{
	exit(1);
}

static void	usage(void)
{
	ft_putstr("usage: ./fractol [fractal]\nAvaliable fractals:	mandelbrot,\n\
			julia,\n			burning_ship,\n			mandelbar,\n\
			brain,\n			feigenbaum,\n			leaf,\n\
			hyper\n");
	exit_func();
}

static int	fractal_exists(char *name)
{
	if (ft_strequ(name, "mandelbrot") || ft_strequ(name, "julia") ||
		ft_strequ(name, "burning_ship") || ft_strequ(name, "mandelbar") ||
		ft_strequ(name, "brain") || ft_strequ(name, "feigenbaum") ||
		ft_strequ(name, "leaf") || ft_strequ(name, "hyper"))
		return (1);
	return (0);
}

int			main(int args, char **argv)
{
	t_env	env;

	if (args != 2 || !fractal_exists(argv[1]))
		usage();
	env = init(argv[1]);
	draw(&env);
	mlx_hook(env.win_ptr, EVENT_KEYS, 0, key_hook, &env);
	mlx_hook(env.win_ptr, EVENT_CLOSE, 0, exit_func, NULL);
	mlx_hook(env.win_ptr, EVENT_MOUSE, 0, move_with_mouse, &env);
	mlx_mouse_hook(env.win_ptr, mouse_controls, &env);
	mlx_loop(env.mlx_ptr);
	return (0);
}
