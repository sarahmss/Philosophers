/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:35:55 by smodesto          #+#    #+#             */
/*   Updated: 2022/03/05 15:43:06 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

long long int	get_current_time(void)
{
	struct timeval	current_time;
	long long int	milliseconds;

	gettimeofday(&current_time, NULL);
	milliseconds = current_time.tv_sec * 1000;
	milliseconds += current_time.tv_usec / 1000;
	return (milliseconds);
}

long long int	formated_time(long long int ms_start)
{
	return (get_current_time() - ms_start);
}

void	delay(long long int delay_time)
{
	usleep(delay_time * 1000);
}
