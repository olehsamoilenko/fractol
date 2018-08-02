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

t_dot			**init_values(void)
{
	int		i;
	int		j;
	t_dot	**values;
	float	delta_re;
	float	delta_im;

	delta_re = (float)(RE_MAX - RE_MIN) / (WIN_WIDTH - 1);
	delta_im = (float)(IM_MAX - IM_MIN) / (WIN_HEIGHT - 1);
	// printf("dre: %f dim: %f\n", delta_re, delta_im);
	values = (t_dot**)ft_memalloc(WIN_HEIGHT * sizeof(t_dot*));
	i = -1;
	while (++i < WIN_HEIGHT)
	{
		values[i] = (t_dot*)ft_memalloc(WIN_WIDTH * sizeof(t_dot));
		j = -1;
		while (++j < WIN_WIDTH)
		{
			values[i][j].c_re = 1.5 * (i - WIN_WIDTH / 2) * 2 / WIN_WIDTH;
			values[i][j].c_im = (j - WIN_HEIGHT / 2) * 2 / WIN_HEIGHT;
			// values[i][j].c_re = 0;
			// values[i][j].c_im = 0;
			// values[i][j].z_re = RE_MIN + delta_re * j;
			// values[i][j].z_im = IM_MAX - delta_im * i;
			values[i][j].z_re = 0;
			values[i][j].z_im = 0;
			// printf("(%i,%i) re: %f im: %f\n", i, j, values[i][j].re, values[i][j].im);
		}
	}
	return (values);
	
}

t_view			init(void)
{
	t_view	view;

	view.mlx_ptr = mlx_init();
	view.win_ptr = mlx_new_window(view.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "fractol");
	view.values = init_values();
	init_img(&view);
	return (view);
}
