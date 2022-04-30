/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:13:22 by morgana           #+#    #+#             */
/*   Updated: 2022/04/29 09:59:41 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Philosophers.h"

int	main(int argc, char *argv[])
{
	t_dt			*data;
	t_philos		*philos;

	data = (t_dt *)malloc(sizeof(t_dt));
	if (!data)
		ft_check_error(EFAULT, "Failed to alloc data (A0)", -1);
	parsing_args(argc, argv, data);
	philos = creating_philosophers(data);
	start_philosophers(philos->data->number_of_philos, philos);
	before_living(philos);
	return (0);
}
