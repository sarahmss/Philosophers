/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 15:52:10 by smodesto          #+#    #+#             */
/*   Updated: 2022/04/28 16:29:55 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "structures.h"

//	Error manager
int			ft_check_error(int err_code, char *err_msg, int exit_code);
void		before_living(t_philos *philo);

//	Libft
int			ft_isdigit(int c);
long		ft_atol(const char *nptr);
int			ft_strlen(const char *str);
char		*ft_strcpy(char *destination, const char *source);
int			ft_atoi(const char *str);

//	Philos list
t_philos	*create_philosopher(int index, t_dt *data);
void		philo_insert_at_foot(int index, t_philos *head, t_dt *data);
void		philo_del(t_philos **head, t_philos *del);
void		free_lst(t_philos *head);

//time
long		get_current_time(void);
void		delay(int delay_time);
long		formated_time(long first_time);
void		msleep(int time_in_ms);

#endif
