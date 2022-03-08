/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:31:28 by smodesto          #+#    #+#             */
/*   Updated: 2022/03/06 01:50:17 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	define_dead(t_philos *philosopher, long long int ms_die,
	pthread_mutex_t *res_write)
{
	if (philosopher->time.last_meal >= ms_die)
	{
		philosopher->state = DIED;
		print_action(DIED, philosopher->philo_num, philosopher->time.ms_start,
			res_write);
		philosopher->end = true;
		return (1);
	}
	return (0);
}

int	sleeping(long long int time_ms, t_philos *philo, pthread_mutex_t *rw)
{
	if (check_if_died(philo) || check_full_stomach(philo))
		return (-1);
	print_action(philo->state, philo->philo_num, philo->time.ms_start, rw);
	delay(time_ms);
	philo->state = THINKING;
	print_action(philo->state, philo->philo_num, philo->time.ms_start, rw);
	return (0);
}

int	eating(long long int time_ms, t_philos *philo, pthread_mutex_t *rw)
{
	if (check_if_died(philo) || check_full_stomach(philo))
		return (-1);
	print_action(philo->state, philo->philo_num, philo->time.ms_start, rw);
	if (philo->time.ms_die < philo->time.ms_sleep)
	{
		delay(philo->time.ms_die);
		philo->state = DIED;
		print_action(DIED, philo->philo_num, philo->time.ms_start, rw);
		philo->end = true;
		return_forks(philo);
		return (-1);
	}
	delay(time_ms);
	philo->time.eaten_times++;
	philo->time.last_meal = formated_time(philo->time.ms_start);
	return (0);
}

void	run_action(t_philos *philo, pthread_mutex_t *rw)
{
	if (philo->end == true)
		return ;
	if (philo->state == TAKING_FORK)
		print_action(TAKING_FORK, philo->philo_num, philo->time.ms_start, rw);
	if (philo->state == EATING)
		eating(philo->time.ms_eat, philo, rw);
	if (philo->state == SLEEPING)
		sleeping(philo->time.ms_sleep, philo, rw);
	if (philo->state == THINKING && philo->time.eaten_times > 0)
		print_action(THINKING, philo->philo_num, philo->time.ms_start, rw);
	if (philo->state == DIED)
		print_action(DIED, philo->philo_num, philo->time.ms_start, rw);
	return ;
}

void	print_action(t_states action, int num_philo, long long int ms_start,
				pthread_mutex_t *res_write)
{
	long long int	time;
	char			msg[100];

	if (action == TAKING_FORK)
		ft_strcpy(msg, "has taken a fork");
	if (action == EATING)
		ft_strcpy(msg, "\033[37;1mis eating \033[0m");
	if (action == SLEEPING)
		ft_strcpy(msg, "is sleeping");
	if (action == THINKING)
		ft_strcpy(msg, "is thinking");
	if (action == DIED)
		ft_strcpy(msg, "\033[1;31mdied \033[0m");
	pthread_mutex_lock(res_write);
	time = formated_time(ms_start);
	printf("%-10lld %d %s \n", time, num_philo, msg);
	pthread_mutex_unlock(res_write);
}
