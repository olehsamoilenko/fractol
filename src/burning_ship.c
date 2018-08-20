/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 03:41:42 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/09 03:41:43 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	iter_burning_ship_1(t_dot dot, t_env *env)
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
		dot.z_re = fabs(dot.z_re);
		dot.z_im = fabs(dot.z_im);
		tmp_re = dot.z_re;
		tmp_im = dot.z_im;
		dot.z_re = tmp_re + dot.c_re;
		dot.z_im = tmp_im + dot.c_im;
	}
	return (iter);
}

int	iter_burning_ship_2(t_dot dot, t_env *env)
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
		dot.z_re = fabs(dot.z_re);
		dot.z_im = fabs(dot.z_im);
		tmp_re = POW2(dot.z_re) - POW2(dot.z_im);
		tmp_im = 2 * dot.z_re * dot.z_im;
		dot.z_re = tmp_re + dot.c_re;
		dot.z_im = tmp_im + dot.c_im;
	}
	return (iter);
}

int	iter_burning_ship_3(t_dot dot, t_env *env)
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
		dot.z_re = fabs(dot.z_re);
		dot.z_im = fabs(dot.z_im);
		tmp_re = POW3(dot.z_re) - 3 * dot.z_re * POW2(dot.z_im);
		tmp_im = 3 * POW2(dot.z_re) * dot.z_im - POW3(dot.z_im);
		dot.z_re = tmp_re + dot.c_re;
		dot.z_im = tmp_im + dot.c_im;
	}
	return (iter);
}

int	iter_burning_ship_4(t_dot dot, t_env *env)
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
		dot.z_re = fabs(dot.z_re);
		dot.z_im = fabs(dot.z_im);
		tmp_re = POW4(dot.z_re) + POW4(dot.z_im) - 6 * POW2(dot.z_re) * POW2(dot.z_im);
		tmp_im = 4 * dot.z_im * POW3(dot.z_re) - 4 * POW3(dot.z_im) * dot.z_re;
		dot.z_re = tmp_re + dot.c_re;
		dot.z_im = tmp_im + dot.c_im;
	}
	return (iter);
}

int	iter_burning_ship_5(t_dot dot, t_env *env)
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
		dot.z_re = fabs(dot.z_re);
		dot.z_im = fabs(dot.z_im);
		tmp_re = 5 * POW4(dot.z_im) * dot.z_re - 10 * POW2(dot.z_im) * POW3(dot.z_re) + POW5(dot.z_re);
		tmp_im = POW5(dot.z_im) - 10 * POW3(dot.z_im) * POW2(dot.z_re) + 5 * POW4(dot.z_re) * dot.z_im;
		dot.z_re = tmp_re + dot.c_re;
		dot.z_im = tmp_im + dot.c_im;
	}
	return (iter);
}
