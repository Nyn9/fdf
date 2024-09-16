/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 19:11:01 by nferrad           #+#    #+#             */
/*   Updated: 2024/09/16 19:45:20 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	parse_map(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		free(lines[i]);
		lines[i] = NULL;
		i++;
	}
	free(lines);
	return (i);
}

int	check_map(char *file/*, t_img *data*/)
{
	int		fd;
	char	*line;
	int		height;
	int		width;
	int		nb;

	nb = 0;
	height = 0;
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	width = parse_map(ft_split(line, ' '));
	while (line != NULL)
	{
		nb += parse_map(ft_split(line, ' '));
		height++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	if (height * width == nb && nb)
		return (1);
	return (0);
}

void	new_point(t_point **point, int x, int y, int z)
{
	t_point	*new;
	t_point	*tmp;

	new = malloc(sizeof(t_point));
	new->x = x;
	new->y = y;
	new->z = z;
	new->next = NULL;
	if (!(*point))
	{
		*point = new;
		return ;
	}
	tmp = *point;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

void	fill_point(char **line, t_point **point)
{
	static int	y = 0;
	int			x;

	x = 0;
	while (line[x])
	{
		new_point(point, x, y, ft_atoi(line[x]));
		free(line[x]);
		line[x] = NULL;
		x++;
	}
	y++;
	free(line);
}

t_point	*get_point(char *file)
{
	t_point	*point;
	char	*line;
	int		fd;

	point = NULL;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	line = get_next_line(fd);
	while (line != NULL)
	{
		fill_point(ft_split(line, ' '), &point);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (point);
}
