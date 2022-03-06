/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:35:55 by smodesto          #+#    #+#             */
/*   Updated: 2022/03/06 01:23:21 by smodesto         ###   ########.fr       */
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

static int	print_fed(t_philos *philo)
{
	t_bool		all_fed;
	t_philos	*temp;

	temp = philo;
	all_fed = true;
	if (philo->next == philo && philo->time.eaten_times == philo->time.must_eat)
	{
		printf("\n\n All philosophers have been fed 🧠🤔🍜\n");
		return (1);
	}
	else if (philo->next == philo)
		return (0);
	while (temp->next != philo)
	{
		if (temp->time.eaten_times < temp->time.must_eat)
			all_fed = false;
		temp = temp->next;
	}
	if (all_fed == true)
	{
		printf("\n\n All philosophers have been fed 🧠🤔🍜\n");
		return (1);
	}
	return (0);
}

void	print_exit_status(t_philos *philos)
{
	if (philos->time.must_eat)
		if (print_fed(philos))
			return ;
	if (check_if_died(philos))
		printf("\n\n Some Philosopher died 😵🥣\n");
}
