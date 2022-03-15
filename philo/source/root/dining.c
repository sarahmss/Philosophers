/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 19:57:42 by smodesto          #+#    #+#             */
/*   Updated: 2022/03/15 20:18:05 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Philosophers.h"

int	define_dead(t_philos *p, pthread_mutex_t *r_w)
{
	int			tot;
	t_philos	*tmp;

	if (p->end == true)
		return (1);
	tmp = p;
	tot = p->time->philo_tot;
	while (tot)
	{
		if (tmp->time->last_meal > tmp->time->new_ms_die)
		{
			tmp->state = DIED;
			run_action(tmp, r_w);
			check_end(p, tot);
			return (1);
		}
		tot--;
		tmp = tmp->next;
	}
	return (0);
}

void	*philosopher_routine(void *param)
{
	t_philos		*p;
	int				tot;

	p = (t_philos *)param;
	tot = p->time->philo_tot;
	if (one_philo(p))
		return (NULL);
	while (!check_if_died(p, tot) || !check_full_stomach(p, tot))
	{
		if (check_able_to_eat(p))
		{
			if ((eating(p->time->ms_eat, p, &p->res_write) == -1)
				|| (sleeping(p->time->ms_sleep, p, &p->res_write) == -1)
				|| (thinking(p, &p->res_write) == -1))
				return (NULL);
		}
		define_dead(p, &p->res_write);
		if (p->end == true)
			return (NULL);
	}
	return (NULL);
}
