/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhirlpo <jwhirlpo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 17:22:13 by jwhirlpo          #+#    #+#             */
/*   Updated: 2021/01/28 11:50:49 by jwhirlpo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static void	resources(t_strukt *map)
{
	map->flags = 0;
	map->presicion = 0;
	map->spec_pres = 0;
	map->width = 0;
	map->spec_wid = 0; 
	map->type = 0;
	map->types = "cspdiuxX%";
}

static int			put_p_char(int c, t_strukt *map)
{
	int		i;
	
	i = 0;

	if (map->width < 0)
         map->width *= -1, map->flags = -1;
	if (map->flags == -1)
		write(1, &c,1);
	if (map->width > 1)
		while (map->width > 1)
		{
			if (map->flags == 0)
				write(1, " ",1), map->width--, map->length++;
			else if (map->flags == 1)
				write(1, "0",1), map->width--, map->length++;
			else
				write(1, " ",1), map->width--, map->length++;
		}
	if (map->flags != -1)
		write(1, &c, 1);
	return (1);
}

static int			put_p_str(char *str, t_strukt *map)
{
	int		i;
	int		j;	

	j = ft_strlen(str);
	i = 0;
	if (!str)
		j = 6;
	if (map->presicion < 0)
		map->spec_pres = 0;
	if (map->width < 0)
         map->width *= -1, map->flags = -1;
	if (map->spec_pres == 1 && map->flags == 1)
		map->flags = 0;
	if (map->width < i)
		map->width = 0;
	if (map->spec_pres == 1 && map->presicion < j)
		j = map->presicion;
	if (map->flags == 0)
		while (map->width > j && map->width != j)
			write(1, " ", 1), map->length++, map->width--;
	if (map->flags == 1)
		while (map->width > j && map->width != j)
			write(1, "0",1), map->length++, map->width--;
	if (str)
		while (i < j && str[i] != '\0')
			write(1, &str[i], 1), i++;
	else
		write(1, "(null)",j), map->length += j;
	if (map->flags == -1)
		while (map->width > j && map->width != j)
			write(1, " ", 1), map->length++, map->width--; 
	return (i);
}

static	int			intlen_h(unsigned long int n)
{
	int			i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 16;
		i++;
	}
	return (i);
}

static int			put_p_pointer(unsigned long int n, t_strukt *map)
{
	int i;
	int	j;
	
	i = intlen_h(n);
	// printf("|%i|", i);
	j = i;
	if (map->presicion < 0)
		map->spec_pres = 0;
	if (map->width < 0)
         map->width *= -1, map->flags = -1;
	if (map->spec_pres == 1 && map->flags == 1)
		map->flags = 0;
	if (map->width < i)
		map->width = 0;
	if (map->presicion > i && n >= 0)
		j = map->presicion;
	// else if (map->presicion >= i && n < 0)
	// 	j = map->presicion + 1;
	if (map->spec_pres == 1 && map->presicion == 0 && n == 0)
		j = 0, i = 0;
	if (map->flags == 0)
	{
		if (map->width > j)
			while (map->width > (j + 2) && map->width > 0)
				write(1, " ", 1), map->width--, map->length++;
//		if (n < 0)
		write(1, "0x", 2), map->length += 2;
		if (map->presicion > i)
			while (map->presicion > i)
				write(1, "0", 1), map->presicion--, map->length++;
	}
	if (map->flags == 1)
	{
		// if (n < 0)
		write(1, "0x", 2), map->length += 2;
 		while (map->width > (j + 2) && map->width > 0)
			write(1, "0", 1), map->width--, map->length++;
	}
	if (map->flags == -1)
	{
		// if (n < 0)
		write(1, "0x", 2), map->length += 2;
		if (map->presicion > i)
			while (map->presicion > i && map->presicion > 0)
				write(1, "0", 1), map->presicion--, map->length++; 
	}
	if (!(n == 0 && map->presicion == 0 && map->spec_pres == 1))
		put_hex_low(n), map->length += intlen_h(n);
	if (map->flags == -1)
		if (map->width > j)
			while (map->width > (j + 2) && map->width > 0)
				write(1, " ",1), map->width--, map->length++;
	return (0);
}
// {
// 	int i;
	
// 	i = intlen_h(n);
// 	if (map->presicion < 0)
// 		map->spec_pres = 0;
// 	if (map->width < 0)
//          map->width *= -1, map->flags = -1;
// 	if (map->spec_pres == 1 && map->flags == 1)
// 		map->flags = 0;
// 	if (map->spec_pres == 1 && map->presicion == 0 && n == 0)
// 		i = 0;
// 	if (map->flags == 0)
// 	{
// 		if (map->width > i + 2)
// 			while (map->width > (i + 2) && map->width > 0)
// 				write(1, " ", 1), map->width--, map->length++;
// 		write(1, "0x",2), map->length += 2;
// 		if (map->presicion > i)
// 			while (map->presicion > i && map->presicion > 0)
// 				write(1, "0", 1), map->presicion--, map->length++;
// 	}
// 	if (map->flags == 1)
// 	{
// 		write(1, "0x", 2), map->length += 2;
// 		if (map->width > i)
// 			while (map->width > (i + 2) && map->width > 0)
// 				write(1, "0", 1), map->width--, map->length++;
// 	}
// 	if (map->flags == -1)
// 	{
// 		write(1, "0x", 2), map->length += 2;
// 		if (map->spec_pres == 1 && map->presicion > i)
// 			while (map->presicion > i && map->presicion > 0)
// 				write(1, "0", 1), map->presicion--, map->length++;
// 	}
// 	if (!(map->spec_pres == 1 && n == 0 && map->presicion == 0))
// 		put_hex_low(n), map->length += intlen_h(n);
// 	if (map->flags == -1)
// 		if (map->width > i + 2)
// 			while (map->width > (i + 2) && map->width > 0)
// 				write(1, " ", 1), map->width--, map->length++;
// 	return (0);
// }
static int			intlen(long int n)
{
	int		i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		n *= -1, i++;
	while (n > 0)
		n /= 10, i++;
   return (i);	
}

static long	int			pow_ten(long int n)
{
	int	i;

	i = 1;
	while (n != 1)
	{
		i *= 10;
		n--;
	}
	return (i);
}

static int			put_p_int(long int n,t_strukt *map)
{
	int i;
	int	k;
	int	j;
	
	i = intlen(n);
	j = i;
	if (map->presicion < 0)
		map->spec_pres = 0;
	if (map->width < 0)
         map->width *= -1, map->flags = -1;
	if (map->spec_pres == 1 && map->flags == 1)
		map->flags = 0;
	if (map->width < i)
		map->width = 0;
	if (map->presicion > i && n >= 0)
		j = map->presicion;
	else if (map->presicion >= i && n < 0)
		j = map->presicion + 1;
	if (map->spec_pres == 1 && map->presicion == 0 && n == 0)
		j = 0, i = 0;
	if (map->flags == 0)
	{
		if (map->width > j)
			while (map->width > j && map->width > 0)
				write(1, " ", 1), map->width--, map->length++;
		if (n < 0)
			write(1, "-", 1), map->length++, n *= -1, i--;
		if (map->presicion > i)
			while (map->presicion > i && map->presicion > 0)
				write(1, "0", 1), map->presicion--, map->length++;
	}
	if (map->flags == 1)
	{
		if (n < 0)
			write(1, "-", 1), map->length++, n *= -1, i--;
 		while (map->width > j && map->width > 0)
			write(1, "0", 1), map->width--, map->length++;
	}
	if (map->flags == -1)
	{
		if (n < 0)
			write(1, "-", 1), map->length++, n *= -1, i--;
		if (map->presicion > i)
			while (map->presicion > i && map->presicion > 0)
				write(1, "0", 1), map->presicion--, map->length++; 
	}
	if (!(n == 0 && map->presicion == 0 && map->spec_pres == 1))
		while (i > 0)
    	{
        	k = n / pow_ten(i) + '0';
	        write(1, &k,1);
    	    n %= pow_ten(i);
	    	i--, map->length++, map->presicion--;
    	}
	if (map->flags == -1)
		if (map->width > j)
			while (map->width > j && map->width > 0)
				write(1, " ",1), map->width--, map->length++;
	return (i);
}

static int			put_p_hex_low(unsigned int n, t_strukt *map)
{
	int i;
	
	i = intlen_h(n);
	if (map->presicion < 0)
		map->spec_pres = 0;
	if (map->width < 0)
         map->width *= -1, map->flags = -1;
	if (map->spec_pres == 1 && map->flags == 1)
		map->flags = 0;
	if (map->width < i)
		map->width = 0;
	if (map->presicion > i && n >= 0)
		i = map->presicion;
	if (map->spec_pres == 1 && map->presicion == 0 && n == 0)
		i = 0;
	if (map->flags == 0)
	{
		if (map->width > i)
			while (map->width > i && map->width > 0)
				write(1, " ", 1), map->width--, map->length++;
		if (map->presicion > intlen_h(n))
			while (map->presicion > intlen_h(n) && map->presicion > 0)
				write(1, "0", 1), map->presicion--, map->length++;
	}
	if (map->flags == 1)
		if (map->width > i)
			while (map->width > i && map->width > 0)
				write(1, "0",1), map->width--, map->length++;
	if (map->flags == -1)
		if (map->presicion > intlen_h(n))
			while (map->presicion > intlen_h(n) && map->presicion > 0)
				write(1, "0", 1), map->presicion--, map->length++;
	if (!(n == 0 && map->presicion == 0 && map->spec_pres == 1))
		put_hex_low(n), map->length += intlen_h(n);
	if (map->flags == -1)
		if (map->width > i)
			while (map->width > i && map->width > 0)
				write(1, " ", 1), map->width--, map->length++;
	return (0);
}

static int			put_p_hex_up(unsigned int n, t_strukt *map)
{
	int i;
	
	i = intlen_h(n);
	if (map->presicion < 0)
		map->spec_pres = 0;
	if (map->width < 0)
         map->width *= -1, map->flags = -1;
	if (map->spec_pres == 1 && map->flags == 1)
		map->flags = 0;
	if (map->width < i)
		map->width = 0;
	if (map->presicion > i && n >= 0)
		i = map->presicion;
	if (map->spec_pres == 1 && map->presicion == 0 && n == 0)
		i = 0;
	if (map->flags == 0)
	{
		if (map->width > i)
			while (map->width > i && map->width > 0)
				write(1, " ", 1), map->width--, map->length++;
		if (map->presicion > intlen_h(n))
			while (map->presicion > intlen_h(n) && map->presicion > 0)
				write(1, "0", 1), map->presicion--, map->length++;
	}
	if (map->flags == 1)
		if (map->width > i)
			while (map->width > i && map->width > 0)
				write(1, "0",1), map->width--, map->length++;
	if (map->flags == -1)
		if (map->presicion > intlen_h(n))
			while (map->presicion > intlen_h(n) && map->presicion > 0)
				write(1, "0", 1), map->presicion--, map->length++;
	if (!(n == 0 && map->presicion == 0 && map->spec_pres == 1))
		put_hex_up(n), map->length += intlen_h(n);
	if (map->flags == -1)
		if (map->width > i)
			while (map->width > i && map->width > 0)
				write(1, " ", 1), map->width--, map->length++;
	return (0);
}

static int			put_p_perc(t_strukt *map)
{
	int		i;

	i = put_p_char('%', map);
	return (i);
}

static void			wht_spec(t_strukt *map)
{
	int		i;

	if (map->type == 'c')
		i = put_p_char((va_arg(map->ap, int)), map), map->length += i;
	else if (map->type == 's')
		i = put_p_str(va_arg(map->ap, char *), map), map->length += i;
	else if (map->type == 'p')
		i = put_p_pointer(va_arg(map->ap, unsigned long int), map),
		  map->length += i;
	else if (map->type == 'd')
		i = put_p_int(va_arg(map->ap, int), map), map->length += i;
	else if (map->type == 'i')
		i = put_p_int(va_arg(map->ap, int), map), map->length += i;
	else if (map->type == 'u')
		i = put_p_int(va_arg(map->ap, unsigned int), map), map->length += i;
	else if (map->type == 'x')
		i = put_p_hex_low(va_arg(map->ap, unsigned int), map), map->length += i;
	else if (map->type == 'X')
		i = put_p_hex_up(va_arg(map->ap, unsigned int), map), map->length += i;
	else if (map->type == '%')
		i = put_p_perc(map), map->length += i;
}

static char	*pars_line(char *line, t_strukt *map)
{
	int i;

	i = 1;
	resources(map);
	while (line[i])
	{
		if (line[i] == '-')
			map->flags = -1, i++;
		if (line[i] == '0' && line[i + 1] != '-')
		{
			if (map->flags != -1)
				map->flags = 1;
			i++;
		}
		if (ft_isdigit(line[i]) && line[i] != '0')
			while (ft_isdigit(line[i]) && line[i])
			{
				map->width = map->width * 10 + line[i] - '0', map->spec_wid = 1;
				i++;
			}
		else if (line[i] == '*')
			map->width = va_arg(map->ap, unsigned int), map->spec_wid = 1,i++;
		if (line[i] == '.' && ft_isdigit(line[i + 1]))
		{
			map->spec_pres = 1, i++;
			while (ft_isdigit((line[i])) && line[i])
			{
				map->presicion = map->presicion * 10 + line[i] - '0';
				i++;
			}
		}
		else if (line[i] == '.' && line[i + 1] == '*')
		{
			map->presicion = va_arg(map->ap, int);
			map->spec_pres = 1, i++;
		}
		else if (line[i] == '.' && !(line[i + 1] == '*' || ft_isdigit(line[i + 1])))
			map->presicion = 0, map->spec_pres = 1, i++;
		if (ft_strchr(map->types, line[i]))
		{
			map->type = line[i];
	   		i++;
			wht_spec(map);
			return (&line[i]);
		}
		if (line[i] != '\0')
			i++;
	}
	return(&line[i]);
}

int			ft_printf(const char *line, ...)
{
	t_strukt	map;
	char		*c;

	resources(&map);
	map.length = 0;
	c = (char *)line;
	va_start(map.ap, line);
	while (*c != '\0')
	{
		if (*c == '%')
		{
			if (!(c = pars_line(c, &map)))
			{
				va_end(map.ap);
				return (0);
			}
		}
		else
		{
			write(1, c, 1);
			c++;
			map.length += 1;
		}
	}
	va_end(map.ap);
	return (map.length);
}
