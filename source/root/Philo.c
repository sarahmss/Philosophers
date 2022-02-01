/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:22:56 by smodesto          #+#    #+#             */
/*   Updated: 2022/02/01 19:53:20 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Philosophers.h"

/*
	the last argument of pthread_join and pthread create are pointer that
	allows communication between threads.
	in pthread_join we store at result the return value of function in myturn
*/

int	main(int argc, char *argv[])
{
	char			msg[55];
	t_dining_table	*dt;

	ft_strcpy(msg, "./philo num_philo ms_die ms_eat ms_sleep num_must_eat");
	if (argc < 5 || argc > 6 || ft_check_args(argv))
		ft_check_error(EUSAGE, msg, -1);
	dt = parsing(argv);
	create_philo_thread(dt);
	before_living(dt);
	return (0);
}
