/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:44:46 by smodesto          #+#    #+#             */
/*   Updated: 2022/03/05 13:46:42 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef enum e_bool
{
	false,
	true
}					t_bool;

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

typedef struct s_time
{
	long long int	ms_die;
	long long int	ms_eat;
	long long int	ms_sleep;
	long long int	ms_start;
	long long int	last_meal;
	int				eaten_times;
	int				must_eat;
}		t_time;

/*
	mutex is a MUTual EXclusion device
		A mutex has two possible states: unlocked (not owned by
		any thread), and locked (owned by one thread). A mutex can
		never  be owned by two different threads simultaneously. A
		thread attempting to lock a mutex that is  already  locked
		by  another thread is suspended until the owning thread
		unlocks the mutex first.
	there are as many forks as philosophers.
	the mutex lock of philosopher 1 indicates the fork in his left side
*/
typedef struct s_philos
{
	int					philo_num;
	pthread_t			tid;
	t_states			state;
	pthread_mutex_t		mutex_lock;
	pthread_mutex_t		res_write;
	t_time				time;
	struct s_philos		*next;
	struct s_philos		*prev;
}		t_philos;

typedef struct s_dining_table
{
	int					philo_num;
	int					num_each_must_eat;
	int					eaten_times;
	pthread_mutex_t		res_write;
	t_time				time;
	t_philos			*philos;
}		t_dining_table;

#endif
