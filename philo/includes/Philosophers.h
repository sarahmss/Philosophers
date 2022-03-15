/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 18:56:26 by smodesto          #+#    #+#             */
/*   Updated: 2022/03/15 20:17:23 by smodesto         ###   ########.fr       */
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

int				one_philo(t_philos *philo);
void			*philosopher_routine(void *param);
void			pickup_forks(t_philos *philo);
void			return_forks(t_philos *philo);

// states
int				eating(long long int ms_eat, t_philos *philo,
					pthread_mutex_t *rw);
int				sleeping(long long int ms_sleep, t_philos *philo,
					pthread_mutex_t *rw);
int				thinking(t_philos *philo, pthread_mutex_t *r_w);
int				define_dead(t_philos *p, pthread_mutex_t *r_w);
int				run_action(t_philos *p, pthread_mutex_t *rw);
void			print_action(t_states action, int num_philo,
					long long int ms_start, pthread_mutex_t *res_write);
int				diedoing(t_philos *p, pthread_mutex_t *r_w,
					long long int ms_action);
#endif
