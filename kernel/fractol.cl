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


// # define FRACTAL_JULIA 1
// # define FRACTAL_MANDELBROT 2
// # define FRACTAL_BURNING_SHIP 3
// # define FRACTAL_MANDELBAR 4

# define WIN_HEIGHT 720
# define WIN_WIDTH 1280

#define POW2(a) a * a
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
		z_re = fabs(tmp_re + c_re);
		z_im = tmp_im + c_im;
	}
	img[WIN_WIDTH * y + x] = iterating_rgb(color, iter, depth);
}












// int	iter_mandelbrot_1(t_dot dot, t_env *env)
// {
// 	int		iter;
// 	double	tmp_re;
// 	double	tmp_im;

// 	dot.z_im = 0;
// 	dot.z_re = 0;
// 	iter = -1;
// 	while (++iter < env->depth)
// 	{
// 		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
// 			break ;
// 		tmp_re = dot.z_re;
// 		tmp_im = dot.z_im;
// 		dot.z_re = tmp_re + dot.c_re;
// 		dot.z_im = tmp_im + dot.c_im;
// 	}
// 	return (iter);
// }

// int	iter_mandelbrot_2(t_dot dot, t_env *env)
// {
// 	int		iter;
// 	double	tmp_re;
// 	double	tmp_im;

// 	dot.z_im = 0;
// 	dot.z_re = 0;
// 	iter = -1;
// 	while (++iter < env->depth)
// 	{
// 		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
// 			break ;
// 		tmp_re = POW2(dot.z_re) - POW2(dot.z_im);
// 		tmp_im = 2 * dot.z_re * dot.z_im;
// 		dot.z_re = tmp_re + dot.c_re;
// 		dot.z_im = tmp_im + dot.c_im;
// 	}
// 	return (iter);
// }

// int	iter_mandelbrot_3(t_dot dot, t_env *env)
// {
// 	int		iter;
// 	double	tmp_re;
// 	double	tmp_im;

// 	dot.z_im = 0;
// 	dot.z_re = 0;
// 	iter = -1;
// 	while (++iter < env->depth)
// 	{
// 		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
// 			break ;
// 		tmp_re = POW3(dot.z_re) - 3 * dot.z_re * POW2(dot.z_im);
// 		tmp_im = 3 * POW2(dot.z_re) * dot.z_im - POW3(dot.z_im);
// 		dot.z_re = tmp_re + dot.c_re;
// 		dot.z_im = tmp_im + dot.c_im;
// 	}
// 	return (iter);
// }

// int	iter_mandelbrot_4(t_dot dot, t_env *env)
// {
// 	int		iter;
// 	double	tmp_re;
// 	double	tmp_im;

// 	dot.z_im = 0;
// 	dot.z_re = 0;
// 	iter = -1;
// 	while (++iter < env->depth)
// 	{
// 		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
// 			break ;
// 		tmp_re = POW4(dot.z_re)
// 		+ POW4(dot.z_im) - 6 * POW2(dot.z_re) * POW2(dot.z_im);
// 		tmp_im = 4 * dot.z_im * POW3(dot.z_re) - 4 * POW3(dot.z_im) * dot.z_re;
// 		dot.z_re = tmp_re + dot.c_re;
// 		dot.z_im = tmp_im + dot.c_im;
// 	}
// 	return (iter);
// }


// int	iter_mandelbrot_5(t_dot dot, t_env *env)
// {
// 	int		iter;
// 	double	tmp_re;
// 	double	tmp_im;

// 	dot.z_im = 0;
// 	dot.z_re = 0;
// 	iter = -1;
// 	while (++iter < env->depth)
// 	{
// 		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
// 			break ;
// 		tmp_re = 5 * POW4(dot.z_im) * dot.z_re - 10 * POW2(dot.z_im) * POW3(dot.z_re) + POW5(dot.z_re);
// 		tmp_im = POW5(dot.z_im) - 10 * POW3(dot.z_im) * POW2(dot.z_re) + 5 * POW4(dot.z_re) * dot.z_im;
// 		dot.z_re = tmp_re + dot.c_re;
// 		dot.z_im = tmp_im + dot.c_im;
// 	}
// 	return (iter);
// }



