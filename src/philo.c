/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:06:15 by valarcon          #+#    #+#             */
/*   Updated: 2022/12/12 13:06:18 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philo_status(t_ph *ph, char *status)
{
	unsigned long	aux;

	ft_act(ph);
	pthread_mutex_lock(&ph->info->endlock);
	aux = ((get_useconds() - ph->info->t_start) / 1000);
	printf("%zu %d %s\n", aux, ph->n, status);
	pthread_mutex_unlock(&ph->info->endlock);
}

void	print_philo_dead(t_ph *ph, char *status)
{
	unsigned long	aux;

	pthread_mutex_lock(&ph->info->endlock);
	aux = ((get_useconds() - ph->info->t_start) / 1000);
	printf("%zu %d %s\n", aux, ph->n, status);
}

static void	ft_start_eat(t_ph	*ph)
{
	if (ft_neat(ph) == 0)
	{
		if ((ph->n) % 2 == 0)
		{
			usleep(1);
			pthread_mutex_lock(ph->fork_r);
			print_philo_status(ph, "has taken a fork");
			pthread_mutex_lock(&ph->fork_l);
			print_philo_status(ph, "has taken a fork");
		}
		else
		{
			pthread_mutex_lock(&ph->fork_l);
			print_philo_status(ph, "has taken a fork");
			pthread_mutex_lock(ph->fork_r);
			print_philo_status(ph, "has taken a fork");
		}
	}
	else
	{
		pthread_mutex_lock(&ph->fork_l);
		print_philo_status(ph, "has taken a fork");
		pthread_mutex_lock(ph->fork_r);
		print_philo_status(ph, "has taken a fork");
	}
}

void	ph_eat(t_ph *ph)
{
	while (1)
	{
		ft_act(ph);
		ft_start_eat(ph);
		pthread_mutex_lock(&ph->info->leat);
		ph->lst_eat = get_useconds();
		pthread_mutex_unlock(&ph->info->leat);
		print_philo_status(ph, "is eating");
		pthread_mutex_lock(&ph->info->neat);
		ph->n_eat++;
		pthread_mutex_unlock(&ph->info->neat);
		ft_usleep((ph->t_eat * 1000));
		pthread_mutex_unlock(&ph->fork_l);
		pthread_mutex_unlock(ph->fork_r);
		ft_act(ph);
		if (ft_neat(ph) >= ph->stop && ph->stop != -1)
			ft_endeat(ph);
		break ;
	}
}

void	*ph_life(void	*arg)
{
	while (1)
	{
		ph_eat((t_ph *)arg);
		print_philo_status((t_ph *)arg, "is sleeping");
		ft_usleep(((t_ph *)arg)->info->t_slp * 1000);
		print_philo_status((t_ph *)arg, "is thinking");
	}
	return (NULL);
}
