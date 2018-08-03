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

# define KEY_UP 126
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_LEFT 123

# define KEY_PLUS 69
# define KEY_MINUS 78

# define MOUSE_UP 4
# define MOUSE_DOWN 5
// # define MOUSE_LEFT 1
// # define MOUSE_RIGHT 2

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h> //trash

typedef struct	s_dot
{
	float		z_re;
	float		z_im;
	float		c_re;
	float		c_im;
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

	int			depth;
	float		move_x;
	float		move_y;
	int			zoom;

	int			mouse_x;
	int			mouse_y;

	float		re_min;
	float		re_max;
	float		im_min;
	float		im_max;

	t_img		img;
}				t_view;

void			iterate(t_view *view);

void			draw_mandelbrot(t_view *view);


t_view			init(void);

int				key_hook(int key, void *v);
int				mouse_controls(int event, int x, int y, t_view *view);
int				move_with_mouse(int x, int y, t_view *view);

#endif
