/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 18:01:23 by osamoile          #+#    #+#             */
/*   Updated: 2018/07/24 18:01:35 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			move_with_mouse(int x, int y, t_env *env)
{
	if (env->mouse_on)
	{
		env->mouse_x = x;
		env->mouse_y = y;
	}
	draw(env);
	return (0);
}

int			mouse_controls(int event, int x, int y, t_env *env)
{
	double	k;

	// x = 0;
	// y= 0;
	// x = WIN_WIDTH / 2;
	// y = WIN_HEIGHT / 2;
	if (event == MOUSE_UP || event == MOUSE_DOWN)
	{
		if (event == MOUSE_DOWN)
		{
			env->depth -= 3;
			k = (double)10 / 9;

		}
		else
		{
			env->depth += 3;
			k = (double)9/ 10;

		}
		env->delta_im *= k;
		env->delta_re *= k;
		env->re_min = env->re_min + ((double)x / WIN_WIDTH) * env->delta_re / k * (1 - k);
		env->im_min = env->im_min - ((double)(WIN_HEIGHT - y) / WIN_HEIGHT) * env->delta_im / k * (1 - k);
		// printf("re_min: %f im_min: %f\n", env->re_min, env->im_min);

	}
	ft_bzero(env->img.img, WIN_WIDTH * WIN_HEIGHT * env->img.bits_per_pixel);
	draw(env);
	return (0);
}

int		key_hook(int key, void *v)
{
	t_env		*env;

	env = (t_env*)v;
	key == KEY_ESC ? exit(1) : 0;

	if (key == KEY_C)
		env->color = (env->color + 1) % 6;
	else if (key == KEY_SPACE)
		env->mouse_on = (env->mouse_on + 1) % 2;
	// double delta = env->re_max - env->re_min;

	if (key == KEY_LEFT)
		env->re_min -= 0.05 * env->delta_re;
	if (key == KEY_RIGHT)
		env->re_min += 0.05 * env->delta_re;
	if (key == KEY_UP)
		env->im_min -= 0.05 * env->delta_im;
	if (key == KEY_DOWN)
		env->im_min += 0.05 * env->delta_im;

	
	if (key == KEY_ONE)
	{
		env->power = 1;
	}
	if (key == KEY_TWO)
	{
		env->power = 2;
		create_kernel("mandelbrot2", env);
	}
	if (key == KEY_THREE)
	{
		env->power = 3;
		create_kernel("mandelbrot3", env);
	}
	if (key == KEY_FOUR)
		env->power = 4;
	if (key == KEY_FIVE)
		env->power = 5;

	key == KEY_PLUS ? env->depth += 1 : 0;
	if (key == KEY_MINUS)
	{
		if (env->depth != 0)
			env->depth -= 1;
	}
	// printf("re_min: %f im_min: %f\n", env->re_min, env->im_min);

	ft_bzero(env->img.img, WIN_WIDTH * WIN_HEIGHT * env->img.bits_per_pixel);
	draw(env);

	return (0);
}
