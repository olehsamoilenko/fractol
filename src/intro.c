/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 17:53:05 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/23 17:53:07 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	pixel_put_img(t_env *env, int x, int y, int color)
{
	if (x <= 0 || x >= WIN_WIDTH || y <= 0 || y >= WIN_HEIGHT)
		return ;
	*(int *)(env->img.img + x * env->img.bits_per_pixel +
		y * env->img.size_line) = mlx_get_color_value(env->mlx_ptr, color);
}

void		intro_labels(t_env *env)
{
	char	*s;
	int		i;

	s = ft_strdup(env->name);
	i = -1;
	while (s[++i])
		s[i] = ft_toupper(s[i]);
	mlx_string_put(env->mlx_ptr, env->win_ptr,
		(WIN_WIDTH - ft_strlen(s) * ALPHA_WIDTH) / 2,
		WIN_HEIGHT / 2 - ALPHA_HEIGHT / 2, RGB(255, 255, 255), s);
	ft_strdel(&s);
	s = "press any key";
	mlx_string_put(env->mlx_ptr, env->win_ptr,
		(WIN_WIDTH - ft_strlen(s) * ALPHA_WIDTH) / 2,
		WIN_HEIGHT / 2 - ALPHA_HEIGHT / 2 + 20, RGB(0, 0, 0), s);
	s = "osamoile";
	mlx_string_put(env->mlx_ptr, env->win_ptr,
		(WIN_WIDTH - ft_strlen(s) * ALPHA_WIDTH) / 2 + 255,
		WIN_HEIGHT / 2 - ALPHA_HEIGHT / 2 + 135, RGB(0, 0, 0), s);
}

void		intro(t_env *env)
{
	int		i;
	int		j;

	i = WIN_HEIGHT / 2 - 150;
	while (++i < WIN_HEIGHT / 2 + 150)
	{
		j = WIN_WIDTH / 2 - 300;
		pixel_put_img(env, j - 1, i, RGB(255, 255, 255));
		pixel_put_img(env, j, i, RGB(255, 255, 255));
		while (++j < WIN_WIDTH / 2 + 300)
		{
			pixel_put_img(env, j, WIN_HEIGHT / 2 - 151, RGB(255, 255, 255));
			pixel_put_img(env, j, WIN_HEIGHT / 2 - 150, RGB(255, 255, 255));
			pixel_put_img(env, j, i, RGB(150, 0, 0));
			pixel_put_img(env, j, WIN_HEIGHT / 2 + 150, RGB(255, 255, 255));
			pixel_put_img(env, j, WIN_HEIGHT / 2 + 151, RGB(255, 255, 255));
		}
		pixel_put_img(env, j, i, RGB(255, 255, 255));
		pixel_put_img(env, j + 1, i, RGB(255, 255, 255));
	}
}
