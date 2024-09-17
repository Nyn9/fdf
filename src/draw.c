/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 21:39:56 by nferrad           #+#    #+#             */
/*   Updated: 2024/09/17 20:59:39 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_pixel	set_iso(t_point *point)
{
	double	x;
	double	y;
	t_pixel	pixel;

	x = (point->x - point->y) * cos(0.523599);
	y = (-(point->z)) + (point->x + point->y) * sin(0.523599);
	x = WIDTH / 2 + (x * ZOOM);
	y = HEIGHT / 2 + (y * ZOOM);
	pixel.x = x;
	pixel.y = y;
	pixel.color = 0xFFFFFF;
	return (pixel);
}

t_line	*set_horizontal(t_point *point)
{
	t_line	*line;
	t_pixel	pixel;

	if ((point && point->next) && point->y == point->next->y)
	{
		line = malloc(sizeof(t_line));
		pixel = set_iso(point);
		line->beginx = pixel.x;
		line->beginy = pixel.y;
		pixel = set_iso(point->next);
		line->endx = pixel.x;
		line->endy = pixel.y;
		line->color = pixel.color;
		return (line);
	}
	return (NULL);
}

t_line	*set_vertical(t_point *point)
{
	t_point	*next_point;
	t_pixel	pixel;
	t_line	*line;

	if (!point->next)
		return (NULL);
	next_point = point->next;
	while (point->x != next_point->x)
	{
		if (next_point->next)
			next_point = next_point->next;
		else
			return (NULL);
	}
	line = malloc(sizeof(t_line));
	pixel = set_iso(point);
	line->beginx = pixel.x;
	line->beginy = pixel.y;
	pixel = set_iso(next_point);
	line->endx = pixel.x;
	line->endy = pixel.y;
	line->color = pixel.color;
	return (line);
}

void	put_lines(t_img *data, t_line *line)
{
	int		pixels;
	double	dx;
	double	dy;
	double	pixel_x;
	double	pixel_y;

	if (!line)
		return ;
	dx = line->endx - line->beginx;
	dy = line->endy - line->beginy;
	pixels = (int)sqrt(pow(dx, 2) + pow(dy, 2));
	dx /= pixels;
	dy /= pixels;
	pixel_x = line->beginx;
	pixel_y = line->beginy;
	while (pixels)
	{
		put_pixel(data, (int)pixel_x, (int)pixel_y, line->color);
		pixel_x += dx;
		pixel_y += dy;
		pixels--;
	}
	free(line);
}

void	draw_fdf(t_img *data, t_mlx *mlx)
{
	t_point	*point;

	point = mlx->points;
	while (point)
	{
		put_lines(data, set_horizontal(point));
		put_lines(data, set_vertical(point));
		point = point->next;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, data->img, 0, 0);
}
