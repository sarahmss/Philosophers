/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:37:08 by smodesto          #+#    #+#             */
/*   Updated: 2022/03/15 19:25:34 by smodesto         ###   ########.fr       */
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

static int	die_eating(t_philos *p, pthread_mutex_t *r_w, long long int e)
{
	if (p->time->ms_die < p->time->ms_sleep || p->time->ms_die < e)
	{
		delay(p->time->ms_die);
		p->state = DIED;
		run_action(p, r_w);
		check_end(p, p->time->philo_tot);
		return_forks(p);
		return (-1);
	}
	return (0);
}

/*
	printf("---%d, %lld > %lld\n\n", p->philo_num, p->time->last_meal,
	p->time->new_ms_die);
*/
int	eating(long long int ms_eat, t_philos *p, pthread_mutex_t *r_w)
{
	pickup_forks(p);
	if (p->end == true || run_action(p, r_w) == -1)
		return (-1);
	p->time->eaten_times++;
	p->time->last_meal = formated_time(p->time->ms_start);
	p->time->new_ms_die = p->time->last_meal + p->time->ms_die;
	if (die_eating(p, r_w, ms_eat))
		return (-1);
	delay(ms_eat);
	return_forks(p);
	return (0);
}
