/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.cl                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 14:03:36 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/19 14:03:38 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define WIN_HEIGHT 1080
# define WIN_WIDTH 1920
# define POW2(a) ((a) * (a))
# define POW3(a) ((a) * (a) * (a))
# define POW4(a) ((a) * (a) * (a) * (a))
# define POW5(a) ((a) * (a) * (a) * (a) * (a))

int		rgb_to_color(unsigned char r, unsigned char g, unsigned char b)
{
	return (r << 16 | g << 8 | b);
}

int		iterating_rgb(int color, int iter, int depth)
{
	double k = (double)iter / depth;

	if (color == 0)
	{
		return (rgb_to_color(9 * (1-k) * POW3(k) * 255,
			15 * POW2(1-k) * POW2(k) * 255,
			8.5 * POW3(1-k) * k * 255));
	}
	else if (color == 1 && iter != depth)
		return (rgb_to_color(k * 200, 0, 0));
	else if (color == 2)
	{
		if (iter == depth)
			iter = 1;
		return (rgb_to_color(127.5 * (cos((double)iter) + 1),
			127.5 * (sin((double)iter) + 1),
			127.5 * (1 - cos((double)iter))));
	}
	else if (color == 3)
	{
		if (iter == depth)
			iter = 50;
		return (rgb_to_color(abs(255 - 5 * iter),
			abs(255 - 10 * iter),
			abs(255 - 2 * iter)));
	}
	else if (color == 4)
	{
		if (iter % 4 == 0)
			return (rgb_to_color(250, 0, 0));
		else if (iter % 4 == 1)
			return (rgb_to_color(0, 250, 0));
		else if (iter % 4 == 2)
			return (rgb_to_color(0, 0, 250));
		else if (iter % 4 == 3)
			return (rgb_to_color(255, 255, 0));
	}
	else if (color == 5)
		return (rgb_to_color(k * 255, k * 255, 150 + k * 155));
	else if (color == 6 && iter % 2 == 1 && iter != depth)
		return (rgb_to_color(200, 0, 0));
	return (0);
}

__kernel void mandelbrot1(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = re_min + x * step_re;
	double	c_im = im_min - (WIN_HEIGHT - y) * step_im;
	double	z_re = 0;
	double	z_im = 0;

	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		tmp_re = z_re;
		tmp_im = z_im;
		z_re = tmp_re + c_re;
		z_im = tmp_im + c_im;
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}

__kernel void mandelbrot2(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = re_min + x * step_re;
	double	c_im = im_min - (WIN_HEIGHT - y) * step_im;
	double	z_re = 0;
	double	z_im = 0;
	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		tmp_re = POW2(z_re) - POW2(z_im);
		tmp_im = 2 * (z_re) * (z_im);
		z_re = tmp_re + c_re;
		z_im = tmp_im + c_im;
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}

__kernel void mandelbrot3(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = re_min + x * step_re;
	double	c_im = im_min - (WIN_HEIGHT - y) * step_im;
	double	z_re = 0;
	double	z_im = 0;

	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		tmp_re = POW3(z_re) - 3 * z_re * POW2(z_im);
		tmp_im = 3 * POW2(z_re) * z_im - POW3(z_im);
		z_re = tmp_re + c_re;
		z_im = tmp_im + c_im;
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}

__kernel void mandelbrot4(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = re_min + x * step_re;
	double	c_im = im_min - (WIN_HEIGHT - y) * step_im;
	double	z_re = 0;
	double	z_im = 0;

	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		tmp_re = POW4(z_re) + POW4(z_im) - 6 * POW2(z_re) * POW2(z_im);
		tmp_im = 4 * z_im * POW3(z_re) - 4 * POW3(z_im) * z_re;
		z_re = tmp_re + c_re;
		z_im = tmp_im + c_im;
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}

