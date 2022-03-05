/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:31:28 by smodesto          #+#    #+#             */
/*   Updated: 2022/03/05 16:00:24 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	define_dead(long long int ms_start, t_philos *philosopher,
	long long int ms_die, pthread_mutex_t *res_write)
{
	if ((ms_start - philosopher->time.last_meal) >= ms_die)
	{
		philosopher->state = DIED;
		print_action(DIED, philosopher->philo_num, philosopher->time.ms_start,
			res_write);
		exit (0);
	}
	return (0);
}

void	st_action(t_states action, long long int time_ms, t_philos *philo,
		pthread_mutex_t *rw)
{
	print_action(action, philo->philo_num, philo->time.ms_start, rw);
	usleep(time_ms * 1000);
	if (action == EATING)
	{
		philo->time.eaten_times++;
		philo->time.last_meal = formated_time(philo->time.ms_start);
		if (philo->time.ms_die < philo->time.ms_sleep)
			define_dead(philo->time.ms_start, philo, philo->time.ms_die,
				&philo->res_write);
	}
	if (action == SLEEPING)
		philo->state = THINKING;
}

void	run_action(t_philos *philo, pthread_mutex_t *rw)
{
	if (philo->state == TAKING_FORK)
		print_action(TAKING_FORK, philo->philo_num, philo->time.ms_start, rw);
	if (philo->state == EATING)
		st_action(EATING, philo->time.ms_eat, philo, rw);
	if (philo->state == SLEEPING)
		st_action(SLEEPING, philo->time.ms_sleep, philo, rw);
	if (philo->state == THINKING && philo->time.eaten_times > 0)
		print_action(THINKING, philo->philo_num, philo->time.ms_start, rw);
	if (philo->state == DIED)
		print_action(DIED, philo->philo_num, philo->time.ms_start, rw);
	return ;
}

void	print_action(t_states action, int num_philo, long long int ms_start,
					pthread_mutex_t *res_write)
{
	long long int		time;
	char				msg[100];

	if (action == TAKING_FORK)
		ft_strcpy(msg, "has taken a fork");
	if (action == EATING)
		ft_strcpy(msg, "is eating");
	if (action == SLEEPING)
		ft_strcpy(msg, "is sleeping");
	if (action == THINKING)
		ft_strcpy(msg, "is thinking");
	if (action == DIED)
		ft_strcpy(msg, "died");
	pthread_mutex_lock(res_write);
	time = formated_time(ms_start);
	printf("%-10lld %d %s \n", time, num_philo, msg);
	pthread_mutex_unlock(res_write);
	return ;
}
