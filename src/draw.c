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

static void	queue_kernel(t_env *env)
{
	int		i;
	double	step_re;
	double	step_im;

	i = -1;
	clSetKernelArg(env->kernel.kernel, ++i, sizeof(cl_mem),
		(void*)&env->kernel.mem);
	clSetKernelArg(env->kernel.kernel, ++i, sizeof(int), (void*)&env->color);
	clSetKernelArg(env->kernel.kernel, ++i, sizeof(int),
		(void*)&env->depth);
	clSetKernelArg(env->kernel.kernel, ++i, sizeof(double),
		(void*)&env->re_min);
	clSetKernelArg(env->kernel.kernel, ++i, sizeof(double),
		(void*)&env->im_min);
	step_re = env->delta_re / (WIN_WIDTH - 1);
	clSetKernelArg(env->kernel.kernel, ++i, sizeof(double), (void*)&step_re);
	step_im = env->delta_im / (WIN_HEIGHT - 1);
	clSetKernelArg(env->kernel.kernel, ++i, sizeof(double), (void*)&step_im);
	clSetKernelArg(env->kernel.kernel, ++i, sizeof(int), (void*)&env->mouse_x);
	clSetKernelArg(env->kernel.kernel, ++i, sizeof(int), (void*)&env->mouse_y);
	clEnqueueNDRangeKernel(env->kernel.command_queue, env->kernel.kernel, 2,
		NULL, GLOBAL_WORK_SIZE, NULL, 0, NULL, NULL);
	clEnqueueReadBuffer(env->kernel.command_queue, env->kernel.mem, CL_TRUE, 0,
	sizeof(unsigned int) * WIN_HEIGHT * WIN_WIDTH, env->img.img, 0, NULL, NULL);
}

static void	help(t_env *env)
{
	mlx_string_put(env->mlx_ptr, env->win_ptr, WIN_WIDTH - 220, 10,
		RGB(255, 255, 255), "RESET     : BACKSPACE");
	mlx_string_put(env->mlx_ptr, env->win_ptr, WIN_WIDTH - 220,
		WIN_HEIGHT - 110, RGB(255, 255, 255), "ZOOM      : WHEEL");
	mlx_string_put(env->mlx_ptr, env->win_ptr, WIN_WIDTH - 220,
		WIN_HEIGHT - 90, RGB(255, 255, 255), "COLORS    : C");
	mlx_string_put(env->mlx_ptr, env->win_ptr, WIN_WIDTH - 220,
		WIN_HEIGHT - 70, RGB(255, 255, 255), "ITERATIONS: + -");
	mlx_string_put(env->mlx_ptr, env->win_ptr, WIN_WIDTH - 220,
		WIN_HEIGHT - 50, RGB(255, 255, 255), "POWER     : 1 2 3 4 5");
	mlx_string_put(env->mlx_ptr, env->win_ptr, WIN_WIDTH - 220,
		WIN_HEIGHT - 30, RGB(255, 255, 255), "MOVE      : ARROWS");
	mlx_string_put(env->mlx_ptr, env->win_ptr, 10, WIN_HEIGHT - 50,
		RGB(255, 255, 255), "HELP      : H");
	mlx_string_put(env->mlx_ptr, env->win_ptr, 10, WIN_HEIGHT - 30,
		RGB(255, 255, 255), "EXIT      : ESC");
}

void		draw(t_env *env)
{
	char	*number;
	char	*label;

	queue_kernel(env);
	number = ft_itoa(env->depth);
	label = ft_strjoin("ITERATIONS: ", number);
	ft_strdel(&number);
	if (env->start)
		intro(env);
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img.img_ptr, 0, 0);
	mlx_string_put(env->mlx_ptr, env->win_ptr, 10, 10, RGB(255, 255, 255),
		label);
	ft_strdel(&label);
	if (env->start)
		intro_labels(env);
	if (env->help)
		help(env);
}
