/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 18:56:26 by smodesto          #+#    #+#             */
/*   Updated: 2022/03/06 01:16:03 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include "utils.h"
# include "structures.h"

t_dining_table	*parsing(char *argv[], long long int ms_start);

t_philos		*creating_philo(int num_philo, t_time *time,
					pthread_mutex_t *rw);
int				create_philo_thread(t_dining_table *dt);
int				join_philo_thread(t_philos *philosophers, int philo_num);
void			print_exit_status(t_philos *philos);

void			*philosopher_routine(void *param);
void			pickup_forks(t_philos *philo);
void			return_forks(t_philos *philo);

// states
void			st_action(t_states action, long long int time_ms,
					t_philos *philo, pthread_mutex_t *rw);
int				define_dead(t_philos *philosopher, long long int ms_die,
					pthread_mutex_t *res_write);
void			run_action(t_philos *philo, pthread_mutex_t *rw);
void			print_action(t_states action, int num_philo,
					long long int ms_start, pthread_mutex_t *res_write);
#endif
