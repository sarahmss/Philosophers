/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_philos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 15:44:12 by smodesto          #+#    #+#             */
/*   Updated: 2022/03/06 01:07:10 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

/*
	pthread_join:
		1º paramater: thread wich pthread_join will waits to terminate
		2º paramater: where pthread_join copies the exit status
		of the target thread
*/
int	join_philo_thread(t_philos *philosophers, int philo_num)
{
	t_philos	*philo;
	int			i;

	i = 0;
	philo = philosophers;
	while (i < philo_num)
	{
		if (pthread_join(philo->tid, NULL) != 0)
			return (ft_check_error(EPTHREAD_FUNC, "Fail joining thread", 1));
		philo = philo->next;
		i++;
	}
	return (0);
}

/*
	pthread_create:
		1º paramater: pthread_t == ID returned by pthread_create
		2º paramater: optionall(determine attributes for the new thread)
		3º paramater: The new thread starts execution by invoking start_routine
		4º paramater: arguments utilized by start_routine
*/
int	create_philo_thread(t_dining_table *dt)
{
	int			i;
	t_philos	*philo;

	i = 0;
	philo = dt->philos;
	while (i < dt->philo_num)
	{
		if (pthread_create(&philo->tid, NULL, philosopher_routine, philo) != 0)
			return (ft_check_error(EPTHREAD_FUNC, "Fail creating thread", 1));
		philo = philo->next;
		i++;
	}
	join_philo_thread(dt->philos, dt->philo_num);
	print_exit_status(philo);
	return (0);
}

t_philos	*creating_philo(int num_philo, t_time *time, pthread_mutex_t *rw)
{
	int			i;
	t_philos	*philos;
	t_philos	*tail;

	i = 2;
	philos = create_philosopher(1, time, rw);
	while (i <= num_philo)
	{
		philo_insert_at_foot(i, philos, time, rw);
		i++;
	}
	tail = philos;
	while (tail->next != NULL)
		tail = tail->next;
	tail->next = philos;
	philos->prev = tail;
	return (philos);
}

t_dining_table	*parsing(char *argv[], long long int ms_start)
{
	t_dining_table	*dining_table;

	dining_table = (t_dining_table *)malloc(sizeof(t_dining_table));
	if (!dining_table)
		ft_check_error(EALLOC, "Creating dining_table", -1);
	pthread_mutex_init(&dining_table->res_write, NULL);
	dining_table->time.last_meal = 0;
	dining_table->philo_num = ft_atoi(argv[1]);
	dining_table->time.ms_die = ft_atoi(argv[2]);
	dining_table->time.ms_eat = ft_atoi(argv[3]);
	dining_table->time.ms_sleep = ft_atoi(argv[4]);
	dining_table->time.ms_start = ms_start;
	if (argv[5])
	dining_table->time.must_eat = ft_atoi(argv[5]);
	dining_table->time.eaten_times = 0;
	dining_table->philos = creating_philo(dining_table->philo_num, \
	&dining_table->time, &dining_table->res_write);
	return (dining_table);
}
