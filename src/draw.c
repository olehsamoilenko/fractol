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

int		iterating_rgb(int iter, int depth)
{
	if (iter == depth)
		return (0);
	else
	{
		// printf("%i\n", iter / depth * 200);
		return (rgb_to_color((float)iter / (float)depth * 200, 0, 0));
	}
}

void	draw_mandelbrot(t_view *view)
{
	int		x;
	int		y;
	t_dot	dot;
	float	tmp_re;
	float	tmp_im;
	int		iter;

	float	step_re;
	float	step_im;


	step_re = view->delta_re / (WIN_WIDTH - 1);
	step_im = view->delta_im / (WIN_HEIGHT - 1);
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		dot.c_im = view->im_min + (WIN_WIDTH - y) * step_im; // +-ok 
		x = -1;
		while (++x < WIN_WIDTH)
		{
			dot.c_re = view->re_min + x * step_re; // ok
			dot.z_im = dot.c_im;
			dot.z_re = dot.c_re;
			iter = -1;
			while (++iter < view->depth)
			{
				if (dot.z_re * dot.z_re + dot.z_im * dot.z_im > 4)
					break ;
				tmp_re = dot.z_re * dot.z_re - dot.z_im * dot.z_im + dot.c_re;
				tmp_im = 2 * dot.z_re * dot.z_im + dot.c_im;
				dot.z_re = tmp_re;
				dot.z_im = tmp_im;
			}
			pixel_put_img(view, x, y, iterating_rgb(iter, view->depth));
		}
	}
	mlx_put_image_to_window(view->mlx_ptr, view->win_ptr,
		view->img.img_ptr, 0, 0);
}

// void	draw_mandelbrot(t_view *view)
// {
// 	int		x;
// 	int		y;
// 	t_dot	dot;
// 	float	tmp_re;
// 	float	tmp_im;
// 	int		iter;

// 	y = -1;
// 	while (++y < WIN_HEIGHT)
// 	{
// 		x = -1;
// 		while (++x < WIN_WIDTH)
// 		{
// 			dot.z_re = 0;
// 			dot.z_im = 0;
// 			dot.c_re = (x - 0.5 * WIN_HEIGHT) / (0.5 * view->zoom * WIN_WIDTH) + view->move_x; //solve
// 			dot.c_im = (y - 0.5 * WIN_WIDTH) / (0.5 * view->zoom * WIN_HEIGHT) + view->move_y; //solve
// 			iter = -1;
// 			while (++iter < view->depth)
// 			{
// 				if (dot.z_re * dot.z_re + dot.z_im * dot.z_im > 4)
// 					break ;
// 				tmp_re = dot.z_re * dot.z_re - dot.z_im * dot.z_im + dot.c_re;
// 				tmp_im = 2 * dot.z_re * dot.z_im + dot.c_im;
// 				dot.z_re = tmp_re;
// 				dot.z_im = tmp_im;
// 			}
// 			pixel_put_img(view, x, y, iterating_rgb(iter, view->depth));
// 		}
// 	}
// 	mlx_put_image_to_window(view->mlx_ptr, view->win_ptr,
// 		view->img.img_ptr, 0, 0);
// }
