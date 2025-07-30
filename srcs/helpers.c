/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:10:57 by frey-gal          #+#    #+#             */
/*   Updated: 2025/07/29 18:37:30 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	ft_isdigit(int c)
{
	if ((c > 47 && c < 58))
		return (1);
	else
		return (0);
}

int	ft_isalpha(int c)
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123))
		return (1);
	else
		return (0);
}

void	ft_bzero(void *s, size_t n)
{
	char	*ptr;

	ptr = s;
	while (n--)
		*ptr++ = '\0';
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;

	i = 0;
	while (i < n)
	{
		if ((unsigned char)s1[i] > (unsigned char)s2[i] || (!s2[i]))
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if ((unsigned char)s1[i] < (unsigned char)s2[i] || (!s1[i]))
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	n;
	int	flag;

	flag = 0;
	n = 0;
	while ((*nptr <= 13 && *nptr >= 9) || *nptr == 32)
		nptr++;
	if (ft_strncmp(nptr, "-2147483648", 11) == 0)
		return (-2147483648);
	if (*nptr == '+')
		nptr++;
	else if (*nptr == '-')
	{
		nptr++;
		flag++;
	}
	while (*nptr > 47 && *nptr < 58)
	{
		n *= 10;
		n = n + (*nptr++ - '0');
	}
	if (flag)
		n = -n;
	return (n);
}
