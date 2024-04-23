/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 11:47:46 by valarcon          #+#    #+#             */
/*   Updated: 2022/12/12 17:24:43 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef struct l_philo
{
	int				n;
	int				n_eat;
	pthread_t		thread;
	useconds_t		lst_eat;
	struct l_info	*info;
	int				t_die;
	int				t_eat;
	int				t_slp;
	int				stop;
	useconds_t		t_start;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	fork_l;
}			t_ph;

typedef struct l_info
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_slp;
	int				*end_eat;
	int				stop;
	useconds_t		t_start;
	t_ph			*philo;
	pthread_mutex_t	endlock;
	pthread_mutex_t	endeat;
	pthread_mutex_t	leat;
	pthread_mutex_t	neat;
	pthread_mutex_t	destroy;
}			t_info;

useconds_t	get_useconds(void);
int			ft_init_info(t_info *info, int argc, char **argv);
int			ft_init_philo(t_info *info);
void		ft_act(t_ph *ph);
void		print_philo_status(t_ph *ph, char *status);
void		print_philo_dead(t_ph *ph, char *status);
void		ph_eat(t_ph *ph);
void		*ph_life(void	*arg);
void		ft_fullfree(t_info *info);
int			ft_check_arg(int argc, char **argv);
int			ft_atoi(char *str);
void		*ft_sec_malloc(int size);
void		ft_usleep(useconds_t time);
useconds_t	ft_lsteat(t_ph	*ph);
int			ft_neat(t_ph	*ph);
void		ft_endeat(t_ph	*ph);
int			ft_endalleat(t_info *info);

#endif