// int	iter_new_1(t_dot dot, t_env *env)
// {
// 	int		iter;
// 	double	tmp_re;
// 	double	tmp_im;

// 	dot.z_im = 0;
// 	dot.z_re = 0;
// 	iter = -1;
// 	while (++iter < env->depth)
// 	{
// 		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
// 			break ;
// 		tmp_re = dot.z_re;
// 		tmp_im = dot.z_im;
// 		dot.z_re = fabs(tmp_re + dot.c_re);
// 		dot.z_im = tmp_im + dot.c_im;
// 	}
// 	return (iter);
// }

// int	iter_new_2(t_dot dot, t_env *env)
// {
// 	int		iter;
// 	double	tmp_re;
// 	double	tmp_im;

// 	dot.z_im = 0;
// 	dot.z_re = 0;
// 	iter = -1;
// 	while (++iter < env->depth)
// 	{
// 		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
// 			break ;
// 		tmp_re = POW2(dot.z_re) - POW2(dot.z_im);
// 		tmp_im = 2 * dot.z_re * dot.z_im;
// 		dot.z_re = fabs(tmp_re + dot.c_re);
// 		dot.z_im = tmp_im + dot.c_im;
// 	}
// 	return (iter);
// }

// int	iter_new_3(t_dot dot, t_env *env)
// {
// 	int		iter;
// 	double	tmp_re;
// 	double	tmp_im;

// 	dot.z_im = 0;
// 	dot.z_re = 0;
// 	iter = -1;
// 	while (++iter < env->depth)
// 	{
// 		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
// 			break ;
// 		tmp_re = POW3(dot.z_re) - 3 * dot.z_re * POW2(dot.z_im);
// 		tmp_im = 3 * POW2(dot.z_re) * dot.z_im - POW3(dot.z_im);
// 		dot.z_re = fabs(tmp_re + dot.c_re);
// 		dot.z_im = tmp_im + dot.c_im;
// 	}
// 	return (iter);
// }

// int	iter_new_4(t_dot dot, t_env *env)
// {
// 	int		iter;
// 	double	tmp_re;
// 	double	tmp_im;

// 	dot.z_im = 0;
// 	dot.z_re = 0;
// 	iter = -1;
// 	while (++iter < env->depth)
// 	{
// 		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
// 			break ;
// 		tmp_re = POW4(dot.z_re)
// 		+ POW4(dot.z_im) - 6 * POW2(dot.z_re) * POW2(dot.z_im);
// 		tmp_im = 4 * dot.z_im * POW3(dot.z_re) - 4 * POW3(dot.z_im) * dot.z_re;
// 		dot.z_re = fabs(tmp_re + dot.c_re);
// 		dot.z_im = tmp_im + dot.c_im;
// 	}
// 	return (iter);
// }

// int	iter_new_5(t_dot dot, t_env *env)
// {
// 	int		iter;
// 	double	tmp_re;
// 	double	tmp_im;

// 	dot.z_im = 0;
// 	dot.z_re = 0;
// 	iter = -1;
// 	while (++iter < env->depth)
// 	{
// 		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
// 			break ;
// 		tmp_re = 5 * POW4(dot.z_im) * dot.z_re - 10 * POW2(dot.z_im) * POW3(dot.z_re) + POW5(dot.z_re);
// 		tmp_im = POW5(dot.z_im) - 10 * POW3(dot.z_im) * POW2(dot.z_re) + 5 * POW4(dot.z_re) * dot.z_im;
// 		dot.z_re = fabs(tmp_re + dot.c_re);
// 		dot.z_im = tmp_im + dot.c_im;
// 	}
// 	return (iter);
// }

