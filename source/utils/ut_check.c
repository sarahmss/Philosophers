/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 21:48:54 by smodesto          #+#    #+#             */
/*   Updated: 2022/02/02 11:22:52 by smodesto         ###   ########.fr       */
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

/*
	If my left and right neighbors aren't eating, then let me
	eat.
*/
int	check_able_to_eat(t_philos *philo)
{
	if ((philo->next->state != EATING) && (philo->prev->state != EATING)
		&& philo->state == THINKING)
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
			return (1);
		philo_temp = philo_temp->next;
	}
	return (0);
}
