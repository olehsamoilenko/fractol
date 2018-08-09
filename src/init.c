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



// int	iter_mandelbrot(t_dot dot, t_view *view, int power)
// {
// 	int		iter;
// 	float	tmp_re;
// 	float	tmp_im;

// 	dot.z_im = 0;
// 	dot.z_re = 0;
// 	iter = -1;
// 	while (++iter < view->depth)
// 	{
// 		if (dot.z_re * dot.z_re + dot.z_im * dot.z_im > 4)
// 			break ;
// 		if (power == 1)
// 		{
// 			tmp_re = dot.z_re + dot.c_re;
// 			tmp_im = dot.z_im + dot.c_im;
// 		}
// 		else if (power == 2)
// 		{
// 			tmp_re = dot.z_re * dot.z_re - dot.z_im * dot.z_im + dot.c_re;
// 			tmp_im = 2 * dot.z_re * dot.z_im + dot.c_im;
// 		}
// 		else if (power == 3)
// 		{
// 			tmp_re = mult(dot.z_re, 3) - 3 * dot.z_re * mult(dot.z_im, 2) + dot.c_re;
// 			tmp_im = 3 * mult(dot.z_re, 2) * dot.z_im - mult(dot.z_im, 3) + dot.c_im;
// 		}
// 		else if (power == 4)
// 		{
// 			tmp_re = mult(dot.z_re, 4) + mult(dot.z_im, 4) - 6 * mult(dot.z_re, 2) * mult(dot.z_im, 2) + dot.c_re;
// 			tmp_im = 4 * dot.z_im * mult(dot.z_re, 3) - 4 * mult(dot.z_im, 3) * dot.z_re + dot.c_im;
// 		}
// 		else if (power == 5)
// 		{
// 			tmp_re = 5 * mult(dot.z_im, 4) * dot.z_re - 10 * mult(dot.z_im, 2) * mult(dot.z_re, 3) + mult(dot.z_re, 5) + dot.c_re;
// 			tmp_im = mult(dot.z_im, 5) - 10 * mult(dot.z_im, 3) * mult(dot.z_re, 2) + 5 * mult(dot.z_re, 4) * dot.z_im + dot.c_im;
// 		}
// 		dot.z_re = tmp_re;
// 		dot.z_im = tmp_im;
// 	}
// 	return (iter);
// }



// int	iter_julia_1(t_dot dot, t_view *view)
// {
// 	int		iter;
// 	float	tmp_re;
// 	float	tmp_im;

// 	dot.z_im = dot.c_im;
// 	dot.z_re = dot.c_re;
// 	iter = -1;
// 	while (++iter < view->depth)
// 	{
// 		if (dot.z_re * dot.z_re + dot.z_im * dot.z_im > 4)
// 			break ;
// 		tmp_re = dot.z_re + (float)(view->mouse_x) / WIN_WIDTH;
// 		tmp_im = dot.z_im + (float)(view->mouse_y) / WIN_HEIGHT;
// 		dot.z_re = tmp_re;
// 		dot.z_im = tmp_im;
// 	}
// 	return (iter);
// }

// int	iter_julia_2(t_dot dot, t_view *view)
// {
// 	int		iter;
// 	float	tmp_re;
// 	float	tmp_im;

// 	dot.z_im = dot.c_im;
// 	dot.z_re = dot.c_re;
// 	iter = -1;
// 	while (++iter < view->depth)
// 	{
// 		if (dot.z_re * dot.z_re + dot.z_im * dot.z_im > 4)
// 			break ;
// 		tmp_re = mult(dot.z_re, 2) - mult(dot.z_im, 2) + (float)(view->mouse_x) / WIN_WIDTH;
// 		tmp_im = 2 * dot.z_im * dot.z_re + (float)(view->mouse_y) / WIN_HEIGHT;
// 		dot.z_re = tmp_re;
// 		dot.z_im = tmp_im;
// 	}
// 	return (iter);
// }

// int	iter_julia_3(t_dot dot, t_view *view)
// {
// 	int		iter;
// 	float	tmp_re;
// 	float	tmp_im;

// 	dot.z_im = dot.c_im;
// 	dot.z_re = dot.c_re;
// 	iter = -1;
// 	while (++iter < view->depth)
// 	{
// 		if (mult(dot.z_re, 2) + mult(dot.z_im, 2) > 4)
// 			break ;
// 		tmp_re = mult(dot.z_re, 3) - 3 * dot.z_re * mult(dot.z_im, 2) + (float)(view->mouse_x) / WIN_WIDTH;
// 		tmp_im = 3 * mult(dot.z_re, 2) * dot.z_im - mult(dot.z_im, 3) + (float)(view->mouse_y) / WIN_HEIGHT;
// 		dot.z_re = tmp_re;
// 		dot.z_im = tmp_im;
// 	}
// 	return (iter);
// }

// int	iter_burning_ship_2(t_dot dot, t_view *view)
// {
// 	int		iter;
// 	float	tmp_re;
// 	float	tmp_im;

// 	dot.z_im = 0;
// 	dot.z_re = 0;
// 	iter = -1;
// 	while (++iter < view->depth)
// 	{
// 		if (dot.z_re * dot.z_re + dot.z_im * dot.z_im > 4)
// 			break ;
// 		tmp_re = dot.z_re * dot.z_re - dot.z_im * dot.z_im + dot.c_re;
// 		tmp_im = 2 * dot.z_re * dot.z_im + dot.c_im;
// 		dot.z_re = fabs(tmp_re);
// 		dot.z_im = fabs(tmp_im);
// 	}
// 	return (iter);
// }