__kernel void mandelbrot5(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = re_min + x * step_re;
	double	c_im = im_min - (WIN_HEIGHT - y) * step_im;
	double	z_re = 0;
	double	z_im = 0;

	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		tmp_re = 5 * POW4(z_im) * z_re - 10 * POW2(z_im) * POW3(z_re) + POW5(z_re);
		tmp_im = POW5(z_im) - 10 * POW3(z_im) * POW2(z_re) + 5 * POW4(z_re) * z_im;
		z_re = tmp_re + c_re;
		z_im = tmp_im + c_im;
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}

__kernel void julia1(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = im_min - (WIN_HEIGHT - y) * step_im;
	double	c_im = re_min + x * step_re;
	double	z_re = c_re;
	double	z_im = c_im;

	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		tmp_re = z_re;
		tmp_im = z_im;
		z_re = tmp_re + (double)mouse_y / WIN_HEIGHT;
		z_im = tmp_im + (double)mouse_x / WIN_WIDTH;
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}

__kernel void julia2(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = im_min - (WIN_HEIGHT - y) * step_im;
	double	c_im = re_min + x * step_re;
	double	z_re = c_re;
	double	z_im = c_im;

	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		tmp_re = POW2(z_re) - POW2(z_im);
		tmp_im = 2 * (z_re) * (z_im);
		z_re = tmp_re + (double)mouse_y / WIN_HEIGHT;
		z_im = tmp_im + (double)mouse_x / WIN_WIDTH;
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}

__kernel void julia3(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = im_min - (WIN_HEIGHT - y) * step_im;
	double	c_im = re_min + x * step_re;
	double	z_re = c_re;
	double	z_im = c_im;

	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		tmp_re = POW3(z_re) - 3 * z_re * POW2(z_im);
		tmp_im = 3 * POW2(z_re) * z_im - POW3(z_im);
		z_re = tmp_re + (double)mouse_y / WIN_HEIGHT;
		z_im = tmp_im + (double)mouse_x / WIN_WIDTH;
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}

__kernel void julia4(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = im_min - (WIN_HEIGHT - y) * step_im;
	double	c_im = re_min + x * step_re;
	double	z_re = c_re;
	double	z_im = c_im;

	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		tmp_re = POW4(z_re) + POW4(z_im) - 6 * POW2(z_re) * POW2(z_im);
		tmp_im = 4 * z_im * POW3(z_re) - 4 * POW3(z_im) * z_re;
		z_re = tmp_re + (double)mouse_y / WIN_HEIGHT;
		z_im = tmp_im + (double)mouse_x / WIN_WIDTH;
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}

__kernel void julia5(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = im_min - (WIN_HEIGHT - y) * step_im;
	double	c_im = re_min + x * step_re;
	double	z_re = c_re;
	double	z_im = c_im;

	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		tmp_re = 5 * POW4(z_im) * z_re - 10 * POW2(z_im) * POW3(z_re) + POW5(z_re);
		tmp_im = POW5(z_im) - 10 * POW3(z_im) * POW2(z_re) + 5 * POW4(z_re) * z_im;
		z_re = tmp_re + (double)mouse_y / WIN_HEIGHT;
		z_im = tmp_im + (double)mouse_x / WIN_WIDTH;
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}

__kernel void mandelbar1(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = re_min + x * step_re;
	double	c_im = im_min - (WIN_HEIGHT - y) * step_im;
	double	z_re = 0;
	double	z_im = 0;

	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		tmp_re = z_re;
		tmp_im = z_im;
		z_re = -tmp_re + c_re;
		z_im = tmp_im + c_im;
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}

__kernel void mandelbar2(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = re_min + x * step_re;
	double	c_im = im_min - (WIN_HEIGHT - y) * step_im;
	double	z_re = 0;
	double	z_im = 0;

	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		tmp_re = POW2(z_re) - POW2(z_im);
		tmp_im = 2 * (z_re) * (z_im);
		z_re = -tmp_re + c_re;
		z_im = tmp_im + c_im;
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}

