/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_philos_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:42:22 by smodesto          #+#    #+#             */
/*   Updated: 2022/03/15 17:17:11 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Philosophers.h"

t_time	*cp_time(t_time *src)
{
	t_time	*dest;

	dest = (t_time *)malloc(sizeof(t_time));
	if (!dest)
		ft_check_error(EALLOC, "Creating time structure", -1);
	dest->eaten_times = 0;
	dest->last_meal = src->last_meal;
	dest->ms_die = src->ms_die;
	dest->ms_sleep = src->ms_sleep;
	dest->ms_eat = src->ms_eat;
	dest->ms_start = src->ms_start;
	dest->must_eat = src->must_eat;
	dest->philo_tot = src->philo_tot;
	dest->new_ms_die = src->new_ms_die;
	return (dest);
}

t_philos	*create_philosopher(int index, t_time *time, pthread_mutex_t *rw)
{
	t_philos	*philos;

	philos = (t_philos *)malloc(sizeof(t_philos));
	if (!philos)
		ft_check_error(EALLOC, "Creating philosophers", -1);
	philos->time = cp_time(time);
	philos->res_write = *rw;
	philos->philo_num = index;
	philos->tid = 0;
	philos->state = THINKING;
	pthread_mutex_init(&philos->mutex_lock, NULL);
	philos->prev = NULL;
	philos->next = NULL;
	philos->end = false;
	return (philos);
}

/*
Insert a new element at the bottom of a doubly linked list
*/
void	philo_insert_at_foot(int philo_num, t_philos *head, t_time *time,
		pthread_mutex_t *rw)
{
	t_philos	*new_node;
	t_philos	*temp;

	new_node = create_philosopher(philo_num, time, rw);
	temp = head;
	if (temp->next == NULL)
	{
		head->next = new_node;
		new_node->prev = head;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
		new_node->prev = temp;
	}
}

/*
	Delete a philosopher del in the list
*/
void	philo_del(t_philos **head, t_philos *del)
{
	if (*head == NULL || del == NULL)
		return ;
	if (*head == del)
		*head = del->next;
	if (del->next != NULL)
		del->next->prev = del->prev;
	if (del->prev != NULL)
		del->prev->next = del->next;
	pthread_mutex_destroy(&del->mutex_lock);
	free(del->time);
	free(del);
}

/*
	Free the list
*/
void	free_lst(t_philos *head)
{
	t_philos	*current;
	t_philos	*next;
	int			i;

	i = head->time->philo_tot;
	current = head;
	if (i == 1)
	{
		pthread_mutex_destroy(&current->mutex_lock);
		free(current->time);
		free (current);
		return ;
	}
	while (i--)
	{
		next = current->next;
		pthread_mutex_destroy(&current->mutex_lock);
		free(current->time);
		free (current);
		current = next;
	}
}
