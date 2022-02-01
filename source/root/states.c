/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:31:28 by smodesto          #+#    #+#             */
/*   Updated: 2022/02/01 18:32:41 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	st_thinking(int ms_eating)
{
	sleep(ms_eating);
}

void	st_eating(int ms_eating)
{
	sleep(ms_eating);
}

void	st_sleeping(int ms_sleeping)
{
	sleep(ms_sleeping);
}

void	print_action(t_states action, int num_philo)
{
	struct timeval	current_time;
	suseconds_t		time;
	char			msg[100];

	gettimeofday(&current_time, NULL);
	time = current_time.tv_usec;
	if (action == TAKING_FORK)
		ft_strcpy(msg, "has taken a fork");
	if (action == EATING)
		ft_strcpy(msg, "is eating");
	if (action == SLEEPING)
		ft_strcpy(msg, "is sleeping");
	if (action == THINKING)
		ft_strcpy(msg, "is thinking");
	if (action == DIED)
		ft_strcpy(msg, "died");
	printf("%ld %d %s \n", time, num_philo, msg);
	return ;
}