__kernel void mandelbar3(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = re_min + x * step_re;
	double	c_im = im_min - (WIN_HEIGHT - y) * step_im;
	double	z_re = 0;
	double	z_im = 0;

	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		tmp_re = POW3(z_re) - 3 * z_re * POW2(z_im);
		tmp_im = 3 * POW2(z_re) * z_im - POW3(z_im);
		z_re = -tmp_re + c_re;
		z_im = tmp_im + c_im;
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}

__kernel void mandelbar4(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = re_min + x * step_re;
	double	c_im = im_min - (WIN_HEIGHT - y) * step_im;
	double	z_re = 0;
	double	z_im = 0;

	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		tmp_re = POW4(z_re) + POW4(z_im) - 6 * POW2(z_re) * POW2(z_im);
		tmp_im = 4 * z_im * POW3(z_re) - 4 * POW3(z_im) * z_re;
		z_re = -tmp_re + c_re;
		z_im = tmp_im + c_im;
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}

__kernel void mandelbar5(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = re_min + x * step_re;
	double	c_im = im_min - (WIN_HEIGHT - y) * step_im;
	double	z_re = 0;
	double	z_im = 0;

	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		tmp_re = 5 * POW4(z_im) * z_re - 10 * POW2(z_im) * POW3(z_re) + POW5(z_re);
		tmp_im = POW5(z_im) - 10 * POW3(z_im) * POW2(z_re) + 5 * POW4(z_re) * z_im;
		z_re = -tmp_re + c_re;
		z_im = tmp_im + c_im;
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}
__kernel void burning_ship1(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = re_min + x * step_re;
	double	c_im = im_min - (WIN_HEIGHT - y) * step_im;
	double	z_re = 0;
	double	z_im = 0;

	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		z_re = fabs(z_re);
		z_im = fabs(z_im);
		tmp_re = z_re;
		tmp_im = z_im;
		z_re = tmp_re + c_re;
		z_im = tmp_im + c_im;
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}

__kernel void burning_ship2(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = re_min + x * step_re;
	double	c_im = im_min - (WIN_HEIGHT - y) * step_im;
	double	z_re = 0;
	double	z_im = 0;

	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		z_re = fabs(z_re);
		z_im = fabs(z_im);
		tmp_re = POW2(z_re) - POW2(z_im);
		tmp_im = 2 * (z_re) * (z_im);
		z_re = tmp_re + c_re;
		z_im = tmp_im + c_im;
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}

__kernel void burning_ship3(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = re_min + x * step_re;
	double	c_im = im_min - (WIN_HEIGHT - y) * step_im;
	double	z_re = 0;
	double	z_im = 0;

	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		z_re = fabs(z_re);
		z_im = fabs(z_im);
		tmp_re = POW3(z_re) - 3 * z_re * POW2(z_im);
		tmp_im = 3 * POW2(z_re) * z_im - POW3(z_im);
		z_re = tmp_re + c_re;
		z_im = tmp_im + c_im;
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}

__kernel void burning_ship4(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = re_min + x * step_re;
	double	c_im = im_min - (WIN_HEIGHT - y) * step_im;
	double	z_re = 0;
	double	z_im = 0;

	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		z_re = fabs(z_re);
		z_im = fabs(z_im);
		tmp_re = POW4(z_re) + POW4(z_im) - 6 * POW2(z_re) * POW2(z_im);
		tmp_im = 4 * z_im * POW3(z_re) - 4 * POW3(z_im) * z_re;
		z_re = tmp_re + c_re;
		z_im = tmp_im + c_im;
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}

__kernel void burning_ship5(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = re_min + x * step_re;
	double	c_im = im_min - (WIN_HEIGHT - y) * step_im;
	double	z_re = 0;
	double	z_im = 0;

	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		z_re = fabs(z_re);
		z_im = fabs(z_im);
		tmp_re = 5 * POW4(z_im) * z_re - 10 * POW2(z_im) * POW3(z_re) + POW5(z_re);
		tmp_im = POW5(z_im) - 10 * POW3(z_im) * POW2(z_re) + 5 * POW4(z_re) * z_im;
		z_re = tmp_re + c_re;
		z_im = tmp_im + c_im;
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}

