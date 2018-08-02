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

void	iterate(t_view *view)
{
	int		i;
	int		j;
	t_dot	tmp;

	i = -1;
	while (++i < WIN_HEIGHT)
	{
		j = -1;
		while (++j < WIN_WIDTH)
		{
			tmp.z_re = view->values[i][j].z_re * view->values[i][j].z_re + view->values[i][j].c_re -
				view->values[i][j].z_im * view->values[i][j].z_im;
			tmp.z_im = 2 * view->values[i][j].z_re * view->values[i][j].z_im - view->values[i][j].c_im;
			view->values[i][j] = tmp;
		}
	}

}

int		main(int args, char **argv)
{
	t_view	view;

	if (args != 2 || !ft_strequ(argv[1], "Julia"))
	{
		ft_putstr("usage: ./fractol [fractal]\nAvaliable fractals: Julia\n");
		exit(0);
	}
	view = init();
	// draw(&view);
	// iterate(&view);
	mlx_hook(view.win_ptr, EVENT_KEYS, 0, &key_hook, &view);
	mlx_hook(view.win_ptr, EVENT_CLOSE, 0, &exit_func, 0);
	mlx_loop(view.mlx_ptr);
	return (0);
}
