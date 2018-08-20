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

# define GLOBAL_WORK_SIZE (size_t[3]){WIN_WIDTH, WIN_HEIGHT, 0}

void	pixel_put_img(t_env *env, int x, int y, int color)
{
	if (x <= 0 || x >= WIN_WIDTH || y <= 0 || y >= WIN_HEIGHT)
		return ;
	*(int *)(env->img.img + x * env->img.bits_per_pixel +
		y * env->img.size_line) = mlx_get_color_value(env->mlx_ptr, color);
}

// int		rgb_to_color(unsigned char r, unsigned char g, unsigned char b) //here?
// {
// 	return (r << 16 | g << 8 | b);
// }



void	queue_kernel(t_env *env)
{
	cl_int	error;
	int		i;
	
	i = -1;
	error = clSetKernelArg(env->kernel.kernel, ++i, sizeof(cl_mem), (void*)&env->kernel.mem);
	if (error)
		ft_printf("kernel: error with parameter %d in clSetKernelArg\n", i);
	error = clSetKernelArg(env->kernel.kernel, ++i, sizeof(int), (void*)&env->name);
	if (error)
		ft_printf("kernel: error with parameter %d in clSetKernelArg\n", i);
	error = clSetKernelArg(env->kernel.kernel, ++i, sizeof(int), (void*)&env->power);
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
	error = clSetKernelArg(env->kernel.kernel, ++i, sizeof(double), (void*)&env->delta_re);
	if (error)
		ft_printf("kernel: error with parameter %d in clSetKernelArg\n", i);
	error = clSetKernelArg(env->kernel.kernel, ++i, sizeof(double), (void*)&env->delta_im);
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

void	draw(t_env *env)
{


	ft_bzero(env->img.img, WIN_HEIGHT * WIN_WIDTH * env->img.bits_per_pixel); // yes?
	queue_kernel(env);

	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img.img_ptr, 0, 0);
}