__kernel void brain1(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = im_min - (WIN_HEIGHT - y) * step_im;
	double	c_im = re_min + x * step_re;
	double	z_re = c_re;
	double	z_im = c_im;

	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		tmp_re = z_re;
		tmp_im = z_im;
		z_re = tmp_re + (double)mouse_x / WIN_WIDTH;
		z_im = tmp_im + (double)mouse_y / WIN_HEIGHT * tmp_im;
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}

__kernel void brain2(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = im_min - (WIN_HEIGHT - y) * step_im;
	double	c_im = re_min + x * step_re;
	double	z_re = c_re;
	double	z_im = c_im;
	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		tmp_re = POW2(z_re) - POW2(z_im);
		tmp_im = 2 * (z_re) * (z_im);
		z_re = tmp_re + (double)mouse_x / WIN_WIDTH;
		z_im = tmp_im + (double)mouse_y / WIN_HEIGHT * tmp_im;
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}

__kernel void brain3(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = im_min - (WIN_HEIGHT - y) * step_im;
	double	c_im = re_min + x * step_re;
	double	z_re = c_re;
	double	z_im = c_im;

	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		tmp_re = POW3(z_re) - 3 * z_re * POW2(z_im);
		tmp_im = 3 * POW2(z_re) * z_im - POW3(z_im);
		z_re = tmp_re + (double)mouse_x / WIN_WIDTH;
		z_im = tmp_im + (double)mouse_y / WIN_HEIGHT * tmp_im;
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}

__kernel void brain4(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = im_min - (WIN_HEIGHT - y) * step_im;
	double	c_im = re_min + x * step_re;
	double	z_re = c_re;
	double	z_im = c_im;

	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		tmp_re = POW4(z_re) + POW4(z_im) - 6 * POW2(z_re) * POW2(z_im);
		tmp_im = 4 * z_im * POW3(z_re) - 4 * POW3(z_im) * z_re;
		z_re = tmp_re + (double)mouse_x / WIN_WIDTH;
		z_im = tmp_im + (double)mouse_y / WIN_HEIGHT * tmp_im;
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}

__kernel void brain5(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = im_min - (WIN_HEIGHT - y) * step_im;
	double	c_im = re_min + x * step_re;
	double	z_re = c_re;
	double	z_im = c_im;

	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		tmp_re = 5 * POW4(z_im) * z_re - 10 * POW2(z_im) * POW3(z_re) + POW5(z_re);
		tmp_im = POW5(z_im) - 10 * POW3(z_im) * POW2(z_re) + 5 * POW4(z_re) * z_im;
		z_re = tmp_re + (double)mouse_x / WIN_WIDTH;
		z_im = tmp_im + (double)mouse_y / WIN_HEIGHT * tmp_im;
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}

__kernel void feigenbaum1(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = re_min + x * step_re;
	double	c_im = im_min - (WIN_HEIGHT - y) * step_im;
	double	z_re = 0;
	double	z_im = 0;

	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		tmp_re = z_re;
		tmp_im = z_im;
		z_re = tmp_re + POW3(c_re) - 3 * c_re * POW2(c_im) + (double)mouse_y / WIN_HEIGHT;
		z_im = tmp_im + 3 * POW2(c_re) * c_im - POW3(c_im) + (double)mouse_x / WIN_WIDTH;
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}

__kernel void feigenbaum2(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = re_min + x * step_re;
	double	c_im = im_min - (WIN_HEIGHT - y) * step_im;
	double	z_re = 0;
	double	z_im = 0;
	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		tmp_re = POW2(z_re) - POW2(z_im);
		tmp_im = 2 * (z_re) * (z_im);
		z_re = tmp_re + POW3(c_re) - 3 * c_re * POW2(c_im) + (double)mouse_y / WIN_HEIGHT;
		z_im = tmp_im + 3 * POW2(c_re) * c_im - POW3(c_im) + (double)mouse_x / WIN_WIDTH;
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}

