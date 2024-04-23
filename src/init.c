/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 12:44:39 by valarcon          #+#    #+#             */
/*   Updated: 2022/12/12 12:56:33 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_var_init(t_info *info, char **argv, int argc)
{
	if (argc == 6)
	{
		info->stop = ft_atoi(argv[5]);
		if (info->stop < 1)
		{
			free(info);
			return (1);
		}
	}
	else
		info->stop = -1;
	info->n_philo = ft_atoi(argv[1]);
	info->t_die = ft_atoi(argv[2]);
	info->t_eat = ft_atoi(argv[3]);
	info->t_slp = ft_atoi(argv[4]);
	info->end_eat = ft_sec_malloc(sizeof(int));
	return (0);
}

int	ft_init_info(t_info *info, int argc, char **argv)
{
	if (!info)
		return (1);
	if (ft_var_init(info, argv, argc))
		return (1);
	if (!info->end_eat)
	{
		free(info);
		return (1);
	}
	else
		*info->end_eat = 0;
	pthread_mutex_init(&info->endlock, NULL);
	pthread_mutex_init(&info->endeat, NULL);
	pthread_mutex_init(&info->leat, NULL);
	pthread_mutex_init(&info->neat, NULL);
	pthread_mutex_init(&info->destroy, NULL);
	return (0);
}

static int	ft_create_pth(t_info *info, int x)
{
	info->philo[x].lst_eat = info->t_start;
	if (pthread_create(&info->philo[x].thread, NULL, \
		&ph_life, &(info->philo[x])) != 0)
	{
		write(2, "Error creating pthread\n", 23);
		while (--x != -1)
		{
			pthread_mutex_destroy(&info->philo[x].fork_l);
			pthread_detach(info->philo[x].thread);
		}
		free(info->philo);
		ft_fullfree(info);
		return (1);
	}
	return (0);
}

static int	ft_creator(t_info	*info)
{
	int	x;

	x = 0;
	info->t_start = get_useconds();
	while (x < info->n_philo)
	{
		if (ft_create_pth(info, x))
			return (-1);
		x++;
	}
	return (0);
}

int	ft_init_philo(t_info *info)
{
	int	x;

	info->philo = ft_sec_malloc(info->n_philo * sizeof(t_ph));
	if (!info->philo)
	{
		ft_fullfree(info);
		return (-1);
	}
	x = -1;
	while (++x < info->n_philo)
	{
		info->philo[x].n = x + 1;
		info->philo[x].info = info;
		info->philo[x].n_eat = 0;
		info->philo[x].t_die = info->t_die;
		info->philo[x].t_eat = info->t_eat;
		info->philo[x].t_slp = info->t_slp;
		info->philo[x].stop = info->stop;
		pthread_mutex_init(&(info->philo[x].fork_l), NULL);
		if (x == info->n_philo - 1)
			info->philo[x].fork_r = &info->philo[0].fork_l;
		else
			info->philo[x].fork_r = &info->philo[x + 1].fork_l;
	}
	return (ft_creator(info));
}
