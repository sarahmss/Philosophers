/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_philos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 15:44:12 by smodesto          #+#    #+#             */
/*   Updated: 2022/02/02 10:57:46 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

long long int	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

long long int	get_passed_time(long long int ms_start)
{
	return ((get_current_time() - ms_start));
}

t_philos	*creating_philo(int num_philo, t_time *time)
{
	int			i;
	t_philos	*philos;
	t_philos	*tail;

	i = 2;
	philos = create_philosopher(1, time);
	while (i <= num_philo)
	{
		philo_insert_at_foot(i, philos, time);
		i++;
	}
	tail = philos;
	while (tail->next != NULL)
		tail = tail->next;
	tail->next = philos;
	philos->prev = tail;
	return (philos);
}

t_dining_table	*parsing(char *argv[], suseconds_t ms_start)
{
	t_dining_table	*dining_table;

	dining_table = (t_dining_table *)malloc(sizeof(t_dining_table));
	if (!dining_table)
		ft_check_error(EALLOC, "Creating dining_table", -1);
	dining_table->philo_num = ft_atoi(argv[1]);
	dining_table->time.ms_die = (suseconds_t)ft_atoi(argv[2]);
	dining_table->time.ms_eat = (suseconds_t)ft_atoi(argv[3]);
	dining_table->time.ms_sleep = (suseconds_t)ft_atoi(argv[4]);
	dining_table->time.ms_start = ms_start;
	if (argv[5])
		dining_table->num_each_must_eat = ft_atoi(argv[5]);
	else
		dining_table->num_each_must_eat = 0;
	dining_table->time.must_eat = dining_table->num_each_must_eat;
	dining_table->eaten_times = 0;
	dining_table->time.eaten_times = 0;
	dining_table->philos = creating_philo(dining_table->philo_num, \
	&dining_table->time);
	return (dining_table);
}