// int	iter_mandelbar_1(t_dot dot, t_env *env)
// {
// 	int		iter;
// 	double	tmp_re;
// 	double	tmp_im;

// 	dot.z_im = 0;
// 	dot.z_re = 0;
// 	iter = -1;
// 	while (++iter < env->depth)
// 	{
// 		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
// 			break ;
// 		tmp_re = dot.z_re;
// 		tmp_im = dot.z_im;
// 		dot.z_re = -tmp_re + dot.c_re;
// 		dot.z_im = tmp_im + dot.c_im;
// 	}
// 	return (iter);
// }

// int	iter_mandelbar_2(t_dot dot, t_env *env)
// {
// 	int		iter;
// 	double	tmp_re;
// 	double	tmp_im;

// 	dot.z_im = 0;
// 	dot.z_re = 0;
// 	iter = -1;
// 	while (++iter < env->depth)
// 	{
// 		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
// 			break ;
// 		tmp_re = POW2(dot.z_re) - POW2(dot.z_im);
// 		tmp_im = 2 * dot.z_re * dot.z_im;
// 		dot.z_re = -tmp_re + dot.c_re;
// 		dot.z_im = tmp_im + dot.c_im;
// 	}
// 	return (iter);
// }

// int	iter_mandelbar_3(t_dot dot, t_env *env)
// {
// 	int		iter;
// 	double	tmp_re;
// 	double	tmp_im;

// 	dot.z_im = 0;
// 	dot.z_re = 0;
// 	iter = -1;
// 	while (++iter < env->depth)
// 	{
// 		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
// 			break ;
// 		tmp_re = POW3(dot.z_re) - 3 * dot.z_re * POW2(dot.z_im);
// 		tmp_im = 3 * POW2(dot.z_re) * dot.z_im - POW3(dot.z_im);
// 		dot.z_re = -tmp_re + dot.c_re;
// 		dot.z_im = tmp_im + dot.c_im;
// 	}
// 	return (iter);
// }

// int	iter_mandelbar_4(t_dot dot, t_env *env)
// {
// 	int		iter;
// 	double	tmp_re;
// 	double	tmp_im;

// 	dot.z_im = 0;
// 	dot.z_re = 0;
// 	iter = -1;
// 	while (++iter < env->depth)
// 	{
// 		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
// 			break ;
// 		tmp_re = POW4(dot.z_re)
// 		+ POW4(dot.z_im) - 6 * POW2(dot.z_re) * POW2(dot.z_im);
// 		tmp_im = 4 * dot.z_im * POW3(dot.z_re) - 4 * POW3(dot.z_im) * dot.z_re;
// 		dot.z_re = -tmp_re + dot.c_re;
// 		dot.z_im = tmp_im + dot.c_im;
// 	}
// 	return (iter);
// }

// int	iter_mandelbar_5(t_dot dot, t_env *env)
// {
// 	int		iter;
// 	double	tmp_re;
// 	double	tmp_im;

// 	dot.z_im = 0;
// 	dot.z_re = 0;
// 	iter = -1;
// 	while (++iter < env->depth)
// 	{
// 		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
// 			break ;
// 		tmp_re = 5 * POW4(dot.z_im) * dot.z_re - 10 * POW2(dot.z_im) * POW3(dot.z_re) + POW5(dot.z_re);
// 		tmp_im = POW5(dot.z_im) - 10 * POW3(dot.z_im) * POW2(dot.z_re) + 5 * POW4(dot.z_re) * dot.z_im;
// 		dot.z_re = -tmp_re + dot.c_re;
// 		dot.z_im = tmp_im + dot.c_im;
// 	}
// 	return (iter);
// }


// int	iter_julia_1(t_dot dot, t_env *env)
// {
// 	int		iter;
// 	double	tmp_re;
// 	double	tmp_im;

