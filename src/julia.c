/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 03:32:07 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/09 03:32:09 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"



int	iter_julia_1(t_dot dot, t_view *view)
{
	int		iter;
	float	tmp_re;
	float	tmp_im;

	dot.z_im = dot.c_im;
	dot.z_re = dot.c_re;
	iter = -1;
	while (++iter < view->depth)
	{
		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
			break ;
		tmp_re = dot.z_re;
		tmp_im = dot.z_im;
		dot.z_re = tmp_re + ((float)view->mouse_x) / WIN_WIDTH;
		dot.z_im = tmp_im + ((float)view->mouse_y) / WIN_HEIGHT;
	}
	return (iter);
}

int	iter_julia_2(t_dot dot, t_view *view)
{
	int		iter;
	float	tmp_re;
	float	tmp_im;

	dot.z_im = dot.c_im;
	dot.z_re = dot.c_re;
	iter = -1;
	while (++iter < view->depth)
	{
		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
			break ;
		tmp_re = POW2(dot.z_re) - POW2(dot.z_im);
		tmp_im = 2 * dot.z_re * dot.z_im;
		dot.z_re = tmp_re + ((float)view->mouse_x) / WIN_WIDTH;
		dot.z_im = tmp_im + ((float)view->mouse_y) / WIN_HEIGHT;
	}
	return (iter);
}

int	iter_julia_3(t_dot dot, t_view *view)
{
	int		iter;
	float	tmp_re;
	float	tmp_im;

	dot.z_im = dot.c_im;
	dot.z_re = dot.c_re;
	iter = -1;
	while (++iter < view->depth)
	{
		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
			break ;
		tmp_re = POW3(dot.z_re) - 3 * dot.z_re * POW2(dot.z_im);
		tmp_im = 3 * POW2(dot.z_re) * dot.z_im - POW3(dot.z_im);
		dot.z_re = tmp_re + ((float)view->mouse_x) / WIN_WIDTH;
		dot.z_im = tmp_im + ((float)view->mouse_y) / WIN_HEIGHT;
	}
	return (iter);
}

int	iter_julia_4(t_dot dot, t_view *view)
{
	int		iter;
	float	tmp_re;
	float	tmp_im;

	dot.z_im = dot.c_im;
	dot.z_re = dot.c_re;
	iter = -1;
	while (++iter < view->depth)
	{
		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
			break ;
		tmp_re = POW4(dot.z_re)
		+ POW4(dot.z_im) - 6 * POW2(dot.z_re) * POW2(dot.z_im);
		tmp_im = 4 * dot.z_im * POW3(dot.z_re) - 4 * POW3(dot.z_im) * dot.z_re;
		dot.z_re = tmp_re + ((float)view->mouse_x) / WIN_WIDTH;
		dot.z_im = tmp_im + ((float)view->mouse_y) / WIN_HEIGHT;
	}
	return (iter);
}

int	iter_julia_5(t_dot dot, t_view *view)
{
	int		iter;
	float	tmp_re;
	float	tmp_im;

	dot.z_im = dot.c_im;
	dot.z_re = dot.c_re;
	iter = -1;
	while (++iter < view->depth)
	{
		if (POW2(dot.z_re) + POW2(dot.z_im) > 4)
			break ;
		tmp_re = 5 * POW4(dot.z_im) * dot.z_re - 10 * POW2(dot.z_im) * POW3(dot.z_re) + POW5(dot.z_re);
		tmp_im = POW5(dot.z_im) - 10 * POW3(dot.z_im) * POW2(dot.z_re) + 5 * POW4(dot.z_re) * dot.z_im;
		dot.z_re = tmp_re + ((float)view->mouse_x) / WIN_WIDTH;
		dot.z_im = tmp_im + ((float)view->mouse_y) / WIN_HEIGHT;
	}
	return (iter);
}