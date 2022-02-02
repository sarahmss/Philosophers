/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:31:28 by smodesto          #+#    #+#             */
/*   Updated: 2022/02/02 10:55:19 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	define_dead(suseconds_t ms_start, t_philos *philosopher, suseconds_t ms_die)
{
	if ((ms_start - philosopher->time.last_meal) >= ms_die)
	{
		philosopher->state = DIED;
		return (1);
	}
	return (0);
}

void	st_action(t_states action, int time_ms, t_philos *philo)
{
	print_action(action, philo->philo_num);
	usleep(time_ms);
	if (action == EATING)
	{
		philo->time.eaten_times++;
		philo->time.last_meal = get_current_time();
	}
}

void	run_action(t_philos *philo)
{
	if (philo->state == TAKING_FORK)
		print_action(TAKING_FORK, philo->philo_num);
	if (philo->state == EATING)
		st_action(EATING, philo->time.ms_eat, philo);
	if (philo->state == SLEEPING)
		st_action(SLEEPING, philo->time.ms_sleep, philo);
	if (philo->state == THINKING)
		print_action(THINKING, philo->philo_num);
	if (philo->state == DIED)
		print_action(DIED, philo->philo_num);
	return ;
}

void	print_action(t_states action, int num_philo)
{
	suseconds_t		time;
	char			msg[100];

	time = get_current_time();
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
	printf("%ld %d %s \n", time, num_philo, msg);
	return ;
}
