/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 18:56:26 by smodesto          #+#    #+#             */
/*   Updated: 2022/04/30 15:33:13 by smodesto         ###   ########.fr       */
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
# include <errno.h>

//	Parsing
void		parsing_args(int argc, char *argv[], t_dt *dt);

//	Philo
t_philos	*creating_philosophers(t_dt *data);
int			start_philosophers(int n, t_philos *philos);
void		set_last_meal(t_philos *philo);
void		set_meals(t_philos *philo);
t_bool		dinner_is_over(t_philos *philo);

void		print_action(t_philos *philo, t_states action);

//	supervisor
void		*check_end(void *ptr);
int			get_last_meal(t_philos *philo);
int			get_meals(t_philos *philo);

//	dinner
void		*philosophers_routine(void *ptr);

#endif