__kernel void feigenbaum3(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = re_min + x * step_re;
	double	c_im = im_min - (WIN_HEIGHT - y) * step_im;
	double	z_re = 0;
	double	z_im = 0;

	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		tmp_re = POW3(z_re) - 3 * z_re * POW2(z_im);
		tmp_im = 3 * POW2(z_re) * z_im - POW3(z_im);
		z_re = tmp_re + POW3(c_re) - 3 * c_re * POW2(c_im)  + (double)mouse_y / WIN_HEIGHT;
		z_im = tmp_im + 3 * POW2(c_re) * c_im - POW3(c_im)  + (double)mouse_x / WIN_WIDTH;
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}

__kernel void feigenbaum4(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = re_min + x * step_re;
	double	c_im = im_min - (WIN_HEIGHT - y) * step_im;
	double	z_re = 0;
	double	z_im = 0;

	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		tmp_re = POW4(z_re) + POW4(z_im) - 6 * POW2(z_re) * POW2(z_im);
		tmp_im = 4 * z_im * POW3(z_re) - 4 * POW3(z_im) * z_re;
		z_re = tmp_re + POW3(c_re) - 3 * c_re * POW2(c_im)  + (double)mouse_y / WIN_HEIGHT;
		z_im = tmp_im + 3 * POW2(c_re) * c_im - POW3(c_im)  + (double)mouse_x / WIN_WIDTH;
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}

__kernel void feigenbaum5(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = re_min + x * step_re;
	double	c_im = im_min - (WIN_HEIGHT - y) * step_im;
	double	z_re = 0;
	double	z_im = 0;

	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		tmp_re = 5 * POW4(z_im) * z_re - 10 * POW2(z_im) * POW3(z_re) + POW5(z_re);
		tmp_im = POW5(z_im) - 10 * POW3(z_im) * POW2(z_re) + 5 * POW4(z_re) * z_im;
		z_re = tmp_re + POW3(c_re) - 3 * c_re * POW2(c_im)  + (double)mouse_y / WIN_HEIGHT;
		z_im = tmp_im + 3 * POW2(c_re) * c_im - POW3(c_im)  + (double)mouse_x / WIN_WIDTH;
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}

__kernel void leaf1(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = re_min + x * step_re;
	double	c_im = im_min - (WIN_HEIGHT - y) * step_im;
	double	z_re = 0;
	double	z_im = 0;

	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		tmp_re = z_re;
		tmp_im = z_im;
		z_re = tmp_re + c_re / (POW2(c_re) + POW2(c_im));
		z_im = tmp_im - c_im / (POW2(c_re) + POW2(c_im));
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}

__kernel void leaf2(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = re_min + x * step_re;
	double	c_im = im_min - (WIN_HEIGHT - y) * step_im;
	double	z_re = 0;
	double	z_im = 0;
	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		tmp_re = POW2(z_re) - POW2(z_im);
		tmp_im = 2 * (z_re) * (z_im);
		z_re = tmp_re + c_re / (POW2(c_re) + POW2(c_im));
		z_im = tmp_im - c_im / (POW2(c_re) + POW2(c_im));
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}

__kernel void leaf3(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = re_min + x * step_re;
	double	c_im = im_min - (WIN_HEIGHT - y) * step_im;
	double	z_re = 0;
	double	z_im = 0;

	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		tmp_re = POW3(z_re) - 3 * z_re * POW2(z_im);
		tmp_im = 3 * POW2(z_re) * z_im - POW3(z_im);
		z_re = tmp_re + c_re / (POW2(c_re) + POW2(c_im));
		z_im = tmp_im - c_im / (POW2(c_re) + POW2(c_im));
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}

