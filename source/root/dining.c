/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 19:57:42 by smodesto          #+#    #+#             */
/*   Updated: 2022/03/09 01:52:35 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Philosophers.h"

int	define_dead(t_philos *p, pthread_mutex_t *r_w)
{
	int			tot;
	t_philos	*tmp;

	if (p->end == true)
		return (1);
	tmp = p;
	tot = p->time->philo_tot;
	while (tot)
	{
		if (tmp->time->last_meal > tmp->time->new_ms_die)
		{
			tmp->state = DIED;
			run_action(tmp, r_w);
			check_end(p, tot);
			return (1);
		}
		tot--;
		tmp = tmp->next;
	}
	return (0);
}

int	sleeping(long long int ms_sleep, t_philos *philo, pthread_mutex_t *r_w)
{
	int	tot;

	tot = philo->time->philo_tot;
	if (check_if_died(philo, tot) || check_full_stomach(philo, tot))
		return (-1);
	if (run_action(philo, r_w) == -1)
		return (-1);
	delay(ms_sleep);
	philo->state = THINKING;
	if (run_action(philo, r_w) == -1)
		return (-1);
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
	int				tot;

	p = (t_philos *)param;
	tot = p->time->philo_tot;
	if (one_philo(p))
		return (NULL);
	while (1)
	{
		if (check_if_died(p, tot) || check_full_stomach(p, tot))
			return (NULL);
		if (check_able_to_eat(p))
		{
			pickup_forks(p);
			if (eating(p->time->ms_eat, p, &p->res_write) == -1)
				return (NULL);
			return_forks(p);
			if (sleeping(p->time->ms_sleep, p, &p->res_write) == -1)
				return (NULL);
		}
		define_dead(p, &p->res_write);
		if (p->end == true)
			return (NULL);
	}
	return (NULL);
}