// int	iter_burning_ship_3(t_dot dot, t_view *view)
// {
// 	int		iter;
// 	float	tmp_re;
// 	float	tmp_im;

// 	dot.z_im = 0;
// 	dot.z_re = 0;
// 	iter = -1;
// 	while (++iter < view->depth)
// 	{
// 		if (mult(dot.z_re, 2) + mult(dot.z_im, 2) > 4)
// 			break ;
// 		tmp_re = mult(dot.z_re, 3) - 3 * dot.z_re * mult(dot.z_im, 2) + dot.c_re;
// 		tmp_im = 3 * mult(dot.z_re, 2) * dot.z_im - mult(dot.z_im, 3) + dot.c_im;
// 		dot.z_re = fabs(tmp_re);
// 		dot.z_im = fabs(tmp_im);
// 	}
// 	return (iter);
// }

// int	iter_mandelbar_1(t_dot dot, t_view *view)
// {
// 	int		iter;
// 	float	tmp_re;
// 	float	tmp_im;

// 	dot.z_im = 0;
// 	dot.z_re = 0;
// 	iter = -1;
// 	while (++iter < view->depth)
// 	{
// 		if (dot.z_re * dot.z_re + dot.z_im * dot.z_im > 4)
// 			break ;
// 		tmp_re = dot.z_re;
// 		tmp_im = dot.z_im;
// 		dot.z_re = tmp_re + dot.c_re;
// 		dot.z_im = -tmp_im + dot.c_im;
// 	}
// 	return (iter);
// }

// int	iter_mandelbar_2(t_dot dot, t_view *view)
// {
// 	int		iter;
// 	float	tmp_re;
// 	float	tmp_im;

// 	dot.z_im = 0;
// 	dot.z_re = 0;
// 	iter = -1;
// 	while (++iter < view->depth)
// 	{
// 		if (dot.z_re * dot.z_re + dot.z_im * dot.z_im > 4)
// 			break ;
// 		tmp_re = dot.z_re * dot.z_re - dot.z_im * dot.z_im;
// 		tmp_im = 2 * dot.z_re * dot.z_im;
// 		dot.z_re = tmp_re + dot.c_re;
// 		dot.z_im = -tmp_im + dot.c_im;
// 	}
// 	return (iter);
// }

// int	iter_mandelbar_5(t_dot dot, t_view *view)
// {
// 	int		iter;
// 	float	tmp_re;
// 	float	tmp_im;

// 	dot.z_im = 0;
// 	dot.z_re = 0;
// 	iter = -1;
// 	while (++iter < view->depth)
// 	{
// 		if (dot.z_re * dot.z_re + dot.z_im * dot.z_im > 4)
// 			break ;
// 		tmp_re = 5 * mult(dot.z_im, 4) * dot.z_re - 10 * mult(dot.z_im, 2) * mult(dot.z_re, 3) + mult(dot.z_re, 5);
// 		tmp_im = mult(dot.z_im, 5) - 10 * mult(dot.z_im, 3) * mult(dot.z_re, 2) + 5 * mult(dot.z_re, 4) * dot.z_im;
// 		dot.z_re = tmp_re + dot.c_re;
// 		dot.z_im = -tmp_im + dot.c_im;
// 	}
// 	return (iter);
// }

t_view			init(char *name)
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
	view.mouse_x = WIN_HEIGHT / 2;
	view.mouse_y = WIN_WIDTH / 2;
	view.mouse_on = 0;
	view.power = 2;
	view.color = 0;
	if (ft_strequ(name, "mandelbrot"))
	{
		view.iter_func[0] = &iter_mandelbrot_1;
		view.iter_func[1] = &iter_mandelbrot_2;
		view.iter_func[2] = &iter_mandelbrot_3;
		view.iter_func[3] = &iter_mandelbrot_4;
		view.iter_func[4] = &iter_mandelbrot_5;
	}
	else if (ft_strequ(name, "julia"))
	{
		view.iter_func[0] = &iter_julia_1;
		view.iter_func[1] = &iter_julia_2;
		view.iter_func[2] = &iter_julia_3;
		view.iter_func[3] = &iter_julia_4;
		view.iter_func[4] = &iter_julia_5;
	}
	else if (ft_strequ(name, "burning_ship"))
	{
		view.iter_func[0] = &iter_burning_ship_1;
		view.iter_func[1] = &iter_burning_ship_2;
		view.iter_func[2] = &iter_burning_ship_3;
		view.iter_func[3] = &iter_burning_ship_4;
		view.iter_func[4] = &iter_burning_ship_5;
	}
	else if (ft_strequ(name, "mandelbar"))
	{
		view.iter_func[0] = &iter_mandelbar_1;
		view.iter_func[1] = &iter_mandelbar_2;
		view.iter_func[2] = &iter_mandelbar_3;
		view.iter_func[3] = &iter_mandelbar_4;
		view.iter_func[4] = &iter_mandelbar_5;
	}
	else if (ft_strequ(name, "new"))
	{
		view.iter_func[0] = &iter_new_1;
		view.iter_func[1] = &iter_new_2;
		view.iter_func[2] = &iter_new_3;
		view.iter_func[3] = &iter_new_4;
		view.iter_func[4] = &iter_new_5;
	}
	else
	{
		usage();
	}
	init_img(&view);
	return (view);
}
