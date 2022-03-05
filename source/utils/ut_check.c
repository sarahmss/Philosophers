/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 21:48:54 by smodesto          #+#    #+#             */
/*   Updated: 2022/03/05 15:59:56 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

/*
	check if the eaten times is less than the number of each times a
	philosopher must eat
*/
int	check_full_stomach(t_philos *philo)
{
	if (!philo->time.must_eat)
		return (0);
	if (philo->time.eaten_times < philo->time.must_eat)
		return (0);
	return (1);
}

int	check_priority(t_philos *p)
{
	t_philos	*tp;

	tp = p;
	while (tp->next != p)
	{
		if ((p->time.eaten_times > 0 && p->time.last_meal < tp->time.last_meal)
			|| (p->time.eaten_times == 0 && p->philo_num > tp->philo_num))
			return (0);
		tp = tp->next;
	}
	return (1);
}

/*
	If my left and right neighbors aren't eating, then let me
	eat.
*/
int	check_able_to_eat(t_philos *philo)
{
	if (check_priority(philo) && (philo->next->state != TAKING_FORK)
		&& (philo->prev->state != TAKING_FORK) && philo->state == THINKING)
	{
		philo->state = EATING;
		return (1);
	}
	return (0);
}

/*
	check if the status of any philosopher e Died
*/
int	check_if_died(t_philos *philos)
{
	t_philos	*philo_temp;

	philo_temp = philos;
	while (philo_temp->next != philos)
	{
		if (philo_temp->state == DIED)
			return (philo_temp->philo_num);
		philo_temp = philo_temp->next;
	}
	if (philo_temp->state == DIED)
		return (philo_temp->philo_num);
	return (0);
}
