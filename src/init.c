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

void			create_kernel(t_env *env)
{
	char	*name;
	char	number[2];

	if (env->kernel.kernel)
		clReleaseKernel(env->kernel.kernel);
	number[0] = '0' + env->power;
	number[1] = 0;
	name = ft_strjoin(env->name, number);
	env->kernel.kernel = clCreateKernel(env->kernel.program, name, NULL);
	ft_strdel(&name);
}

void			default_settings(t_env *env)
{
	env->depth = 50;
	env->re_min = -2.3;
	env->im_min = 1.1;
	env->delta_re = 4.4;
	env->delta_im = 2.2;
}

static void		init_img(t_env *env)
{
	env->img.img_ptr = mlx_new_image(env->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	env->img.img = mlx_get_data_addr(env->img.img_ptr,
		&env->img.bits_per_pixel, &env->img.size_line, &env->img.endian);
	env->img.bits_per_pixel /= 8;
}

static void		init_kernel(t_env *env)
{
	char	*obj;
	int		fd;
	size_t	size;

	clGetDeviceIDs(NULL, CL_DEVICE_TYPE_GPU, 1, &env->kernel.device_id, NULL);
	env->kernel.context = clCreateContext(NULL, 1, &env->kernel.device_id,
		NULL, NULL, NULL);
	env->kernel.command_queue = clCreateCommandQueue(env->kernel.context,
		env->kernel.device_id, 0, NULL);
	obj = ft_memalloc(MAX_SOURCE_SIZE);
	fd = open("./kernel/fractol.cl", O_RDONLY);
	size = read(fd, obj, MAX_SOURCE_SIZE);
	close(fd);
	env->kernel.program = clCreateProgramWithSource(env->kernel.context, 1,
		(const char**)&obj, (const size_t*)&size, NULL);
	ft_memdel((void**)&obj);
	clBuildProgram(env->kernel.program, 1, &env->kernel.device_id,
		NULL, NULL, NULL);
	env->kernel.mem = clCreateBuffer(env->kernel.context, CL_MEM_READ_ONLY,
		WIN_WIDTH * WIN_HEIGHT * env->img.bits_per_pixel, NULL, NULL);
	env->kernel.kernel = NULL;
	create_kernel(env);
}

t_env			init(char *name)
{
	t_env	env;

	env.mlx_ptr = mlx_init();
	env.win_ptr = mlx_new_window(env.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "fractol");
	env.name = name;
	env.mouse_x = 363;
	env.mouse_y = 459;
	env.mouse_on = 0;
	env.power = 2;
	env.color = 0;
	env.help = 1;
	env.start = 1;
	default_settings(&env);
	init_img(&env);
	init_kernel(&env);
	return (env);
}
