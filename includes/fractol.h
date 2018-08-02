/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 11:39:25 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/02 11:39:26 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define WIN_HEIGHT 720
# define WIN_WIDTH 1280

// # define WIN_HEIGHT 10
// # define WIN_WIDTH 10

# define EVENT_KEYS 2
# define EVENT_CLOSE 17

# define KEY_ESC 53
# define KEY_I 34

# define RE_MIN -2
# define RE_MAX 1
# define IM_MAX 1
# define IM_MIN -1

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>

typedef struct	s_dot
{
	float	z_re; // complex x
	float	z_im; // complex y
	float	c_re;
	float	c_im;
}				t_dot;

typedef struct	s_img
{
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	char		*img;
	char		*img_ptr;
}				t_img;

typedef struct	s_view
{
	void		*mlx_ptr;
	void		*win_ptr;

	t_dot		**values;

	t_img		img;
}				t_view;

void			iterate(t_view *view);

void			draw(t_view *view);


t_view			init(void);

int				key_hook(int key, void *v);

#endif
