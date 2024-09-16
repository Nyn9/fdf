/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:41:33 by nferrad           #+#    #+#             */
/*   Updated: 2024/09/16 03:46:12 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <math.h>
# include "libft.h"

# define WIDTH		900
# define HEIGHT		900
# define ZOOM 		10

# define ERR_FMT	"\033[0;31m\x1b[1mError :\033[0m Wrong format !\x1b[30m \
Try \"./fdf <filename>.fdf\".\033[0m"
# define ERR_FILE	"\033[0;31m\x1b[1mError :\033[0m File error !\x1b[30m \
Make sure your file is correct.\033[0m"

typedef struct s_pixel
{
	int	x;
	int	y;
	int	color;
}				t_pixel;

typedef struct s_point
{
	int				x;
	int				y;
	int				z;
	struct s_point	*next;
}			t_point;

typedef struct s_line
{
	int	beginx;
	int	endx;
	int	beginy;
	int	endy;
	int	color;
}				t_line;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_point	*points;
}				t_mlx;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

t_point	*get_point(char *file);
void	free_lst(t_point **lst);
void	put_pixel(t_img *img, int x, int y, int color);
int		check_map(char *file);
void	draw_fdf(t_img *data, t_mlx *mlx);

#endif