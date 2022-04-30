/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:42:22 by smodesto          #+#    #+#             */
/*   Updated: 2022/04/30 15:10:25 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Philosophers.h"

t_philos	*create_philosopher(int index, t_dt *data)
{
	t_philos	*philo;

	philo = (t_philos *)malloc(sizeof(t_philos));
	if (!philo)
	{
		before_living(philo);
		ft_check_error(EFAULT, "Failed to alloc Phillo (A2)", -1);
	}
	philo->name = index;
	philo->meals = 0;
	philo->last_meal = 0;
	philo->tid = 0;
	philo->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	philo->lock_last_meal = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	philo->lock_meals = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo->lock_last_meal, NULL);
	pthread_mutex_init(philo->lock_meals, NULL);
	pthread_mutex_init(philo->fork, NULL);
	philo->data = data;
	philo->prev = NULL;
	philo->next = NULL;
	return (philo);
}

/*
	Insert a new element at the bottom of a doubly linked list
*/
void	philo_insert_at_foot(int index, t_philos *head, t_dt *data)
{
	t_philos	*new_node;
	t_philos	*temp;

	new_node = create_philosopher(index, data);
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

static void	free_philo(t_philos *philo)
{
	pthread_mutex_destroy(philo->fork);
	pthread_mutex_destroy(philo->lock_last_meal);
	pthread_mutex_destroy(philo->lock_meals);
	free(philo->fork);
	free(philo->lock_last_meal);
	free(philo->lock_meals);
	free(philo);
}

/*
	Free the list
*/
void	free_lst(t_philos *head)
{
	t_philos	*current;
	t_philos	*next;
	int			i;

	i = head->data->number_of_philos;
	current = head;
	if (i == 1)
	{
		free_philo(head);
		return ;
	}
	while (i--)
	{
		next = current->next;
		free_philo(current);
		current = next;
	}
}

void	print_action(t_philos *philo, t_states action)
{
	long	current_time;
	char	msg[100];

	if (philo->data->dinner_is_over == true && action < DIED)
		return ;
	pthread_mutex_lock(philo->data->lock_print);
	if (action == TAKING_FORK)
		ft_strcpy(msg, "has taken a fork");
	else if (action == EATING)
		ft_strcpy(msg, "\033[37;1mis eating \033[0m");
	else if (action == SLEEPING)
		ft_strcpy(msg, "is sleeping");
	else if (action == THINKING)
		ft_strcpy(msg, "is thinking");
	else if (action == DIED)
		ft_strcpy(msg, "\033[1;31mdied \033[0m");
	else if (action == END_DEAD)
		printf("\n\n \033[37;1mSome Philosopher died 😵🥣\n\033[0m");
	else if (action == END_FED)
		printf("\n\033[37;1m All philosophers have been fed 🧠🤔🍜\n\033[0m");
	current_time = formated_time(philo->data->ms_init);
	if (action != END_DEAD && action != END_FED)
		printf("%-10ld %d %s \n", current_time, philo->name, msg);
	pthread_mutex_unlock(philo->data->lock_print);
}
