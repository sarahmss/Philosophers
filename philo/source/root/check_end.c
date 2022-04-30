/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dead.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:05:55 by smodesto          #+#    #+#             */
/*   Updated: 2022/04/30 15:33:09 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Philosophers.h"

void	finish_dinner(t_philos *philo)
{
	pthread_mutex_lock(philo->data->lock_dinner);
	philo->data->dinner_is_over = true;
	pthread_mutex_unlock(philo->data->lock_dinner);
}

int	get_last_meal(t_philos *philo)
{
	long	last_meal;

	pthread_mutex_lock(philo->lock_last_meal);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(philo->lock_last_meal);
	return (last_meal);
}

int	get_meals(t_philos *philo)
{
	int	meals;

	pthread_mutex_lock(philo->lock_meals);
	meals = philo->meals;
	pthread_mutex_unlock(philo->lock_meals);
	return (meals);
}

static t_bool	philos_fed(t_philos *philos)
{
	int			i;
	int			philos_fed;
	t_philos	*temp;

	temp = philos;
	philos_fed = 0;
	i = 0;
	while (philos->data->number_of_philos > i++)
	{
		if (get_meals(temp) == temp->data->times_must_eat)
			philos_fed++;
		temp = temp->next;
	}
	if (philos_fed == philos->data->number_of_philos)
	{
		print_action(philos, END_FED);
		return (true);
	}
	return (false);
}

void	*check_end(void *ptr)
{
	int			i;
	long		current_time;
	t_philos	*philos;
	t_philos	*tp;

	philos = (t_philos *)ptr;
	tp = philos;
	while (philos_fed(philos) == false)
	{
		i = 0;
		while (philos->data->number_of_philos > i++)
		{
			current_time = formated_time(philos->data->ms_init);
			if (tp->data->ms_to_die < (current_time - get_last_meal(tp)))
			{
				finish_dinner(tp);
				print_action(tp, DIED);
				print_action(tp, END_DEAD);
				return (NULL);
			}
			tp = tp->next;
		}
		msleep(1);
	}
	return (NULL);
}
