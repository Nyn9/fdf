/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 19:11:01 by nferrad           #+#    #+#             */
/*   Updated: 2024/09/16 03:35:47 by nferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	parse_map(char *line)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]) && !ft_isdigit(line[i + 1])
			&& line[i + 1] != ',')
			nb++;
		i++;
	}
	return (nb);
}

int	check_map(char *file)
{
	int		fd;
	char	*line;
	int		height;
	int		width;
	int		nb;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	height = 0;
	nb = 0;
	while (line != NULL)
	{
		nb += parse_map(line);
		if (!height)
			width = nb;
		height++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	if (height * width == nb && nb != 0)
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
	if (fd == -1)
		return (NULL);
	line = get_next_line(fd);
	while (line != NULL)
	{
		fill_point(ft_split(line, ' '), &point);
		free(line);
		line = get_next_line(fd);
	}
	return (point);
}
