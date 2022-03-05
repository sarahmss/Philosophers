/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_philos_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:42:22 by smodesto          #+#    #+#             */
/*   Updated: 2022/03/05 13:53:50 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

t_philos	*create_philosopher(int index, t_time *time, pthread_mutex_t *rw)
{
	t_philos	*philos;

	philos = (t_philos *)malloc(sizeof(t_philos));
	if (!philos)
		ft_check_error(EALLOC, "Creating philosophers", -1);
	philos->res_write = *rw;
	philos->philo_num = index;
	philos->time.eaten_times = 0;
	philos->time.last_meal = time->last_meal;
	philos->time.ms_die = time->ms_die;
	philos->time.ms_sleep = time->ms_sleep;
	philos->time.ms_eat = time->ms_eat;
	philos->time.ms_start = time->ms_start;
	philos->time.must_eat = time->must_eat;
	philos->tid = 0;
	philos->state = THINKING;
	pthread_mutex_init(&philos->mutex_lock, NULL);
	philos->prev = NULL;
	philos->next = NULL;
	return (philos);
}

/*
Insert a new element at the top of a doubly linked list
*/
t_philos	*tk_insert_at_head(int index, t_philos *head, t_time *time,
			pthread_mutex_t *rw)
{
	t_philos	*new_philo;

	new_philo = create_philosopher(index, time, rw);
	if (head == NULL)
		head = new_philo;
	else
	{
		head->prev = new_philo;
		new_philo->next = head;
		head = new_philo;
	}
	return (new_philo);
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
	free(del);
}

/*
	Free the list
*/
void	free_lst(t_philos *head)
{
	t_philos	*current;
	t_philos	*next;

	current = head;
	while (current->next != head)
	{
		next = current->next;
		pthread_mutex_destroy(&current->mutex_lock);
		free (current);
		current = next;
	}
}
