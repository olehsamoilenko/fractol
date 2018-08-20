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

# define MAX_SOURCE_SIZE 0x400000




// # define FRACTAL_JULIA 1
// # define FRACTAL_MANDELBROT 2
// # define FRACTAL_BURNING_SHIP 3
// # define FRACTAL_MANDELBAR 4


# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <OpenCL/opencl.h>
# include <stdio.h> //trash

typedef struct	s_dot
{
	double		z_re;
	double		z_im;
	double		c_re;
	double		c_im;
}				t_dot;

typedef struct	s_img
{
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	char		*img;
	void		*img_ptr;
}				t_img;

typedef struct	s_kernel
{
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	command_queue;
	cl_mem				mem;
	cl_program			program;
	cl_kernel			kernel;

}				t_kernel;

typedef struct	s_env
{
	void		*mlx_ptr;
	void		*win_ptr;

	int			power;
	int			color;
	int			depth;

	int			mouse_x;
	int			mouse_y;
	int			mouse_on;

	double		re_min;
	double		delta_re;
	double		im_min;
	double		delta_im;



	t_kernel	kernel;
	t_img		img;
}				t_env;



void			draw(t_env *env);

void			usage(void);


t_env			init(char *name);

int				key_hook(int key, void *v);
int				mouse_controls(int event, int x, int y, t_env *env);
int				move_with_mouse(int x, int y, t_env *env);


void			create_kernel(char *name, t_env *env);


#endif
