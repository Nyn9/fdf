/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:34:58 by nferrad           #+#    #+#             */
/*   Updated: 2024/09/18 19:16:48 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error(const char *error_msg)
{
	ft_printf("%s\n", error_msg);
}

int	check_file_format(char *filename)
{
	int		i;

	i = 0;
	while (filename[i] && filename[i - 1] != '.')
		i++;
	if (!ft_strncmp((filename + i), "fdf", 3))
		return (1);
	return (0);
}

void	close_window(t_fdf *fdf, int is_error)
{
	mlx_destroy_image(fdf->mlx->mlx, fdf->img->img);
	mlx_destroy_window(fdf->mlx->mlx, fdf->mlx->win);
	mlx_destroy_display(fdf->mlx->mlx);
	free_lst(&fdf->mlx->points);
	free(fdf->mlx->mlx);
	free(fdf->mlx);
	free(fdf);
	if (is_error)
		error(ERR_FILE);
	exit(-1);
}

int	key_pressed(int keycode, t_fdf *fdf)
{
	if (keycode == 65307)
		close_window(fdf, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_mlx	*mlx;
	t_img	img;
	t_fdf	*fdf;

	if (argc != 2 || !check_file_format(argv[1]))
	{
		error(ERR_FMT);
		exit(-1);
	}
	fdf = malloc(sizeof(t_fdf));
	mlx = malloc(sizeof(t_mlx));
	fdf->mlx = mlx;
	fdf->img = &img;
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "FDF !");
	img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	mlx->points = get_point(open(argv[1], O_RDONLY));
	if (!mlx->points)
		close_window(fdf, 1);
	draw_fdf(&img, mlx);
	mlx_key_hook(mlx->win, key_pressed, fdf);
	mlx_loop(mlx->mlx);
	return (0);
}