__kernel void leaf4(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = re_min + x * step_re;
	double	c_im = im_min - (WIN_HEIGHT - y) * step_im;
	double	z_re = 0;
	double	z_im = 0;

	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		tmp_re = POW4(z_re) + POW4(z_im) - 6 * POW2(z_re) * POW2(z_im);
		tmp_im = 4 * z_im * POW3(z_re) - 4 * POW3(z_im) * z_re;
		z_re = tmp_re + c_re / (POW2(c_re) + POW2(c_im));
		z_im = tmp_im - c_im / (POW2(c_re) + POW2(c_im));
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}

__kernel void leaf5(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = re_min + x * step_re;
	double	c_im = im_min - (WIN_HEIGHT - y) * step_im;
	double	z_re = 0;
	double	z_im = 0;

	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		tmp_re = 5 * POW4(z_im) * z_re - 10 * POW2(z_im) * POW3(z_re) + POW5(z_re);
		tmp_im = POW5(z_im) - 10 * POW3(z_im) * POW2(z_re) + 5 * POW4(z_re) * z_im;
		z_re = tmp_re + c_re / (POW2(c_re) + POW2(c_im));
		z_im = tmp_im - c_im / (POW2(c_re) + POW2(c_im));
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}

__kernel void hyper1(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = re_min + x * step_re;
	double	c_im = im_min - (WIN_HEIGHT - y) * step_im;
	double	z_re = 0;
	double	z_im = 0;

	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		tmp_re = z_re;
		tmp_im = z_im;
		z_re = tmp_re + cos(c_re) * cosh(c_im);
		z_im = tmp_im + sin(c_re) * sinh(c_im);
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}

__kernel void hyper2(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = re_min + x * step_re;
	double	c_im = im_min - (WIN_HEIGHT - y) * step_im;
	double	z_re = 0;
	double	z_im = 0;
	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		tmp_re = POW2(z_re) - POW2(z_im);
		tmp_im = 2 * (z_re) * (z_im);
		z_re = tmp_re + cos(c_re) * cosh(c_im);
		z_im = tmp_im + sin(c_re) * sinh(c_im);
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}

__kernel void hyper3(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = re_min + x * step_re;
	double	c_im = im_min - (WIN_HEIGHT - y) * step_im;
	double	z_re = 0;
	double	z_im = 0;

	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		tmp_re = POW3(z_re) - 3 * z_re * POW2(z_im);
		tmp_im = 3 * POW2(z_re) * z_im - POW3(z_im);
		z_re = tmp_re + cos(c_re) * cosh(c_im);
		z_im = tmp_im + sin(c_re) * sinh(c_im);
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}

__kernel void hyper4(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = re_min + x * step_re;
	double	c_im = im_min - (WIN_HEIGHT - y) * step_im;
	double	z_re = 0;
	double	z_im = 0;

	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		tmp_re = POW4(z_re) + POW4(z_im) - 6 * POW2(z_re) * POW2(z_im);
		tmp_im = 4 * z_im * POW3(z_re) - 4 * POW3(z_im) * z_re;
		z_re = tmp_re + cos(c_re) * cosh(c_im);
		z_im = tmp_im + sin(c_re) * sinh(c_im);
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}

__kernel void hyper5(__global int *img, int color, int depth, double re_min, double im_min, double step_re, double step_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		iter = -1;
	double	tmp_re;
	double	tmp_im;
	double	c_re = re_min + x * step_re;
	double	c_im = im_min - (WIN_HEIGHT - y) * step_im;
	double	z_re = 0;
	double	z_im = 0;

	while (++iter < depth && POW2(z_re) + POW2(z_im) < 4)
	{
		tmp_re = 5 * POW4(z_im) * z_re - 10 * POW2(z_im) * POW3(z_re) + POW5(z_re);
		tmp_im = POW5(z_im) - 10 * POW3(z_im) * POW2(z_re) + 5 * POW4(z_re) * z_im;
		z_re = tmp_re + cos(c_re) * cosh(c_im);
		z_im = tmp_im + sin(c_re) * sinh(c_im);
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}