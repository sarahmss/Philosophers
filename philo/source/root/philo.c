/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:38:48 by smodesto          #+#    #+#             */
/*   Updated: 2022/04/30 15:33:12 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Philosophers.h"

//	increase the number of meals
void	set_meals(t_philos *philo)
{
	pthread_mutex_lock(philo->lock_meals);
	philo->meals++;
	pthread_mutex_unlock(philo->lock_meals);
}

//	determines meal time
void	set_last_meal(t_philos *philo)
{
	pthread_mutex_lock(philo->lock_last_meal);
	philo->last_meal = formated_time(philo->data->ms_init);
	pthread_mutex_unlock(philo->lock_last_meal);
}

// check if dinner is over
t_bool	dinner_is_over(t_philos *philo)
{
	t_bool	dinner_is_over;

	dinner_is_over = false;
	pthread_mutex_lock(philo->data->lock_dinner);
	if (philo->data->dinner_is_over == true)
		dinner_is_over = philo->data->dinner_is_over;
	pthread_mutex_unlock(philo->data->lock_dinner);
	return (dinner_is_over);
}

int	start_philosophers(int n, t_philos *philos)
{
	int			i;
	t_philos	*temp;
	pthread_t	monitor_thread;

	i = -1;
	philos->data->ms_init = get_current_time();
	temp = philos;
	while (++i < n)
	{
		pthread_create(&temp->tid, NULL, &philosophers_routine, temp);
		temp = temp->next;
	}
	pthread_create(&monitor_thread, NULL, &check_end, philos);
	i = -1;
	while (++i < n)
	{
		pthread_join(temp->tid, NULL);
		temp = temp->next;
	}
	pthread_join(monitor_thread, NULL);
	return (0);
}

t_philos	*creating_philosophers(t_dt *data)
{
	int			i;
	t_philos	*philos;
	t_philos	*tail;

	i = 2;
	philos = create_philosopher(1, data);
	while (i <= data->number_of_philos)
	{
		philo_insert_at_foot(i, philos, data);
		i++;
	}
	tail = philos;
	while (tail->next != NULL)
		tail = tail->next;
	tail->next = philos;
	philos->prev = tail;
	return (philos);
}
