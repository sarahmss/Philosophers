/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:22:56 by smodesto          #+#    #+#             */
/*   Updated: 2022/01/24 16:11:52 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Philosophers.h"

void	*myturn(void *arg)
{
	int *iptr = (int *)arg;
	for (int i = 0; i < 8; i++)
	{
		sleep(1);
		printf("My turn [i:%d] [iptr: %d] \n", i, *iptr);
		(*iptr)++;
	}
	return (NULL);
}

void	*yourturn(void *arg)
{
	(void)arg;
	for (int i = 0; i < 3; i++)
	{
		sleep(1);
		printf("Your turn %d \n", i);
	}
	return (NULL);
}

/*
	the last argument of pthread_join and pthread create are pointer that allows communication between threads.
	in pthread_join we store at result the return value of function in myturn
*/

int main()
{
	pthread_t	new_thread;
	int			v = 5;
	int			*result;

	pthread_create(&new_thread, NULL, myturn, &v);
	yourturn(NULL);
	pthread_join(new_thread, result);
	printf("thread is done %d \n", v);
	return (0);
}
