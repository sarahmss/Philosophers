/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 19:57:42 by smodesto          #+#    #+#             */
/*   Updated: 2022/03/06 01:16:57 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	one_philo(t_philos *philo)
{
	if (philo->next == philo)
	{
		philo->state = TAKING_FORK;
		run_action(philo, &philo->res_write);
		delay(philo->time.ms_die);
		philo->state = DIED;
		print_action(DIED, philo->philo_num, philo->time.ms_start,
			&philo->res_write);
		return (1);
	}
	return (0);
}

/*
	Philosopher takes their right and their left forks to eat, one in each hand
*/
void	pickup_forks(t_philos *philo)
{
	philo->state = TAKING_FORK;
	pthread_mutex_lock(&philo->mutex_lock);
	run_action(philo, &philo->res_write);
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
	if (one_philo(p))
		return (NULL);
	while (1)
	{
		if (check_if_died(p) || check_full_stomach(p))
			return (NULL);
		if (check_able_to_eat(p))
		{
			pickup_forks(p);
			st_action(EATING, p->time.ms_eat, p, &p->res_write);
			return_forks(p);
			st_action(SLEEPING, p->time.ms_sleep, p, &p->res_write);
		}
		define_dead(p, p->time.ms_die, &p->res_write);
		run_action(p, &p->res_write);
	}
	return (NULL);
}
