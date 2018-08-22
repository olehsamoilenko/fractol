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
	/////////////////////////////////////////

	/////////////////////////////////////////
	draw(env);
	return (0);
}

int			mouse_controls(int event, int x, int y, t_env *env)
{
	double	k;

	k = 1;
	if ((event == MOUSE_UP || event == MOUSE_DOWN) && !env->start)
	{
		if (event == MOUSE_UP)
		{
			env->depth += 3;
			k = (double)9/ 10;
		}
		else 
		{
			if (env->depth >= 20)
				env->depth -= 3;
			if (env->delta_im < 4.4)
				k = (double)10 / 9;
		}
		env->delta_im *= k;
		env->delta_re *= k;
		env->re_min = env->re_min + ((double)x / WIN_WIDTH) * env->delta_re / k * (1 - k);
		env->im_min = env->im_min - ((double)(WIN_HEIGHT - y) / WIN_HEIGHT) * env->delta_im / k * (1 - k);
	}

	ft_bzero(env->img.img, WIN_WIDTH * WIN_HEIGHT * env->img.bits_per_pixel);
	draw(env);
	return (0);
}

int		key_hook(int key, void *v)
{
	t_env		*env;

	env = (t_env*)v;
	
	if (key == KEY_ESC)	
		exit(1); // exit
	if (!env->start)
	{
		if (key == KEY_C)
			env->color = (env->color + 1) % 7;
		else if (key == KEY_H)
			env->help = (env->help + 1) % 2;
		else if (key == KEY_SPACE)
			env->mouse_on = (env->mouse_on + 1) % 2;
		else if (key == KEY_BACKSPACE)
			default_settings(env);
		else if (key == KEY_LEFT)
			env->re_min -= 0.05 * env->delta_re;
		else if (key == KEY_RIGHT)
			env->re_min += 0.05 * env->delta_re;
		else if (key == KEY_UP)
			env->im_min -= 0.05 * env->delta_im;
		else if (key == KEY_DOWN)
			env->im_min += 0.05 * env->delta_im;
		else if (key == KEY_ONE || key == KEY_TWO || key == KEY_THREE || key == KEY_FOUR || key == KEY_FIVE)
		{
			if (key == KEY_ONE)
				env->power = 1;
			else if (key == KEY_TWO)
				env->power = 2;
			else if (key == KEY_THREE)
				env->power = 3;
			else if (key == KEY_FOUR)
				env->power = 4;
			else if (key == KEY_FIVE)
				env->power = 5;
			create_kernel(env);
		}
		else if (key == KEY_PLUS)
			env->depth += 1;
		else if (key == KEY_MINUS && env->depth > 2)
			env->depth -= 1;
		// mlx_clear_window(env->mlx_ptr, env->win_ptr);
		ft_bzero(env->img.img, WIN_WIDTH * WIN_HEIGHT * env->img.bits_per_pixel); //?
	}
		
	
	
	env->start = 0;
	draw(env);
	

	return (0);
}
