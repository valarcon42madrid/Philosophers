/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 17:28:24 by valarcon          #+#    #+#             */
/*   Updated: 2022/12/12 17:28:27 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_fullfree(t_info *info)
{
	pthread_mutex_destroy(&info->endlock);
	pthread_mutex_destroy(&info->endeat);
	pthread_mutex_destroy(&info->neat);
	pthread_mutex_destroy(&info->leat);
	pthread_mutex_destroy(&info->destroy);
	free(info->end_eat);
	free(info);
}

int	ft_check_arg(int argc, char **argv)
{
	int	x;
	int	aux;

	x = 1;
	while (x < argc)
	{
		if (!argv || !argv[x])
			return (0);
		aux = ft_atoi(argv[x]);
		if (aux == -1)
		{
			write(2, "Invalid arguments\n", 18);
			return (0);
		}
		x++;
	}
	return (1);
}

int	ft_atoi(char	*str)
{
	long	res;

	while (str && (*str == ' ' || (*str >= '\t' && *str <= '\r')))
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		if (res > 2147483647)
			return (-1);
		res = res * 10 + *str - '0';
		str++;
	}
	if (*str && *str > 31 && *str < 127)
		return (-1);
	return (res);
}

void	*ft_sec_malloc(int size)
{
	void	*res;

	if (size < 1)
		return (NULL);
	res = malloc(size);
	if (!res)
	{
		write(2, "Malloc error\n", 13);
		exit (2);
		return (NULL);
	}
	return (res);
}

void	ft_usleep(useconds_t time)
{
	useconds_t	t;

	t = get_useconds();
	while (get_useconds() - t < time)
		usleep(1);
}
