/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhirlpo <jwhirlpo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 17:19:50 by jwhirlpo          #+#    #+#             */
/*   Updated: 2021/01/28 07:43:28 by jwhirlpo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include "./libft/libft.h"

# include <stdio.h>

typedef struct		s_strukt
{
	int			flags;
	int			presicion;
	int			spec_pres;
	int			width;
	int			spec_wid;
	int			length;
	char		type;
	char		*types;
	va_list		ap;
}					t_strukt;

int		ft_printf(const char *line, ...);
char    *itoa_hex_uns(unsigned long int n);
int     put_hex_low(unsigned long long int n);
int     put_hex_up(unsigned long int n);

#endif
