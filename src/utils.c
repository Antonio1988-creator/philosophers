// utils.c
#include "../include/philosophers.h"

// Función para obtener el tiempo actual en milisegundos
long long get_time_in_ms(void)
{
    struct timeval  time;
    long long       ms;

    gettimeofday(&time, NULL);
    ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    return (ms);
}

// Función para imprimir el estado de un filósofo de manera segura
void print_state(t_philosopher *philosopher, char *state)
{
    long long timestamp;

    pthread_mutex_lock(&philosopher->data->print_lock);
    timestamp = get_time_in_ms() - philosopher->data->start_time;
    printf("%lld %d %s\n", timestamp, philosopher->id, state);
    pthread_mutex_unlock(&philosopher->data->print_lock);
}

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
