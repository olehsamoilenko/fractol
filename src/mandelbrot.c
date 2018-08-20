/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 03:07:12 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/09 03:07:14 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	iter_mandelbrot_1(t_dot dot, t_env *env)
{
	int		iter;
	double	tmp_re;
	double	tmp_im;

	dot.z_im = 0;
	dot.z_re = 0;
	iter = -1;
	while (++iter < env->depth)
	{
		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
			break ;
		tmp_re = dot.z_re;
		tmp_im = dot.z_im;
		dot.z_re = tmp_re + dot.c_re;
		dot.z_im = tmp_im + dot.c_im;
	}
	return (iter);
}

int	iter_mandelbrot_2(t_dot dot, t_env *env)
{
	int		iter;
	double	tmp_re;
	double	tmp_im;

	dot.z_im = 0;
	dot.z_re = 0;
	iter = -1;
	while (++iter < env->depth)
	{
		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
			break ;
		tmp_re = POW2(dot.z_re) - POW2(dot.z_im);
		tmp_im = 2 * dot.z_re * dot.z_im;
		dot.z_re = tmp_re + dot.c_re;
		dot.z_im = tmp_im + dot.c_im;
	}
	return (iter);
}

int	iter_mandelbrot_3(t_dot dot, t_env *env)
{
	int		iter;
	double	tmp_re;
	double	tmp_im;

	dot.z_im = 0;
	dot.z_re = 0;
	iter = -1;
	while (++iter < env->depth)
	{
		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
			break ;
		tmp_re = POW3(dot.z_re) - 3 * dot.z_re * POW2(dot.z_im);
		tmp_im = 3 * POW2(dot.z_re) * dot.z_im - POW3(dot.z_im);
		dot.z_re = tmp_re + dot.c_re;
		dot.z_im = tmp_im + dot.c_im;
	}
	return (iter);
}

int	iter_mandelbrot_4(t_dot dot, t_env *env)
{
	int		iter;
	double	tmp_re;
	double	tmp_im;

	dot.z_im = 0;
	dot.z_re = 0;
	iter = -1;
	while (++iter < env->depth)
	{
		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
			break ;
		tmp_re = POW4(dot.z_re)
		+ POW4(dot.z_im) - 6 * POW2(dot.z_re) * POW2(dot.z_im);
		tmp_im = 4 * dot.z_im * POW3(dot.z_re) - 4 * POW3(dot.z_im) * dot.z_re;
		dot.z_re = tmp_re + dot.c_re;
		dot.z_im = tmp_im + dot.c_im;
	}
	return (iter);
}


int	iter_mandelbrot_5(t_dot dot, t_env *env)
{
	int		iter;
	double	tmp_re;
	double	tmp_im;

	dot.z_im = 0;
	dot.z_re = 0;
	iter = -1;
	while (++iter < env->depth)
	{
		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
			break ;
		tmp_re = 5 * POW4(dot.z_im) * dot.z_re - 10 * POW2(dot.z_im) * POW3(dot.z_re) + POW5(dot.z_re);
		tmp_im = POW5(dot.z_im) - 10 * POW3(dot.z_im) * POW2(dot.z_re) + 5 * POW4(dot.z_re) * dot.z_im;
		dot.z_re = tmp_re + dot.c_re;
		dot.z_im = tmp_im + dot.c_im;
	}
	return (iter);
}



int	iter_new_1(t_dot dot, t_env *env)
{
	int		iter;
	double	tmp_re;
	double	tmp_im;

	dot.z_im = 0;
	dot.z_re = 0;
	iter = -1;
	while (++iter < env->depth)
	{
		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
			break ;
		tmp_re = dot.z_re;
		tmp_im = dot.z_im;
		dot.z_re = fabs(tmp_re + dot.c_re);
		dot.z_im = tmp_im + dot.c_im;
	}
	return (iter);
}

int	iter_new_2(t_dot dot, t_env *env)
{
	int		iter;
	double	tmp_re;
	double	tmp_im;

	dot.z_im = 0;
	dot.z_re = 0;
	iter = -1;
	while (++iter < env->depth)
	{
		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
			break ;
		tmp_re = POW2(dot.z_re) - POW2(dot.z_im);
		tmp_im = 2 * dot.z_re * dot.z_im;
		dot.z_re = fabs(tmp_re + dot.c_re);
		dot.z_im = tmp_im + dot.c_im;
	}
	return (iter);
}

int	iter_new_3(t_dot dot, t_env *env)
{
	int		iter;
	double	tmp_re;
	double	tmp_im;

	dot.z_im = 0;
	dot.z_re = 0;
	iter = -1;
	while (++iter < env->depth)
	{
		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
			break ;
		tmp_re = POW3(dot.z_re) - 3 * dot.z_re * POW2(dot.z_im);
		tmp_im = 3 * POW2(dot.z_re) * dot.z_im - POW3(dot.z_im);
		dot.z_re = fabs(tmp_re + dot.c_re);
		dot.z_im = tmp_im + dot.c_im;
	}
	return (iter);
}

int	iter_new_4(t_dot dot, t_env *env)
{
	int		iter;
	double	tmp_re;
	double	tmp_im;

	dot.z_im = 0;
	dot.z_re = 0;
	iter = -1;
	while (++iter < env->depth)
	{
		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
			break ;
		tmp_re = POW4(dot.z_re)
		+ POW4(dot.z_im) - 6 * POW2(dot.z_re) * POW2(dot.z_im);
		tmp_im = 4 * dot.z_im * POW3(dot.z_re) - 4 * POW3(dot.z_im) * dot.z_re;
		dot.z_re = fabs(tmp_re + dot.c_re);
		dot.z_im = tmp_im + dot.c_im;
	}
	return (iter);
}

int	iter_new_5(t_dot dot, t_env *env)
{
	int		iter;
	double	tmp_re;
	double	tmp_im;

	dot.z_im = 0;
	dot.z_re = 0;
	iter = -1;
	while (++iter < env->depth)
	{
		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
			break ;
		tmp_re = 5 * POW4(dot.z_im) * dot.z_re - 10 * POW2(dot.z_im) * POW3(dot.z_re) + POW5(dot.z_re);
		tmp_im = POW5(dot.z_im) - 10 * POW3(dot.z_im) * POW2(dot.z_re) + 5 * POW4(dot.z_re) * dot.z_im;
		dot.z_re = fabs(tmp_re + dot.c_re);
		dot.z_im = tmp_im + dot.c_im;
	}
	return (iter);
}