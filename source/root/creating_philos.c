/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_philos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 15:44:12 by smodesto          #+#    #+#             */
/*   Updated: 2022/03/05 15:37:02 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

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
	dining_table->philo_num = ft_atoi(argv[1]);
	dining_table->time.ms_die = ft_atoi(argv[2]);
	dining_table->time.ms_eat = ft_atoi(argv[3]);
	dining_table->time.ms_sleep = ft_atoi(argv[4]);
	dining_table->time.ms_start = ms_start;
	if (argv[5])
		dining_table->num_each_must_eat = ft_atoi(argv[5]);
	else
		dining_table->num_each_must_eat = 0;
	dining_table->time.must_eat = dining_table->num_each_must_eat;
	dining_table->eaten_times = 0;
	dining_table->time.eaten_times = 0;
	dining_table->philos = creating_philo(dining_table->philo_num, \
	&dining_table->time, &dining_table->res_write);
	return (dining_table);
}
