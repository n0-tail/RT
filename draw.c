/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:41:38 by anikkane          #+#    #+#             */
/*   Updated: 2020/10/06 13:43:28 by anikkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

static void					put_pixel(t_data *data, int x, int y, t_color color, char *texture)
{
	int					i;
	int	k;
	
	
	
	i = ((x * data->bits_per_pixel / 8) + (y * data->size_line));
	k = i;
if (i == 0)
{

printf("tama luku on i: %d jee\n", i);
printf("tama luku on: %d jee\n", texture[i]);

printf("tama luku on: %d jee\n", texture[i + 1]);

printf("tama luku on: %d jee\n", texture[i + 2]);

printf("tama luku on: %d jee\n", texture[i + 3]);
printf("tama luku on i: %d jee\n", i);
printf("tama luku on: %d jee\n", texture[i + 4]);

printf("tama luku on: %d jee\n", texture[i +  5]);

printf("tama luku on: %d jee\n", texture[i + 6]);

printf("tama luku on: %d jee\n", texture[i + 7]);
}
	data->data_addr[i] = ((int)(texture[k+2]));
	i++;
	data->data_addr[i] = ((int)(texture[k+1]));
	i++;
	data->data_addr[i] = ((int)(texture[k+3]));
	i++;
	data->data_addr[i] = ((int)(texture[k]));
color.channel[0] = 1;
	if (i < 6)
{

printf("tama luku on i: %d jee\n", i);
printf("tama luku on: %d jee\n", data->data_addr[0]);

printf("tama luku on: %d jee\n", data->data_addr[1]);

printf("tama luku on: %d jee\n", data->data_addr[2]);

printf("tama luku on: %d jee\n", data->data_addr[3]);

}
}

void						put_color(t_data *data, t_rgb rgb, int x, int y, char *texture)
{
	t_color			color;

	color.channel[0] = 1;
	color.channel[1] = (int8_t)((min(rgb.red * 255, 255)));
	color.channel[2] = (int8_t)((min(rgb.green * 255, 255)));
	color.channel[3] = (int8_t)((min(rgb.blue * 255, 255)));

	put_pixel(data, x, y, color, texture);
}

void						draw(t_data *data)
{
	int				y;
	int				x;
	int			i;
char				*texture;
t_rgb color;
color.red = 100;
texture = read_texture();

i = 0;
while (i < 10)
{
	printf("%d\n", texture[i]);
	i++;

}
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_color(data, color, x, y, texture);
			//get_color(data, x, y, texture);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
}
