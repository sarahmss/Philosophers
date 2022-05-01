/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:22:38 by smodesto          #+#    #+#             */
/*   Updated: 2022/05/01 11:08:36 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Philosophers.h"

static void	*only_one(t_philos *philo)
{
	print_action(philo, TAKING_FORK);
	return (NULL);
}

static void	eating(t_philos *philo)
{
	pthread_mutex_lock(philo->fork);
	pthread_mutex_lock(philo->next->fork);
	if (dinner_is_over(philo))
	{
		pthread_mutex_unlock(philo->fork);
		pthread_mutex_unlock(philo->next->fork);
		return ;
	}
	print_action(philo, TAKING_FORK);
	print_action(philo, TAKING_FORK);
	print_action(philo, EATING);
	set_last_meal(philo);
	msleep(philo->data->ms_to_eat);
	pthread_mutex_unlock(philo->fork);
	pthread_mutex_unlock(philo->next->fork);
	set_meals(philo);
}

static void	sleeping(t_philos *philo)
{
	print_action(philo, SLEEPING);
	msleep(philo->data->ms_to_sleep);
}

static void	thinking(t_philos *philo)
{
	print_action(philo, THINKING);
	usleep(500);
}

void	*philosophers_routine(void *ptr)
{
	t_philos	*philo;

	philo = (t_philos *)ptr;
	if (philo->name % 2)
		msleep(10);
	if (philo->data->alone == true)
		return (only_one(philo));
	while (dinner_is_over(philo) == false)
	{
		eating(philo);
		if (count_meals(philo) == philo->data->times_must_eat)
			return (NULL);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
