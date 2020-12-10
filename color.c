/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 11:41:16 by anikkane          #+#    #+#             */
/*   Updated: 2020/11/18 12:53:16 by anikkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

static t_ray		reflection_direction(t_ray ray, t_vector n, t_data *data)
{
	t_vector	tmp;
	double		reflect;
	double		r_factor;


	//if (data->mat == 1)
	//{
	//	ref_value = 30;
	//}
	//else if (data->mat == 2)
	//{
		//r_factor = 3.5;
	//}
	//else 
	//{
		//ref_value = 0;
	//}
	
	if (ft_strcmp(data->hit.obj_name, "plane") == 0)
	r_factor = 30;
	else
		r_factor = 3.5;
	
	
	ray.start = vector_copy(ray.newstart);
	reflect = r_factor * vectordot(ray.target, n);
	tmp = vectorscale(reflect, n);
	ray.target = vector_minus(ray.target, tmp);
	return (ray);
}

static void			search_intersection(t_data *data, t_ray ray)
{
	int			i;

	i = data->objnbr - 1;
	data->hit.obj_idx = -1;
	data->hit.t = 1000.0;
	data->hit.find_shadow = 0;
	while (i >= 0)
	{
		if (data->cylinder->nbr > i && intersectcylinder(ray, data, i) == 1)
			set_hit(data, "cylinder", i);
		if (data->sphere->nbr > i && intersectsphere(ray, data, i) == 1)
			set_hit(data, "sphere", i);
		if (data->plane->nbr > i && intersectplane(data, i, ray) == 1)
			set_hit(data, "plane", i);
		if (data->cone->nbr > i && intersectcone(ray, data, i) == 1)
			set_hit(data, "cone", i);
		i--;
	}
}

static t_ray		new_hit_direction(t_data *data, t_ray org_ray, t_vector *n)
{
	double		temp;
	t_ray		ray;

	ray.newstart = vector_copy(org_ray.newstart);
	ray.start = vector_copy(org_ray.start);
	ray.target = vector_copy(org_ray.target);
	if (ft_strcmp(data->hit.obj_name, "cone") == 0)
		*n = new_start_dir_cone(data, &ray);
	if (ft_strcmp(data->hit.obj_name, "sphere") == 0)
	{
		*n = new_start_dir_sphere(data, &ray);
		temp = vectordot(*n, *n);
		if (temp == 0)
		{
			n->x = 101010;
			return (ray);
		}
		temp = 1.0f / sqrt(temp);
		*n = vectorscale(temp, *n);
	}
	if (ft_strcmp(data->hit.obj_name, "plane") == 0)
		*n = new_start_dir_plane(data, &ray);
	if (ft_strcmp(data->hit.obj_name, "cylinder") == 0)
		*n = new_start_dir_cylinder(data, &ray);
	return (ray);
}

static t_rgb		search_light_and_shadow(t_data *data, t_ray ray,
		t_vector n, t_rgb rgb)
{
	int			i;

	ray.target = vector_copy(n);
	i = (data->spot->nbr - 1);
	while (i >= 0)
	{
		if (data->iter == data->org_iter)
		{
			if (shadow(data, ray.newstart, i) != 1)
				rgb = get_light(data, rgb, ray, i);
		}
		else
			rgb = get_light(data, rgb, ray, i);
		i--;
	}
	return (rgb);
}


 char    *read_texture(void)
{
    int     fd;
    int     check;
   char     text_data[1];
    int     i;
char    *data;
 char    *filename;
int 	x;
    int     width;
    int     height;
 

    height = 1000;
    width = 1000;
x = 0;
i = 0;
    filename = "wood.ppm";
fd = open(filename, O_RDONLY);
if (!(data = (char*)malloc(sizeof(char) * width * height * 4)))
		return (NULL);
	i = 0;
	while (i < width * height)
	{
		data[i * 4 + 0] = 1;
		data[i * 4 + 1] = 1;
		data[i * 4 + 2] = 1;
		data[i * 4 + 3] = 1;
		i++;
	}
i = 0;
while ((check = read(fd, text_data, 1)) > 0 && width * height * 4)
{
	if (x % 3 == 0)
	i++;
	x++;
    data[i] = text_data[0];
	i++;
	
}
i = 0;
while (i < 10)
{
	printf("%d\n", data[i]);
	i++;

}


close (fd);
return (data);
}

void				get_color(t_data *data, int x, int y, char *texture)
{
	t_vector	n;
	t_rgb		rgb;
	t_ray		ray;
	data->x = x;
	data->y = y;
	ray = init_pixel(data, x, y, &rgb);
	while (data->iter > 0 && data->light_scale > 0.0f)
	{
		search_intersection(data, ray);
		if (data->hit.obj_idx == -1)
			break ;
		ray = new_hit_direction(data, ray, &n);
		if (n.x == 101010)
			break ;
		rgb = search_light_and_shadow(data, ray, n, rgb);
		data->iter--;
		ray = reflection_direction(ray, n, data);
		put_color(data, rgb, x, y, texture);
	}

}



