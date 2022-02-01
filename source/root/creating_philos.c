/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_philos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 15:44:12 by smodesto          #+#    #+#             */
/*   Updated: 2022/02/01 19:52:56 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	*philosopher(void *param)
{
	t_dining_table	*dt;
	t_philos		*philos;

	dt = (t_dining_table *)param;
	philos = dt->philos;
	print_action(EATING, philos->philo_num);
	return (NULL);
}

/*
	pthread_create:
		1º paramater: pthread_t == ID returned by pthread_create
		2º paramater: optionall(determine attributes for the new thread)
		3º paramater: The new thread starts execution by invoking start_routine
		4º paramater: arguments utilized by start_routine
*/
void	create_philo_thread(t_dining_table *dt)
{
	int			i;
	t_philos	*philo;

	i = 0;
	philo = dt->philos;
	while (i < dt->philo_num)
	{
		pthread_create(&philo->tid, NULL, philosopher, dt);
		philo = philo->next;
		i++;
	}
	i = 0;
	philo = dt->philos;
	while (i < dt->philo_num)
	{
		pthread_join(philo->tid, NULL);
		philo = philo->next;
		i++;
	}
}

t_philos	*creating_philo(int num_philo)
{
	int			i;
	t_philos	*philos;
	t_philos	*tail;

	i = 2;
	philos = create_philosopher(1);
	while (i <= num_philo)
	{
		philo_insert_at_foot(i, philos);
		i++;
	}
	tail = philos;
	while (tail->next != NULL)
		tail = tail->next;
	tail->next = philos;
	philos->prev = tail;
	return (philos);
}

t_dining_table	*parsing(char *argv[])
{
	t_dining_table	*dining_table;

	dining_table = (t_dining_table *)malloc(sizeof(t_dining_table));
	if (!dining_table)
		ft_check_error(EALLOC, "Creating dining_table", -1);
	dining_table->philo_num = ft_atoi(argv[1]);
	dining_table->ms_die = ft_atoi(argv[2]);
	dining_table->ms_eat = ft_atoi(argv[3]);
	dining_table->ms_sleep = ft_atoi(argv[4]);
	if (argv[5])
		dining_table->num_each_must_eat = ft_atoi(argv[5]);
	else
		dining_table->num_each_must_eat = 0;
	dining_table->philos = creating_philo(dining_table->philo_num);
	return (dining_table);
}
