/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:44:46 by smodesto          #+#    #+#             */
/*   Updated: 2022/02/01 19:51:42 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef enum e_errcode
{
	EXITSUCESS,
	EUSAGE,
	EALLOC,
	__ERRMAX
}		t_errcode;

typedef enum e_states
{
	THINKING,
	TAKING_FORK,
	EATING,
	SLEEPING,
	DIED,
}				t_states;

typedef struct s_philos
{
	int					philo_num;
	int					interations;
	pthread_t			tid;
	struct s_philos		*next;
	struct s_philos		*prev;
}		t_philos;

typedef struct s_dining_table
{
	int				philo_num;
	int				ms_die;
	int				ms_eat;
	int				ms_sleep;
	int				num_each_must_eat;
	t_philos		*philos;
}		t_dining_table;

#endif
