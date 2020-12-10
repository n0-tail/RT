/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:18:21 by anikkane          #+#    #+#             */
/*   Updated: 2020/11/18 12:39:39 by anikkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		handle_expose(t_data *tmp_data)
{

t_data *data;

data = (t_data *)tmp_data;
	data->bits_per_pixel = '\0';
	data->objnbr = 0;
	data->sphere->nbr = 0;
	data->spot->nbr = 0;
	data->cone->nbr = 0;
	data->cylinder->nbr = 0;
	data->plane->nbr = 0;
	data->org_iter = 2;
	data->hit.find_shadow = 0;
	data->hit.preobj_name = NULL;
	data->hit.obj_name = NULL;
	data->exposure = 1;
	read_scene((t_data *)data);

	return (0);


}

char			*if_negative(char *line, char *str, int *i, int *y)
{
	if (line[*i] == '-')
	{
		if (str[0] != '\0')
			data_read_error();
		str[0] = '-';
		*i += 1;
		*y = 1;
	}
	return (str);
}

static void		check_name(t_data *data, char *data_name, char *line)
{
	if ((ft_strcmp(data_name, "SPHERE") == 0) && data->sphere->nbr < 10)
		parse_sphere(line, data);
	else if ((ft_strcmp(data_name, "CYLINDER") == 0) && data->cylinder->nbr
			< 10)
		parse_cylinder(line, data);
	else if ((ft_strcmp(data_name, "CONE") == 0) && data->cone->nbr < 10)
		parse_cone(line, data);
	else if ((ft_strcmp(data_name, "SPOT") == 0) && data->spot->nbr < 10)
		parse_spot(line, data);
	else if ((ft_strcmp(data_name, "PLANE") == 0) && data->cone->nbr < 10)
		parse_plane(line, data);
	else if (ft_strcmp(data_name, "CAMERA") == 0)
		parse_camera(line, data);
	else if (ft_strcmp(data_name, "TEXTURE") == 0)
		parse_texture(line, data);
}

static char		*parse_name(char *line, char *tmp)
{
	int		i;
	int		y;

	i = 1;
	y = 0;
	if (line[i++] == 32 || line[i++] == 9)
	{
		while (ft_isalpha(line[i]) == 1 && y < 8)
			tmp[y++] = line[i++];
	}
	tmp[y] = '\0';
	free(line);
	return (tmp);
}

int				read_scene(t_data *data)
{
	char	*line;
	char	*data_name;
	int		i;
	int		x;
	int 	fd;
	fd = 0; 
if ((fd = open(data->scene_name, O_RDONLY)) > 0)
		init_data(data);
	else
		wrong_scene_name();
	if (!(data_name = (char *)malloc((sizeof(char) * (8 + 1)))))
		memory_allocation_fail();
	x = 0;
	i = 0;
	while ((get_next_line(fd, &line)) == 1)
	{
		if (line[i] == '*')
		{
			data_name = parse_name(line, data_name);
			if (get_next_line(fd, &line) == 1)
				check_name(data, data_name, line);
			ft_memset(data_name, 0, ft_strlen(data_name));
		}
		if (line[i] != '*')
			free(line);
	}
	free(data_name);
init_mlx(data);
//ft_putnbr(data->cylinder->start_xyz[3].x);
	draw(data);
	return (0);
}
