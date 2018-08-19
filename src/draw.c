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

void	pixel_put_img(t_env *env, int x, int y, int color)
{
	if (x <= 0 || x >= WIN_WIDTH || y <= 0 || y >= WIN_HEIGHT)
		return ;
	*(int *)(env->img.img + x * env->img.bits_per_pixel +
		y * env->img.size_line) = mlx_get_color_value(env->mlx_ptr, color);
}

int		rgb_to_color(unsigned char r, unsigned char g, unsigned char b)
{
	return (r << 16 | g << 8 | b);
}

int		iterating_rgb(int iter, t_env *env)
{
	if (env->color == 0 && iter != env->depth)
		return (rgb_to_color((float)iter / (float)env->depth * 200, 0, 0));
	else if (env->color == 1 && iter % 2 == 1)
		return (rgb_to_color(200, 0, 0));
	else if (env->color == 2)
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
	else if (env->color == 3)
		return (rgb_to_color((float)iter / env->depth * 255,
		(float)iter / env->depth * 255,
		150 + (float)iter / env->depth * 155));
	else if (env->color == 4)
		return (rgb_to_color(sin(iter / env->depth) * 255,
				cos(iter) * 255,
				100 + (float)iter / env->depth * 155));
	else if (env->color == 5)
		return (rgb_to_color(cos((float)iter) * 100,
				sin((float)iter) * 100,
				1 - cos((float)iter)) * 150);
	return (0);
}



void	draw(t_env *env)
{
	int		x;
	int		y;
	t_dot	dot;



	float	step_re;
	float	step_im;


	step_re = env->delta_re / (WIN_WIDTH - 1);
	step_im = env->delta_im / (WIN_HEIGHT - 1);
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			dot.c_re = env->re_min + x * step_re; // ok
			dot.c_im = env->im_min - (WIN_HEIGHT - y) * step_im; // +-ok
			
			// pixel_put_img(env, x, y, iterating_rgb(env->iter_func[env->power - 1](dot, env), env->depth));
			pixel_put_img(env, x, y, iterating_rgb(env->iter_func[env->power - 1](dot, env), env));
		}
	}
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr,
		env->img.img_ptr, 0, 0);
}
