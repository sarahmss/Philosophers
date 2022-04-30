/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:44:54 by morgana           #+#    #+#             */
/*   Updated: 2022/04/30 14:30:51 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Philosophers.h"

void	before_living(t_philos *philo)
{
	t_dt	*data;

	data = philo->data;
	free_lst(philo);
	if (data->lock_print)
		free(data->lock_print);
	if (data->lock_dinner)
		free(data->lock_dinner);
	if (data)
		free(data);
	return ;
}

/*
	ex < 0: ERROR: msg --> exit(err_code)
	ex = 0: msg --> exit(0)
	ex > 0: msg
*/
int	ft_check_error(int err_code, char *err_msg, int exit_code)
{
	if (exit_code < 0)
	{
		printf("ERROR: %s\n", err_msg);
		exit(err_code);
	}
	if (exit_code == 0)
	{
		printf("%s", err_msg);
		exit(0);
	}
	if (exit_code > 0)
		printf("ERROR: %s\ns", err_msg);
	return (err_code);
}
