/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 21:48:54 by smodesto          #+#    #+#             */
/*   Updated: 2022/03/08 20:05:24 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Philosophers.h"

/*
	check if the eaten times is less than the number of each times a
	philosopher must eat
*/
int	check_full_stomach(t_philos *philo, int tot)
{
	t_bool		all_fed;
	t_philos	*temp;

	temp = philo;
	all_fed = true;
	if (!philo->time->must_eat)
		return (0);
	while (tot)
	{
		if (temp->time->eaten_times < temp->time->must_eat)
			all_fed = false;
		temp = temp->next;
		tot--;
	}
	if (all_fed == true)
	{
		check_end(philo, philo->time->philo_tot);
		return (1);
	}
	return (0);
}

int	get_eaten_times(t_philos *p, int tot)
{
	t_philos	*tmp;

	tmp = p;
	while (tot)
	{
		if (tmp->time->eaten_times != p->time->eaten_times)
			return (0);
		tmp = tmp->next;
		tot--;
	}
	return (tmp->time->eaten_times);
}

int	check_priority(t_philos *p, int tot)
{
	t_philos	*tp;
	int			eaten_times;

	eaten_times = get_eaten_times(p, tot);
	tp = p;
	while (tot--)
	{
		if (eaten_times && p->time->last_meal > tp->time->last_meal)
			return (0);
		tp = tp->next;
	}
	return (1);
}

/*
	If my left and right neighbors aren't eating, then let me
	eat.
*/
int	check_able_to_eat(t_philos *p)
{
	if (check_priority(p, p->time->philo_tot) && p->state == THINKING
		&& (p->next->state != TAKING_FORK) && (p->prev->state != EATING)
		&& (p->prev->state != TAKING_FORK) && (p->next->state != EATING))
		return (1);
	return (0);
}

/*
	check if the status of any philosopher e Died
*/
int	check_if_died(t_philos *philos, int tot)
{
	t_philos	*philo_temp;

	philo_temp = philos;
	while (tot)
	{
		if (philo_temp->state == DIED)
			return (philo_temp->philo_num);
		philo_temp = philo_temp->next;
		tot--;
	}
	if (philo_temp->state == DIED)
		return (philo_temp->philo_num);
	return (0);
}
