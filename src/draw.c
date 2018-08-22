/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 15:10:52 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/02 15:10:53 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"



void	pixel_put_img(t_env *env, int x, int y, int color)
{
	if (x <= 0 || x >= WIN_WIDTH || y <= 0 || y >= WIN_HEIGHT)
		return ;
	*(int *)(env->img.img + x * env->img.bits_per_pixel +
		y * env->img.size_line) = mlx_get_color_value(env->mlx_ptr, color);
}


void	queue_kernel(t_env *env)
{
	cl_int	error;
	int		i;

	double	step_re = env->delta_re / (WIN_WIDTH - 1);
	double	step_im = env->delta_im / (WIN_HEIGHT - 1);
	
	i = -1;
	error = clSetKernelArg(env->kernel.kernel, ++i, sizeof(cl_mem), (void*)&env->kernel.mem);
	if (error)
		ft_printf("kernel: error with parameter %d in clSetKernelArg\n", i);
	error = clSetKernelArg(env->kernel.kernel, ++i, sizeof(int), (void*)&env->color);
	if (error)
		ft_printf("kernel: error with parameter %d in clSetKernelArg\n", i);
	error = clSetKernelArg(env->kernel.kernel, ++i, sizeof(int), (void*)&env->depth);
	if (error)
		ft_printf("kernel: error with parameter %d in clSetKernelArg\n", i);
	error = clSetKernelArg(env->kernel.kernel, ++i, sizeof(double), (void*)&env->re_min);
	if (error)
		ft_printf("kernel: error with parameter %d in clSetKernelArg\n", i);
	error = clSetKernelArg(env->kernel.kernel, ++i, sizeof(double), (void*)&env->im_min);
	if (error)
		ft_printf("kernel: error with parameter %d in clSetKernelArg\n", i);
	error = clSetKernelArg(env->kernel.kernel, ++i, sizeof(double), (void*)&step_re);
	if (error)
		ft_printf("kernel: error with parameter %d in clSetKernelArg\n", i);
	error = clSetKernelArg(env->kernel.kernel, ++i, sizeof(double), (void*)&step_im);
	if (error)
		ft_printf("kernel: error with parameter %d in clSetKernelArg\n", i);
	error = clSetKernelArg(env->kernel.kernel, ++i, sizeof(int), (void*)&env->mouse_x);
	if (error)
		ft_printf("kernel: error with parameter %d in clSetKernelArg\n", i);
	error = clSetKernelArg(env->kernel.kernel, ++i, sizeof(int), (void*)&env->mouse_y);
	if (error)
		ft_printf("kernel: error with parameter %d in clSetKernelArg\n", i);
	
	error = clEnqueueNDRangeKernel(env->kernel.command_queue, env->kernel.kernel, 2,
		NULL, GLOBAL_WORK_SIZE, NULL, 0, NULL, NULL);
	if (error)
		ft_printf("kernel: error with clEnqueueNDRangeKernel\n");

	error = clEnqueueReadBuffer(env->kernel.command_queue, env->kernel.mem, CL_TRUE, 0,
		sizeof(unsigned int) * WIN_HEIGHT * WIN_WIDTH, env->img.img, 0, NULL, NULL);
	if (error)
		ft_printf("kernel: error with clEnqueueReadBuffer\n");
	
}



void	help(t_env *env)
{
	mlx_string_put(env->mlx_ptr, env->win_ptr, WIN_WIDTH - 220, 10, RGB(255, 255, 255),	"RESET     : BACKSPACE");

	mlx_string_put(env->mlx_ptr, env->win_ptr, WIN_WIDTH - 220, WIN_HEIGHT - 110, RGB(255, 255, 255),	"ZOOM      : WHEEL");
	mlx_string_put(env->mlx_ptr, env->win_ptr, WIN_WIDTH - 220, WIN_HEIGHT - 90, RGB(255, 255, 255),	"COLORS    : C");
	mlx_string_put(env->mlx_ptr, env->win_ptr, WIN_WIDTH - 220, WIN_HEIGHT - 70, RGB(255, 255, 255),	"ITERATIONS: + -");
	mlx_string_put(env->mlx_ptr, env->win_ptr, WIN_WIDTH - 220, WIN_HEIGHT - 50, RGB(255, 255, 255),	"POWER     : 1 2 3 4 5");
	mlx_string_put(env->mlx_ptr, env->win_ptr, WIN_WIDTH - 220, WIN_HEIGHT - 30, RGB(255, 255, 255),	"MOVE      : ARROWS");
	
	mlx_string_put(env->mlx_ptr, env->win_ptr, 10, WIN_HEIGHT - 50, RGB(255, 255, 255),		"HELP      : H");
	mlx_string_put(env->mlx_ptr, env->win_ptr, 10, WIN_HEIGHT - 30, RGB(255, 255, 255),		"EXIT      : ESC");
}

void	intro_labels(t_env *env)
{
	char *s;
	int		i;

	
	s = ft_strdup(env->name);
	i = -1;
	while (s[++i])
		s[i] = ft_toupper(s[i]);

	mlx_string_put(env->mlx_ptr, env->win_ptr,
		(WIN_WIDTH - ft_strlen(s) * ALPHA_WIDTH) / 2,
		WIN_HEIGHT / 2 - ALPHA_HEIGHT / 2, RGB(255, 255, 255), s);
	s = "press any key";
	mlx_string_put(env->mlx_ptr, env->win_ptr,
		(WIN_WIDTH - ft_strlen(s) * ALPHA_WIDTH) / 2,
		WIN_HEIGHT / 2 - ALPHA_HEIGHT / 2 + 20, RGB(0, 0, 0), s);
	s = "osamoile";
	mlx_string_put(env->mlx_ptr, env->win_ptr,
		(WIN_WIDTH - ft_strlen(s) * ALPHA_WIDTH) / 2 + 255,
		WIN_HEIGHT / 2 - ALPHA_HEIGHT / 2 + 135, RGB(0, 0, 0), s);

}

void	intro(t_env *env)
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

void	draw(t_env *env)
{
	
	
	queue_kernel(env);

	printf("re_min: %f\n", env->re_min);
	printf("im_min: %f\n", env->im_min);
	printf("delta_im: %f\n", env->delta_im);
	printf("delta_re: %f\n", env->delta_re);
	printf("depth: %d\n", env->depth);
	printf("mouse_x: %d\n", env->mouse_x);
	printf("mouse_y: %d\n\n", env->mouse_y);

	if (env->start)
		intro(env);
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img.img_ptr, 0, 0);
	// mlx_string_put(env->mlx_ptr, env->win_ptr, 10, 10, RGB(255, 255, 255),
	// 	ft_strjoin("ITERATIONS: ", ft_itoa(env->depth)));
	if (env->start)
		intro_labels(env);
	if (env->help)
		help(env);
	
	
}
