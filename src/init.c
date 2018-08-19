/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 14:13:37 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/02 14:13:40 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		init_img(t_env *env)
{
	env->img.img_ptr = mlx_new_image(env->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	env->img.img = mlx_get_data_addr(env->img.img_ptr,
		&env->img.bits_per_pixel, &env->img.size_line, &env->img.endian);
	env->img.bits_per_pixel /= 8;
}

void			init_kernel(t_env *env)
{
	t_kernel	kernel;
	cl_int		err;
	

	kernel.device_id = NULL;
	kernel.context = NULL;
	kernel.command_queue = NULL;
	kernel.mem = NULL;
	kernel.program = NULL;
	kernel.kernel = NULL;

	err = clGetDeviceIDs(NULL, CL_DEVICE_TYPE_GPU, 1, &kernel.device_id, NULL);
	if (err)
		ft_printf("kernel: error with clGetDeviceIDs\n");

	kernel.context = clCreateContext(NULL, 1, &kernel.device_id, NULL, NULL, &err);
	if (err)
		ft_printf("kernel: error with clCreateContext\n");

	kernel.command_queue = clCreateCommandQueue(kernel.context, kernel.device_id, 0, &err);
	if (err)
		ft_printf("kernel: error with clCreateCommandQueue\n");

	kernel.mem = clCreateBuffer(kernel.context, CL_MEM_READ_ONLY,
		WIN_WIDTH * WIN_HEIGHT * env->img.bits_per_pixel, NULL, &err);
	if (err)
		ft_printf("kernel: error with clCreateBuffer\n");

	char		*obj;
	int			fd;
	obj = (char*)ft_memalloc(MAX_SOURCE_SIZE);
	fd = open("./kernel/func.cl", O_RDONLY);
	read(fd, obj, MAX_SOURCE_SIZE);
	kernel.program = clCreateProgramWithSource(kernel.context, 1, (const char**)&obj, NULL, &err);
	if (err)
		ft_printf("kernel: error with clCreateProgramWithSource\n");

	err = clBuildProgram(kernel.program, 1, &kernel.device_id, NULL, NULL, &err);
	if (err)
		ft_printf("kernel: error with clBuildProgram\n");

	kernel.kernel = clCreateKernel(kernel.program, "func", &err);
	if (err)
		ft_printf("kernel: error with clCreateKernel\n");

	
	

}

t_env			init(char *name)
{
	t_env	env;

	env.mlx_ptr = mlx_init();
	env.win_ptr = mlx_new_window(env.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "fractol");

	env.depth = 20;

	// env.move_x = 0;
	// env.move_y = 0;

	// env.mouse_x = 0.5 * WIN_HEIGHT;
	// env.mouse_y = 0.5 * WIN_WIDTH;

	env.re_min = -2;
	env.delta_re = 4;
	env.im_min = -1;
	env.delta_im = 2;
	env.mouse_x = WIN_HEIGHT / 2;
	env.mouse_y = WIN_WIDTH / 2;
	env.mouse_on = 0;
	env.power = 2;
	env.color = 0;
	if (ft_strequ(name, "mandelbrot"))
	{
		env.iter_func[0] = &iter_mandelbrot_1;
		env.iter_func[1] = &iter_mandelbrot_2;
		env.iter_func[2] = &iter_mandelbrot_3;
		env.iter_func[3] = &iter_mandelbrot_4;
		env.iter_func[4] = &iter_mandelbrot_5;
	}
	else if (ft_strequ(name, "julia"))
	{
		env.iter_func[0] = &iter_julia_1;
		env.iter_func[1] = &iter_julia_2;
		env.iter_func[2] = &iter_julia_3;
		env.iter_func[3] = &iter_julia_4;
		env.iter_func[4] = &iter_julia_5;
	}
	else if (ft_strequ(name, "burning_ship"))
	{
		env.iter_func[0] = &iter_burning_ship_1;
		env.iter_func[1] = &iter_burning_ship_2;
		env.iter_func[2] = &iter_burning_ship_3;
		env.iter_func[3] = &iter_burning_ship_4;
		env.iter_func[4] = &iter_burning_ship_5;
	}
	else if (ft_strequ(name, "mandelbar"))
	{
		env.iter_func[0] = &iter_mandelbar_1;
		env.iter_func[1] = &iter_mandelbar_2;
		env.iter_func[2] = &iter_mandelbar_3;
		env.iter_func[3] = &iter_mandelbar_4;
		env.iter_func[4] = &iter_mandelbar_5;
	}
	else if (ft_strequ(name, "new"))
	{
		env.iter_func[0] = &iter_new_1;
		env.iter_func[1] = &iter_new_2;
		env.iter_func[2] = &iter_new_3;
		env.iter_func[3] = &iter_new_4;
		env.iter_func[4] = &iter_new_5;
	}
	else
	{
		usage();
	}
	init_img(&env);
	init_kernel(&env);
	return (env);
}
