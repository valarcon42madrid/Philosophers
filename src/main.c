/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:00:28 by valarcon          #+#    #+#             */
/*   Updated: 2022/12/12 13:00:30 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	destroy_mutex_forks(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->n_philo)
	{
		pthread_mutex_destroy(&info->philo[i].fork_l);
		i++;
	}
	pthread_mutex_destroy(&info->endlock);
	pthread_mutex_destroy(&info->endeat);
	pthread_mutex_destroy(&info->leat);
	pthread_mutex_destroy(&info->neat);
	pthread_mutex_destroy(&info->destroy);
	return (0);
}

void	ft_kill_ph(t_info *info, t_ph *ph)
{
	int	i;

	i = 0;
	while (i < info->n_philo)
	{
		pthread_detach(ph[i].thread);
		i++;
	}
	destroy_mutex_forks(info);
	free(info->end_eat);
	free(info);
	free(ph);
}

int	check_ph(t_ph *ph)
{
	useconds_t	aux;

	aux = ft_lsteat(ph);
	if ((get_useconds() - aux) / 1000 > (unsigned int)ph->info->t_die
		&& (ft_neat(ph) < ph->info->stop || ph->info->stop == -1))
	{
		print_philo_dead(ph, "died");
		return (1);
	}
	return (0);
}

void	ft_death(t_ph *ph, t_info	*info)
{
	int	x;
	int	exiter;

	exiter = 0;
	usleep(100);
	while (exiter == 0 && ft_endalleat(info) != info->n_philo)
	{
		usleep(100);
		x = 0;
		while (x != info->n_philo && exiter == 0
			&& ft_endalleat(info) != info->n_philo)
		{
			exiter = check_ph(&ph[x]);
			x++;
		}
	}
	pthread_mutex_lock(&info->destroy);
}

int	main(int argc, char **argv)
{
	t_info	*info;

	if (argc < 5 || argc > 6)
	{
		write(2, "Invalid number of arguments\n", 28);
		return (1);
	}
	if (!ft_check_arg(argc, argv))
		return (1);
	info = (t_info *)ft_sec_malloc(sizeof(t_info));
	if (!info || ft_init_info(info, argc, argv) != 0)
		return (1);
	if (ft_init_philo(info))
		return (1);
	ft_death(info->philo, info);
	ft_kill_ph(info, info->philo);
	return (0);
}
