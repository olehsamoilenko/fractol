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


# define EVENT_KEYS 2
# define EVENT_MOUSE 6
# define EVENT_CLOSE 17

# define KEY_ESC 53
// # define KEY_I 34
# define KEY_C 8

# define KEY_SPACE 49

# define KEY_UP 126
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_LEFT 123

# define KEY_PLUS 69
# define KEY_MINUS 78

# define KEY_ONE 18
# define KEY_TWO 19
# define KEY_THREE 20
# define KEY_FOUR 21
# define KEY_FIVE 23

# define MOUSE_UP 4
# define MOUSE_DOWN 5
// # define MOUSE_LEFT 1
// # define MOUSE_RIGHT 2

#define POW2(a) a * a
#define POW3(a) a * a * a
#define POW4(a) a * a * a * a
#define POW5(a) a * a * a * a * a

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
	// float		move_x;
	// float		move_y;
	// int			zoom;

	int			mouse_x;
	int			mouse_y;
	int			mouse_on;

	float		re_min;
	float		delta_re;
	// float		re_max;
	float		im_min;
	float		delta_im;

	int			(*iter_func[5])(t_dot, struct s_view *);
	// int			(*iter_func)(t_dot, struct s_view *, int power);
	int			power;
	int			color;
	// float		im_max;

	t_img		img;
}				t_view;

void			iterate(t_view *view);

void			draw(t_view *view);

void			usage(void);


t_view			init(char *name);

int				key_hook(int key, void *v);
int				mouse_controls(int event, int x, int y, t_view *view);
int				move_with_mouse(int x, int y, t_view *view);

int				iter_mandelbrot_1(t_dot dot, t_view *view);
int				iter_mandelbrot_2(t_dot dot, t_view *view);
int				iter_mandelbrot_3(t_dot dot, t_view *view);
int				iter_mandelbrot_4(t_dot dot, t_view *view);
int				iter_mandelbrot_5(t_dot dot, t_view *view);
int				iter_mandelbar_1(t_dot dot, t_view *view);
int				iter_mandelbar_2(t_dot dot, t_view *view);
int				iter_mandelbar_3(t_dot dot, t_view *view);
int				iter_mandelbar_4(t_dot dot, t_view *view);
int				iter_mandelbar_5(t_dot dot, t_view *view);
int				iter_julia_1(t_dot dot, t_view *view);
int				iter_julia_2(t_dot dot, t_view *view);
int				iter_julia_3(t_dot dot, t_view *view);
int				iter_julia_4(t_dot dot, t_view *view);
int				iter_julia_5(t_dot dot, t_view *view);
int				iter_burning_ship_1(t_dot dot, t_view *view);
int				iter_burning_ship_2(t_dot dot, t_view *view);
int				iter_burning_ship_3(t_dot dot, t_view *view);
int				iter_burning_ship_4(t_dot dot, t_view *view);
int				iter_burning_ship_5(t_dot dot, t_view *view);
int				iter_new_1(t_dot dot, t_view *view);
int				iter_new_2(t_dot dot, t_view *view);
int				iter_new_3(t_dot dot, t_view *view);
int				iter_new_4(t_dot dot, t_view *view);
int				iter_new_5(t_dot dot, t_view *view);


#endif
