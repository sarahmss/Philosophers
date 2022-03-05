/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_error_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:10:28 by smodesto          #+#    #+#             */
/*   Updated: 2022/03/05 13:46:34 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	before_living(t_dining_table *dt)
{
	free_lst(dt->philos);
	pthread_mutex_destroy(&dt->res_write);
	free(dt);
	return ;
}

int	ft_isdigit(int c)
{
	if (48 <= c && c <= 57)
		return (1);
	else
		return (0);
}

int	ft_check_args(char *argv[])
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
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
