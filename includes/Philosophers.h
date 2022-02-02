/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 18:56:26 by smodesto          #+#    #+#             */
/*   Updated: 2022/02/02 10:56:27 by smodesto         ###   ########.fr       */
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

t_dining_table	*parsing(char *argv[], suseconds_t ms_start);

void			print_action(t_states action, int num_philo);
void			st_action(t_states action, int time_ms, t_philos *philo);
long long int	get_current_time(void);
long long int	get_passed_time(long long int ms_start);

t_philos		*creating_philo(int num_philo, t_time *time);
void			create_philo_thread(t_dining_table *dt);

void			pickup_forks(t_philos *philo);
void			return_forks(t_philos *philo);
int				define_dead(suseconds_t ms_start, t_philos *philosopher, \
				suseconds_t ms_die);
void			run_action(t_philos *philo);

#endif
