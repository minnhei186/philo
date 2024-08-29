/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:17:57 by hosokawa          #+#    #+#             */
/*   Updated: 2024/08/29 11:02:27 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <ctype.h>
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

typedef struct s_theread_memory
{
	pthread_t			*tid;
	int					philo_num;
	int					meals_nb;
	int					dead;
	t_philo				*philos;
	u_int64_t			death_time;
	u_int64_t			eat_time;
	u_int64_t			sleep_time;
	u_int64_t			start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		write;
}						t_thread_memory;

typedef struct s_philo
{
	t_thread_memory		*data;
	pthread_t			t1;
	int					id;
	int					eat_count;
	int					eating;
	u_int64_t			time_to_die;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
}						t_philo;

// philo_utils
void					protected_output(char *str, t_philo *philo);
int						ft_isdigit(int c);
int						ft_atoi(const char *str);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						calc_wait_time(t_philo *philo);

// free_utils
void					all_mutex_destroy(t_thread_memory *thread_info);
void					memory_free(t_thread_memory *thread_info);

// error_exit
void					init_fork_mutex_error(t_thread_memory *info, int i);
void					init_mutex_error(pthread_mutex_t *dead_lock,
							pthread_mutex_t *meal_lock, pthread_mutex_t *write);
int						error_exit(t_thread_memory *info, char *str);
// check_validation
int						is_sutable_argv(int argc);
int						is_argument_number(char **argv);
int						is_sutable_number(char **argv);
int						check_validation_arg(int argc, char **argv);

// data_init_utils
int						thread_fork_init(t_thread_memory *thread_m);

// data_init
void					philo_data_init(t_thread_memory *thread_m,
							t_philo *philo, int philo_id);
void					philo_mutex_init(t_thread_memory *thread_m,
							t_philo *philo);
void					philo_init(t_thread_memory *thread_m);
int						thread_mutex_init(t_thread_memory *thread_m);
int						thread_init(t_thread_memory *thread_m, char **argv);

// time
u_int64_t				get_time(void);
void					ft_strict_usleep(u_int64_t time);

// philo_check
int						dead_check(t_thread_memory *info);

//

// philo_func
void					philo_think_start(t_philo *philo);
void					philo_sleep(t_philo *philo);
void					get_fork(char *fork, t_philo *philo);
void					eat(t_philo *philo);
void					philo_dinner(t_philo *philo);

// observe_and_moniter
int						survived_check(t_thread_memory *info);
int						noteat_check(t_thread_memory *info, t_philo philo,
							u_int64_t dead_time);
int						noteat_dead(t_thread_memory *info);
int						death_flag_wake_up(t_thread_memory *info);
void					*moniter(void *thread_info);
#endif
