/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 19:57:42 by smodesto          #+#    #+#             */
/*   Updated: 2022/03/05 16:00:14 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

/*
	Philosopher takes their right and their left forks to eat, one in each hand
*/
void	pickup_forks(t_philos *philo)
{
	philo->state = TAKING_FORK;
	pthread_mutex_lock(&philo->mutex_lock);
	run_action(philo, &philo->res_write);
	if (philo->next == philo)
	{
		delay(philo->time.ms_die);
		define_dead(philo->time.ms_start, philo, philo->time.ms_die,
			&philo->res_write);
	}
	pthread_mutex_lock(&philo->next->mutex_lock);
	run_action(philo, &philo->res_write);
	philo->state = EATING;
}

/*
	When a philosopher has finished eating, they put their forks back on the
	table and start sleeping.
	printf("--%d. droped forks\n", p->philo_num);
*/
void	return_forks(t_philos *philo)
{
	pthread_mutex_unlock(&philo->mutex_lock);
	pthread_mutex_unlock(&philo->next->mutex_lock);
	philo->state = SLEEPING;
}

void	*philosopher_routine(void *param)
{
	t_philos		*p;

	p = (t_philos *)param;
	if (p->philo_num % 2 == 0)
		delay(60);
	while (!check_if_died(p) && !check_full_stomach(p))
	{
		if (check_able_to_eat(p))
		{
			pickup_forks(p);
			st_action(EATING, p->time.ms_eat, p, &p->res_write);
			return_forks(p);
		}
		define_dead(p->time.ms_start, p, p->time.ms_die, &p->res_write);
		run_action(p, &p->res_write);
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
