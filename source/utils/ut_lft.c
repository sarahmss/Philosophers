/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_lft.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 19:15:22 by smodesto          #+#    #+#             */
/*   Updated: 2022/03/05 23:30:59 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	if (str != NULL)
	{
		while (str[len] != '\0')
			len++;
	}
	return (len);
}

char	*ft_strcpy(char *destination, const char *source)
{
	char	*ptr;

	if (destination == NULL)
		return (NULL);
	ptr = destination;
	while (*source != '\0')
	{
		*destination = *source;
		destination++;
		source++;
	}
	*destination = '\0';
	return (ptr);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	int		result;
	char	*str1;

	sign = 1;
	i = 0;
	result = 0;
	str1 = (char *)str;
	while (str1[i] == ' ' || str1[i] == '\t' || str1[i] == '\f'
		|| str1[i] == '\r' || str1[i] == '\n' || str1[i] == '\v')
		i++;
	if (str1[i] == '-' || str1[i] == '+')
	{
		if (str1[i] == '-')
			sign *= -1;
		i++;
	}
	while (48 <= str1[i] && str1[i] <= 57)
	{
		result = result * 10 + (str1[i] - '0');
		i++;
	}
	return (sign * result);
}