// 	dot.z_im = dot.c_im;
// 	dot.z_re = dot.c_re;
// 	iter = -1;
// 	while (++iter < env->depth)
// 	{
// 		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
// 			break ;
// 		tmp_re = dot.z_re;
// 		tmp_im = dot.z_im;
// 		dot.z_re = tmp_re + ((double)env->mouse_x) / WIN_WIDTH;
// 		dot.z_im = tmp_im + ((double)env->mouse_y) / WIN_HEIGHT;
// 	}
// 	return (iter);
// }

// int	iter_julia_2(t_dot dot, t_env *env)
// {
// 	int		iter;
// 	double	tmp_re;
// 	double	tmp_im;

// 	dot.z_im = dot.c_im;
// 	dot.z_re = dot.c_re;
// 	iter = -1;
// 	while (++iter < env->depth)
// 	{
// 		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
// 			break ;
// 		tmp_re = POW2(dot.z_re) - POW2(dot.z_im);
// 		tmp_im = 2 * dot.z_re * dot.z_im;
// 		dot.z_re = tmp_re + ((double)env->mouse_x) / WIN_WIDTH;
// 		dot.z_im = tmp_im + ((double)env->mouse_y) / WIN_HEIGHT;
// 	}
// 	return (iter);
// }

// int	iter_julia_3(t_dot dot, t_env *env)
// {
// 	int		iter;
// 	double	tmp_re;
// 	double	tmp_im;

// 	dot.z_im = dot.c_im;
// 	dot.z_re = dot.c_re;
// 	iter = -1;
// 	while (++iter < env->depth)
// 	{
// 		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
// 			break ;
// 		tmp_re = POW3(dot.z_re) - 3 * dot.z_re * POW2(dot.z_im);
// 		tmp_im = 3 * POW2(dot.z_re) * dot.z_im - POW3(dot.z_im);
// 		dot.z_re = tmp_re + ((double)env->mouse_x) / WIN_WIDTH;
// 		dot.z_im = tmp_im + ((double)env->mouse_y) / WIN_HEIGHT;
// 	}
// 	return (iter);
// }

// int	iter_julia_4(t_dot dot, t_env *env)
// {
// 	int		iter;
// 	double	tmp_re;
// 	double	tmp_im;

// 	dot.z_im = dot.c_im;
// 	dot.z_re = dot.c_re;
// 	iter = -1;
// 	while (++iter < env->depth)
// 	{
// 		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
// 			break ;
// 		tmp_re = POW4(dot.z_re)
// 		+ POW4(dot.z_im) - 6 * POW2(dot.z_re) * POW2(dot.z_im);
// 		tmp_im = 4 * dot.z_im * POW3(dot.z_re) - 4 * POW3(dot.z_im) * dot.z_re;
// 		dot.z_re = tmp_re + ((double)env->mouse_x) / WIN_WIDTH;
// 		dot.z_im = tmp_im + ((double)env->mouse_y) / WIN_HEIGHT;
// 	}
// 	return (iter);
// }

// int	iter_julia_5(t_dot dot, t_env *env)
// {
// 	int		iter;
// 	double	tmp_re;
// 	double	tmp_im;

// 	dot.z_im = dot.c_im;
// 	dot.z_re = dot.c_re;
// 	iter = -1;
// 	while (++iter < env->depth)
// 	{
// 		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
// 			break ;
// 		tmp_re = 5 * POW4(dot.z_im) * dot.z_re - 10 * POW2(dot.z_im) * POW3(dot.z_re) + POW5(dot.z_re);
// 		tmp_im = POW5(dot.z_im) - 10 * POW3(dot.z_im) * POW2(dot.z_re) + 5 * POW4(dot.z_re) * dot.z_im;
// 		dot.z_re = tmp_re + ((double)env->mouse_x) / WIN_WIDTH;
// 		dot.z_im = tmp_im + ((double)env->mouse_y) / WIN_HEIGHT;
// 	}
// 	return (iter);
// }

// int	iter_burning_ship_1(t_dot dot, t_env *env)
// {
// 	int		iter;
// 	double	tmp_re;
// 	double	tmp_im;

