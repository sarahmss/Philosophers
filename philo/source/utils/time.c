/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:41:54 by smodesto          #+#    #+#             */
/*   Updated: 2022/04/28 16:28:30 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Philosophers.h"

long	get_current_time(void)
{
	struct timeval	current_time;
	long long int	milliseconds;

	gettimeofday(&current_time, NULL);
	milliseconds = current_time.tv_sec * 1000;
	milliseconds += current_time.tv_usec / 1000;
	return (milliseconds);
}

void	delay(int delay_time)
{
	long	start_time;

	start_time = get_current_time();
	while ((get_current_time() - start_time) < (long)delay_time)
		usleep(10);
}

long	formated_time(long first_time)
{
	return (get_current_time() - first_time);
}

void	msleep(int time_in_ms)
{
	long	start_time;

	start_time = get_current_time();
	while ((get_current_time() - start_time) < (long)time_in_ms)
		usleep(10);
}
