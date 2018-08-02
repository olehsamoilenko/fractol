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

int		key_hook(int key, void *v)
{
	t_view		*view;

	view = (t_view*)v;
	key == KEY_ESC ? exit(1) : 0;
	if (key == KEY_I)
	{
		iterate(view);
	}

	ft_bzero(view->img.img, WIN_WIDTH * WIN_HEIGHT * view->img.bits_per_pixel);
	draw(view);

	return (0);
}
