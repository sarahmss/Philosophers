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

#include "../../includes/Philosophers.h"

int	define_dead(t_philos *p, pthread_mutex_t *r_w)
{
	int			tot;
	t_philos	*tmp;

	tmp = p;
	tot = p->time->philo_tot;
	while (tot)
	{
		if (tmp->time->last_meal > tmp->time->new_ms_die)
		{
			printf("---%d, %lld, %lld\n", tmp->philo_num, tmp->time->last_meal, tmp->time->new_ms_die);
			tmp->state = DIED;
			print_action(DIED, tmp->philo_num, tmp->time->ms_start, r_w);
			check_end(p, tot);
			return (1);
		}
		tot--;
		tmp = tmp->next;
	}
	return (0);
}

int	sleeping(long long int ms_sleep, t_philos *philo, pthread_mutex_t *rw)
{
	int	tot;

	tot = philo->time->philo_tot;
	if (check_if_died(philo, tot) || check_full_stomach(philo, tot))
		return (-1);
	print_action(philo->state, philo->philo_num, philo->time->ms_start, rw);
	delay(ms_sleep);
	philo->state = THINKING;
	print_action(philo->state, philo->philo_num, philo->time->ms_start, rw);
	return (0);
}

static int	die_while_sleeping(t_philos *p, pthread_mutex_t *rw)
{
	if (p->time->ms_die < p->time->ms_sleep)
	{
		delay(p->time->ms_die);
		p->state = DIED;
		print_action(DIED, p->philo_num, p->time->ms_start, rw);
		check_end(p, p->time->philo_tot);
		return_forks(p);
		return (-1);
	}
	return (0);
}

int	eating(long long int ms_eat, t_philos *philo, pthread_mutex_t *rw)
{
	int	tot;

	tot = philo->time->philo_tot;
	if (check_if_died(philo, tot) || check_full_stomach(philo, tot))
		return (-1);
	print_action(philo->state, philo->philo_num, philo->time->ms_start, rw);
	philo->time->eaten_times++;
	philo->time->last_meal = formated_time(philo->time->ms_start);
	if (philo->time->eaten_times > 1)
		philo->time->new_ms_die += formated_time(philo->time->ms_start);
	if (die_while_sleeping(philo, rw))
		return (-1);
	delay(ms_eat);
	return (0);
}

void	run_action(t_philos *philo, pthread_mutex_t *rw)
{
	if (philo->end == true)
		return ;
	if (philo->state == TAKING_FORK)
		print_action(TAKING_FORK, philo->philo_num, philo->time->ms_start, rw);
	if (philo->state == EATING)
		eating(philo->time->ms_eat, philo, rw);
	if (philo->state == SLEEPING)
		sleeping(philo->time->ms_sleep, philo, rw);
	if (philo->state == THINKING && philo->time->eaten_times > 0)
		print_action(THINKING, philo->philo_num, philo->time->ms_start, rw);
	if (philo->state == DIED)
		print_action(DIED, philo->philo_num, philo->time->ms_start, rw);
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
