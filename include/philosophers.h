
// philo.h
#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>

// Estructura principal que contiene los datos compartidos
typedef struct s_data {
    int             num_philosophers;
    long long       time_to_die;
    long long       time_to_eat;
    long long       time_to_sleep;
    int             must_eat_count;
    long long       start_time;
    int             all_ate;
    pthread_mutex_t *forks;
    pthread_mutex_t print_lock;
    pthread_t       *threads;
    struct s_philosopher *philosophers;
}               t_data;

// Estructura para cada filósofo
typedef struct s_philosopher {
    int             id;
    int             eat_count;
    long long       last_meal;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_data          *data;
}               t_philosopher;

// Prototipos de funciones
// init.c
int             init_data(t_data *data, int argc, char **argv);
int             init_philosophers(t_data *data);

// threads.c
void            *philosopher_routine(void *arg);
int             create_threads(t_data *data);
int             join_threads(t_data *data);

// simulation.c
int             start_simulation(t_data *data);

// exit.c
void            free_resources(t_data *data);

// utils.c (Opcional para funciones auxiliares)
long long       get_time_in_ms(void);
void            print_state(t_philosopher *philosopher, char *state);
int             ft_atoi(const char *str);

#endif