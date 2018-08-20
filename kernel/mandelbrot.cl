/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.cl                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 14:03:36 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/19 14:03:38 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define FRACTAL_JULIA 1
# define FRACTAL_MANDELBROT 2
# define FRACTAL_BURNING_SHIP 3
# define FRACTAL_MANDELBAR 4

# define WIN_HEIGHT 720 // not here    
# define WIN_WIDTH 1280

#define POW2(a) a * a // NOT HERE
#define POW3(a) a * a * a
#define POW4(a) a * a * a * a
#define POW5(a) a * a * a * a * a

int		rgb_to_color(unsigned char r, unsigned char g, unsigned char b)
{
	return (r << 16 | g << 8 | b);
}

int		iterating_rgb(int color, int iter, int depth)
{
	if (color == 0 && iter != depth)
		return (rgb_to_color((double)iter / depth * 200, 0, 0));
	else if (color == 1 && iter % 2 == 1)
		return (rgb_to_color(200, 0, 0));
	else if (color == 2)
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
	else if (color == 3)
		return (rgb_to_color((double)iter / depth * 255,
		(double)iter / depth * 255,
		150 + (double)iter / depth * 155));
	// else if (color == 4)
	// 	return (rgb_to_color(sin(iter / env->depth) * 255,
	// 			cos(iter) * 255,
	// 			100 + (double)iter / env->depth * 155));
	// else if (color == 5)
	// 	return (rgb_to_color(cos((double)iter) * 100,
	// 			sin((double)iter) * 100,
	// 			1 - cos((double)iter)) * 150);
	return (0);
}

void	power1(double *z_re, double *z_im, double c_re, double c_im)
{
	double tmp_re = *z_re;
	double tmp_im = *z_im;
	*z_re = tmp_re + c_re;
	*z_im = tmp_im + c_im;
}

void	power2(double *z_re, double *z_im, double c_re, double c_im)
{
	double tmp_re = POW2(*z_re) - POW2(*z_im);
	double tmp_im = 2 * (*z_re) * (*z_im);
	*z_re = tmp_re + c_re;
	*z_im = tmp_im + c_im;
}

void	power3(double *z_re, double *z_im, double c_re, double c_im)
{
	double tmp_re = POW3(*z_re) - 3 * *z_re * POW2(*z_im);
	double tmp_im = 3 * POW2(*z_re) * *z_im - POW3(*z_im);
	*z_re = tmp_re + c_re;
	*z_im = tmp_im + c_im;
}

void	power4(double *z_re, double *z_im, double c_re, double c_im)
{
	double tmp_re = POW4(*z_re) + POW4(*z_im) - 6 * POW2(*z_re) * POW2(*z_im);
	double tmp_im = 4 * *z_im * POW3(*z_re) - 4 * POW3(*z_im) * *z_re;
	*z_re = tmp_re + c_re;
	*z_im = tmp_im + c_im;
}

void	power5(double *z_re, double *z_im, double c_re, double c_im)
{
	double tmp_re = 5 * POW4(*z_im) * *z_re - 10 * POW2(*z_im) * POW3(*z_re) + POW5(*z_re);
	double tmp_im = POW5(*z_im) - 10 * POW3(*z_im) * POW2(*z_re) + 5 * POW4(*z_re) * *z_im;
	*z_re = tmp_re + c_re;
	*z_im = tmp_im + c_im;
}

__kernel void func(__global int *img, int power, int color, int depth, double re_min, double im_min, double delta_re, double delta_im, int mouse_x, int mouse_y)
{
	int		x = get_global_id(0);
	int		y = get_global_id(1);

	int		iter = -1;
	double	step_re = delta_re / (WIN_WIDTH - 1);
	double	step_im = delta_im / (WIN_HEIGHT - 1);
	double	c_re = re_min + x * step_re;
	double	c_im = im_min - (WIN_HEIGHT - y) * step_im;
	double	z_re = 0;
	double	z_im = 0;
	while (++iter < depth)
	{
		if (POW2(z_re) + POW2(z_im) > 4)
			break ;

		if (power == 1)
			power1(&z_re, &z_im, c_re, c_im);
		else if (power == 2)
			power2(&z_re, &z_im, c_re, c_im);
		else if (power == 3)
			power3(&z_re, &z_im, c_re, c_im);
		else if (power == 4)
			power4(&z_re, &z_im, c_re, c_im);
		else
			power5(&z_re, &z_im, c_re, c_im);
	}

	if (iter == depth)
		img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
	else
		img[WIN_WIDTH * y + x] = 0;
}