// 	dot.z_im = 0;
// 	dot.z_re = 0;
// 	iter = -1;
// 	while (++iter < env->depth)
// 	{
// 		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
// 			break ;
// 		dot.z_re = fabs(dot.z_re);
// 		dot.z_im = fabs(dot.z_im);
// 		tmp_re = dot.z_re;
// 		tmp_im = dot.z_im;
// 		dot.z_re = tmp_re + dot.c_re;
// 		dot.z_im = tmp_im + dot.c_im;
// 	}
// 	return (iter);
// }

// int	iter_burning_ship_2(t_dot dot, t_env *env)
// {
// 	int		iter;
// 	double	tmp_re;
// 	double	tmp_im;

// 	dot.z_im = 0;
// 	dot.z_re = 0;
// 	iter = -1;
// 	while (++iter < env->depth)
// 	{
// 		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
// 			break ;
// 		dot.z_re = fabs(dot.z_re);
// 		dot.z_im = fabs(dot.z_im);
// 		tmp_re = POW2(dot.z_re) - POW2(dot.z_im);
// 		tmp_im = 2 * dot.z_re * dot.z_im;
// 		dot.z_re = tmp_re + dot.c_re;
// 		dot.z_im = tmp_im + dot.c_im;
// 	}
// 	return (iter);
// }

// int	iter_burning_ship_3(t_dot dot, t_env *env)
// {
// 	int		iter;
// 	double	tmp_re;
// 	double	tmp_im;

// 	dot.z_im = 0;
// 	dot.z_re = 0;
// 	iter = -1;
// 	while (++iter < env->depth)
// 	{
// 		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
// 			break ;
// 		dot.z_re = fabs(dot.z_re);
// 		dot.z_im = fabs(dot.z_im);
// 		tmp_re = POW3(dot.z_re) - 3 * dot.z_re * POW2(dot.z_im);
// 		tmp_im = 3 * POW2(dot.z_re) * dot.z_im - POW3(dot.z_im);
// 		dot.z_re = tmp_re + dot.c_re;
// 		dot.z_im = tmp_im + dot.c_im;
// 	}
// 	return (iter);
// }

// int	iter_burning_ship_4(t_dot dot, t_env *env)
// {
// 	int		iter;
// 	double	tmp_re;
// 	double	tmp_im;

// 	dot.z_im = 0;
// 	dot.z_re = 0;
// 	iter = -1;
// 	while (++iter < env->depth)
// 	{
// 		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
// 			break ;
// 		dot.z_re = fabs(dot.z_re);
// 		dot.z_im = fabs(dot.z_im);
// 		tmp_re = POW4(dot.z_re) + POW4(dot.z_im) - 6 * POW2(dot.z_re) * POW2(dot.z_im);
// 		tmp_im = 4 * dot.z_im * POW3(dot.z_re) - 4 * POW3(dot.z_im) * dot.z_re;
// 		dot.z_re = tmp_re + dot.c_re;
// 		dot.z_im = tmp_im + dot.c_im;
// 	}
// 	return (iter);
// }

// int	iter_burning_ship_5(t_dot dot, t_env *env)
// {
// 	int		iter;
// 	double	tmp_re;
// 	double	tmp_im;

// 	dot.z_im = 0;
// 	dot.z_re = 0;
// 	iter = -1;
// 	while (++iter < env->depth)
// 	{
// 		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
// 			break ;
// 		dot.z_re = fabs(dot.z_re);
// 		dot.z_im = fabs(dot.z_im);
// 		tmp_re = 5 * POW4(dot.z_im) * dot.z_re - 10 * POW2(dot.z_im) * POW3(dot.z_re) + POW5(dot.z_re);
// 		tmp_im = POW5(dot.z_im) - 10 * POW3(dot.z_im) * POW2(dot.z_re) + 5 * POW4(dot.z_re) * dot.z_im;
// 		dot.z_re = tmp_re + dot.c_re;
// 		dot.z_im = tmp_im + dot.c_im;
// 	}
// 	return (iter);
// }
