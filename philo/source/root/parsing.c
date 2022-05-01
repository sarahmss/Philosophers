/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:36:54 by morgana           #+#    #+#             */
/*   Updated: 2022/05/01 12:27:16 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Philosophers.h"

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
			if (!ft_isdigit(argv[i][j]) || ft_atol(argv[i]) > 2147483647
				|| ft_atol(argv[i]) == 0)
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

void	parsing_args(int argc, char *argv[], t_dt *dt)
{
	char	m[60];

	ft_strcpy(m, "Invalid Arguments[./philo n_ph t_die t_eat t_sleep n_meal]");
	if (argc < 5 || argc > 6 || ft_check_args(argv))
		ft_check_error(EXIT_FAILURE, m, -1);
	dt->number_of_philos = ft_atoi(argv[1]);
	dt->ms_to_die = ft_atoi(argv[2]);
	dt->ms_to_eat = ft_atoi(argv[3]);
	dt->ms_to_sleep = ft_atoi(argv[4]);
	dt->times_must_eat = -1;
	dt->alone = false;
	if (argc == 6)
		dt->times_must_eat = ft_atoi(argv[5]);
	if (dt->number_of_philos == 1)
		dt->alone = true;
	dt->dinner_is_over = false;
	dt->ms_init = 0;
	dt->lock_print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
	dt->lock_dinner = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
	if (dt->lock_print == NULL || dt->lock_dinner == NULL)
		ft_check_error(EFAULT, "Failed to alloc mutex (A1)", -1);
	pthread_mutex_init(dt->lock_print, NULL);
	pthread_mutex_init(dt->lock_dinner, NULL);
}
