#include "../include/philosophers.h"

// init.c

// Función para convertir cadena a entero con validación básica
int ft_atoi(const char *str)
{
    int             i;
    int             sign;
    int             res;

    i = 0;
    sign = 1;
    res = 0;
    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        res = res * 10 + (str[i] - '0');
        i++;
    }
    return (res * sign);
}

// Función para obtener el tiempo actual en milisegundos
long long get_time_in_ms(void)
{
    struct timeval  time;
    long long       ms;

    gettimeofday(&time, NULL);
    ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    return (ms);
}

// Función para inicializar los datos compartidos
int init_data(t_data *data, int argc, char **argv)
{
    if (argc != 5 && argc != 6)
    {
        printf("Uso: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
        return (1);
    }

    data->num_philosophers = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    data->must_eat_count = (argc == 6) ? ft_atoi(argv[5]) : -1;
    data->all_ate = 0;
    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
    data->threads = malloc(sizeof(pthread_t) * data->num_philosophers);
    data->philosophers = malloc(sizeof(t_philosopher) * data->num_philosophers);
    if (!data->forks || !data->threads || !data->philosophers)
        return (1);
    
    // Inicializar mutex de impresión
    if (pthread_mutex_init(&data->print_lock, NULL) != 0)
        return (1);
    
    // Inicializar mutexes de los tenedores
    for (int i = 0; i < data->num_philosophers; i++)
    {
        if (pthread_mutex_init(&data->forks[i], NULL) != 0)
            return (1);
    }
    
    // Registrar el tiempo de inicio
    data->start_time = get_time_in_ms();
    return (0);
}

// Función para inicializar los filósofos
int init_philosophers(t_data *data)
{
    for (int i = 0; i < data->num_philosophers; i++)
    {
        data->philosophers[i].id = i + 1;
        data->philosophers[i].eat_count = 0;
        data->philosophers[i].last_meal = data->start_time;
        data->philosophers[i].left_fork = &data->forks[i];
        data->philosophers[i].right_fork = &data->forks[(i + 1) % data->num_philosophers];
        data->philosophers[i].data = data;
    }
    return (0);
}
