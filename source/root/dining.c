/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 19:57:42 by smodesto          #+#    #+#             */
/*   Updated: 2022/02/02 11:22:41 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

/*
	Philosopher takes their right and their left forks to eat, one in each hand
*/
void	pickup_forks(t_philos *philo)
{
	if (check_able_to_eat(philo))
	{
		pthread_mutex_lock(&philo->mutex_lock);
		pthread_mutex_lock(&philo->next->mutex_lock);
	}
	philo->state = EATING;
}

/*
	When a philosopher has finished eating, they put their forks back on the
	table and start sleeping.
*/
void	return_forks(t_philos *philo)
{
	pthread_mutex_unlock(&philo->mutex_lock);
	pthread_mutex_unlock(&philo->next->mutex_lock);
	philo->state = SLEEPING;
}

void	*philosopher_routine(void *param)
{
	t_philos		*philo;

	philo = (t_philos *)param;
	while (!check_if_died(philo) && !check_full_stomach(philo))
	{
		print_action(THINKING, philo->philo_num);
		if (check_able_to_eat(philo))
		{
			pickup_forks(philo);
			st_action(EATING, philo->time.ms_eat, philo);
			return_forks(philo);
		}
		define_dead(philo->time.ms_start, philo, philo->time.ms_die);
		run_action(philo);
	}
	return (NULL);
}

/*
	pthread_create:
		1º paramater: pthread_t == ID returned by pthread_create
		2º paramater: optionall(determine attributes for the new thread)
		3º paramater: The new thread starts execution by invoking start_routine
		4º paramater: arguments utilized by start_routine
	pthread_join:
		1º paramater: thread wich pthread_join will waits to terminate
		2º paramater: where pthread_join copies the exit status
		of the target thread
*/
void	create_philo_thread(t_dining_table *dt)
{
	int			i;
	t_philos	*philo;

	i = 0;
	philo = dt->philos;
	while (i < dt->philo_num)
	{
		pthread_create(&philo->tid, NULL, philosopher_routine, philo);
		philo = philo->next;
		i++;
	}
	i = 0;
	philo = dt->philos;
	while (i < dt->philo_num)
	{
		pthread_join(philo->tid, NULL);
		philo = philo->next;
		i++;
	}
}
