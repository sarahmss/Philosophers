/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:44:46 by smodesto          #+#    #+#             */
/*   Updated: 2022/04/30 15:10:26 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef enum e_bool
{
	false,
	true
}					t_bool;

typedef enum e_states
{
	TAKING_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	END_DEAD,
	END_FED
}				t_states;

typedef struct s_dt
{
	t_bool			alone;
	t_bool			dinner_is_over;
	int				number_of_philos;
	int				ms_to_die;
	int				ms_to_eat;
	int				ms_to_sleep;
	int				times_must_eat;
	long			ms_init;
	pthread_mutex_t	*lock_print;
	pthread_mutex_t	*lock_dinner;
}	t_dt;

typedef struct s_philos
{
	int					name;
	int					meals;
	long				last_meal;
	pthread_t			tid;
	pthread_mutex_t		*fork;
	pthread_mutex_t		*lock_last_meal;
	pthread_mutex_t		*lock_meals;
	t_dt				*data;
	struct s_philos		*next;
	struct s_philos		*prev;
}	t_philos;

#endif
