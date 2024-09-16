/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:34:58 by nferrad           #+#    #+#             */
/*   Updated: 2024/09/16 19:45:33 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	close_window(t_fdf *fdf)
{
	mlx_destroy_image(fdf->mlx->mlx, fdf->img->img);
	mlx_destroy_window(fdf->mlx->mlx, fdf->mlx->win);
	mlx_destroy_display(fdf->mlx->mlx);
	free_lst(&fdf->mlx->points);
	free(fdf->mlx->mlx);
	free(fdf->mlx);
	free(fdf);
	exit(EXIT_SUCCESS);
}

int	key_pressed(int keycode, t_fdf *fdf)
{
	if (keycode == 65307)
		close_window(fdf);
	return (0);
}

int	main(int argc, char **argv)
{
	t_mlx	*mlx;
	t_img	img;
	t_fdf	*fdf;

	if (argc != 2 || !check_file_format(argv[1]))
	{
		ft_printf(ERR_FMT"\n");
		return (-1);
	}
	else if (!check_map(argv[1]/*, &img*/))
	{
		ft_printf(ERR_FILE"\n");
		return (-1);
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
	mlx->points = get_point(argv[1]);
	draw_fdf(&img, mlx);
	mlx_key_hook(mlx->win, key_pressed, fdf);
	mlx_loop(mlx->mlx);
	return (0);
}
