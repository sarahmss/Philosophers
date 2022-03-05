/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 15:52:10 by smodesto          #+#    #+#             */
/*   Updated: 2022/03/05 16:04:08 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "structures.h"

int				ft_check_args(char *argv[]);
int				ft_check_error(int err_code, char *err_msg, int exit_code);
void			before_living(t_dining_table *dt);

int				ft_strlen(const char *str);
int				ft_atoi(const char *str);
char			*ft_strcpy(char *destination, const char *source);
int				ft_strlen(const char *str);

t_philos		*create_philosopher(int index, t_time *time,
					pthread_mutex_t *rw);
void			philo_insert_at_foot(int philo_num, t_philos *head,
					t_time*time, pthread_mutex_t *rw);
void			philo_del(t_philos **head, t_philos *del);
void			free_lst(t_philos *head);
t_philos		*tk_insert_at_head(int index, t_philos *head, t_time *time,
					pthread_mutex_t *rw);
int				check_able_to_eat(t_philos *philo);
int				check_if_died(t_philos *philos);
int				check_full_stomach(t_philos *philo);
int				check_priority(t_philos *p);

long long int	get_current_time(void);
long long int	formated_time(long long int ms_start);
void			delay(long long int delay_time);
#endif
