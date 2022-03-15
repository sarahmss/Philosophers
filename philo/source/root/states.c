/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:31:28 by smodesto          #+#    #+#             */
/*   Updated: 2022/03/08 20:32:29 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Philosophers.h"

/*
	printf("---%d, %lld > %lld\n\n", tmp->philo_num, tmp->time->last_meal + ms_action, tmp->time->new_ms_die);
int	diedoing(t_philos *p, pthread_mutex_t *r_w, long long int ms_action)
{
	int			tot;
	t_philos	*tmp;

	tmp = p->next;
	tot = p->time->philo_tot - 1;
	while (tot--)
	{
		if (tmp->time->last_meal + ms_action > tmp->time->new_ms_die)
		{
			delay(tmp->time->new_ms_die - formated_time(p->time->ms_start));
			if (tmp->state == EATING)
				return_forks(tmp);
			tmp->state = DIED;
			run_action(tmp, r_w);
			check_end(tmp, tmp->time->philo_tot);
			return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}
*/
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

int	eating(long long int ms_eat, t_philos *p, pthread_mutex_t *r_w)
{
	if (p->end == true || run_action(p, r_w) == -1)
		return (-1);
	p->time->eaten_times++;
	p->time->last_meal = formated_time(p->time->ms_start);
	if (p->time->eaten_times > 1)
		p->time->new_ms_die += formated_time(p->time->ms_start);
	if (die_eating(p, r_w, ms_eat))
		return (-1);
	delay(ms_eat);
	return (0);
}

int	run_action(t_philos *p, pthread_mutex_t *r_w)
{
	int	tot;

	tot = p->time->philo_tot;
	check_full_stomach(p, tot);
	if (p->end == true || (check_if_died(p, tot) && p->state != DIED))
		return (-1);
	if (p->state == TAKING_FORK)
		print_action(TAKING_FORK, p->philo_num, p->time->ms_start, r_w);
	else if (p->state == EATING)
		print_action(EATING, p->philo_num, p->time->ms_start, r_w);
	else if (p->state == SLEEPING)
		print_action(SLEEPING, p->philo_num, p->time->ms_start, r_w);
	else if (p->state == THINKING && p->time->eaten_times > 0)
		print_action(THINKING, p->philo_num, p->time->ms_start, r_w);
	else if (p->state == DIED)
		print_action(DIED, p->philo_num, p->time->ms_start, r_w);
//	if (diedoing(p, r_w, p->time->ms_eat) || diedoing(p, r_w, p->time->ms_die))
//		return (-1);
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
