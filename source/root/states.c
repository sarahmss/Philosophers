/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:31:28 by smodesto          #+#    #+#             */
/*   Updated: 2022/03/08 19:20:45 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Philosophers.h"

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

static int	die_while_eating(t_philos *p, pthread_mutex_t *r_w, long long int e)
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

int	eating(long long int ms_eat, t_philos *philo, pthread_mutex_t *r_w)
{
	int	tot;

	tot = philo->time->philo_tot;
	if (check_if_died(philo, tot) || check_full_stomach(philo, tot))
		return (-1);
	if (run_action(philo, r_w) == -1)
		return (-1);
	philo->time->eaten_times++;
	philo->time->last_meal = formated_time(philo->time->ms_start);
	if (philo->time->eaten_times > 1)
		philo->time->new_ms_die += formated_time(philo->time->ms_start);
	if (die_while_eating(philo, r_w, philo->time->ms_eat))
		return (-1);
	delay(ms_eat);
	return (0);
}

int	run_action(t_philos *philo, pthread_mutex_t *r_w)
{
	check_if_died(philo, philo->time->philo_tot);
	check_full_stomach(philo, philo->time->philo_tot);
	if (philo->end == true)
		return (-1);
	if (philo->state == TAKING_FORK)
		print_action(TAKING_FORK, philo->philo_num, philo->time->ms_start, r_w);
	if (philo->state == EATING)
		print_action(EATING, philo->philo_num, philo->time->ms_start, r_w);
	if (philo->state == SLEEPING)
		print_action(SLEEPING, philo->philo_num, philo->time->ms_start, r_w);
	if (philo->state == THINKING && philo->time->eaten_times > 0)
		print_action(THINKING, philo->philo_num, philo->time->ms_start, r_w);
	if (philo->state == DIED)
		print_action(DIED, philo->philo_num, philo->time->ms_start, r_w);
	return (0);
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
