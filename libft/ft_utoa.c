/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhirlpo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 17:33:01 by jwhirlpo          #+#    #+#             */
/*   Updated: 2021/01/23 17:52:55 by jwhirlpo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
static    int            ft_intlen(unsigned int n)
{
    int            i;
    long long    tmp;

    i = 0;
    tmp = n;
    if (tmp == 0)
        return (1);
    if (tmp < 0)
    {
        tmp *= -1;
        i++;
    }
    while (tmp > 0)
    {
        tmp /= 10;
        i++;
    }
    return (i);
}

static    long long    ft_ifneg(char *c, unsigned int n)
{
    long long tmp;

    tmp = n;
    if (tmp < 0)
    {
        c[0] = '-';
        tmp *= -1;
    }
    return (tmp);
}

char                *ft_utoa(unsigned int n)
{
    char        *c;
    int            len;
    long long    tmp;

    len = ft_intlen(n);
    if (!(c = (char *)malloc(sizeof(char) * (len + 1))))
        return (NULL);
    c[len] = '\0';
    tmp = ft_ifneg(c, n);
    len--;
    if (tmp == 0)
    {
        c[0] = '0';
        return (c);
    }
    while (len >= 0 && tmp != 0)
    {
        c[len] = (tmp % 10) + '0';
        tmp /= 10;
        len--;
    }
//    free(c);
    return (c);
}
