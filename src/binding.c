/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 12:39:49 by valarcon          #+#    #+#             */
/*   Updated: 2022/12/12 12:39:51 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

useconds_t	ft_lsteat(t_ph *ph)
{
	useconds_t	res;

	ft_act(ph);
	pthread_mutex_lock(&ph->info->leat);
	res = ph->lst_eat;
	pthread_mutex_unlock(&ph->info->leat);
	return (res);
}

int	ft_neat(t_ph	*ph)
{
	int	res;

	ft_act(ph);
	pthread_mutex_lock(&ph->info->neat);
	res = ph->n_eat;
	pthread_mutex_unlock(&ph->info->neat);
	return (res);
}

void	ft_endeat(t_ph	*ph)
{
	ft_act(ph);
	pthread_mutex_lock(&ph->info->endeat);
	(*ph->info->end_eat)++;
	pthread_mutex_unlock(&ph->info->endeat);
	while (1)
		usleep(33);
}

int	ft_endalleat(t_info	*info)
{
	int	res;

	pthread_mutex_lock(&info->destroy);
	pthread_mutex_unlock(&info->destroy);
	pthread_mutex_lock(&info->endeat);
	res = (*info->end_eat);
	pthread_mutex_unlock(&info->endeat);
	return (res);
}
