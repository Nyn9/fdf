/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferrad <nferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 19:11:01 by nferrad           #+#    #+#             */
/*   Updated: 2024/09/18 19:13:16 by nferrad          ###   ########.fr       */
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

int	check_map(char *file)
{
	int		fd;
	char	*line;
	int		nb_prev;
	int		nb;
	int		return_value;

	nb = 0;
	nb_prev = 0;
	return_value = 1;
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		nb = parse_map(ft_split(line, ' '));
		free(line);
		if (nb_prev != nb && nb_prev)
			return_value = 0;
		nb_prev = nb;
		line = get_next_line(fd);
	}
	free(line);
	line = NULL;
	close(fd);
	return (return_value);
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

int	fill_point(char **line, t_point **point)
{
	static int	y = 0;
	int			x;
	int			return_value;

	x = 0;
	return_value = 1;
	while (line[x])
	{
		if (return_value)
		{
			new_point(point, x, y, ft_atoi(line[x]));
			if (!ft_atoi(line[x]) && line[x][0] != '0' && line[x][0] != '\n')
				return_value = 0;
		}
		free(line[x]);
		line[x] = NULL;
		x++;
	}
	y++;
	free(line);
	return (return_value);
}

t_point	*get_point(int fd)
{
	t_point	*point;
	char	*line;
	int		error;

	error = 0;
	point = NULL;
	if (fd < 0)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		if (!fill_point(ft_split(line, ' '), &point))
			error = 1;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	if (error)
	{
		free_lst(&point);
		return (0);
	}
	return (point);
}
