// threads.c
#include "../include/philosophers.h"
// Función para imprimir el estado de un filósofo de manera segura
void print_state(t_philosopher *philosopher, char *state)
{
    long long timestamp;

    pthread_mutex_lock(&philosopher->data->print_lock);
    timestamp = get_time_in_ms() - philosopher->data->start_time;
    printf("%lld %d %s\n", timestamp, philosopher->id, state);
    pthread_mutex_unlock(&philosopher->data->print_lock);
}

// Rutina que ejecuta cada filósofo
void *philosopher_routine(void *arg)
{
    t_philosopher *philosopher = (t_philosopher *)arg;

    // Si el filósofo es par, esperar un poco para evitar condiciones de carrera
    if (philosopher->id % 2 == 0)
        usleep(1000);
    
    while (1)
    {
        // Pensar
        print_state(philosopher, "is thinking");

        // Tomar el tenedor izquierdo
        pthread_mutex_lock(philosopher->left_fork);
        print_state(philosopher, "has taken a fork");

        // Tomar el tenedor derecho
        pthread_mutex_lock(philosopher->right_fork);
        print_state(philosopher, "has taken a fork");

        // Comer
        pthread_mutex_lock(&philosopher->data->print_lock);
        philosopher->last_meal = get_time_in_ms();
        print_state(philosopher, "is eating");
        pthread_mutex_unlock(&philosopher->data->print_lock);
        usleep(philosopher->data->time_to_eat * 1000);
        philosopher->eat_count++;

        // Soltar los tenedores
        pthread_mutex_unlock(philosopher->right_fork);
        pthread_mutex_unlock(philosopher->left_fork);

        // Dormir
        print_state(philosopher, "is sleeping");
        usleep(philosopher->data->time_to_sleep * 1000);
    }
    return (NULL);
}

// Función para crear los hilos de los filósofos
int create_threads(t_data *data)
{
    for (int i = 0; i < data->num_philosophers; i++)
    {
        if (pthread_create(&data->threads[i], NULL, philosopher_routine, &data->philosophers[i]) != 0)
            return (1);
    }
    return (0);
}

// Función para unir los hilos de los filósofos
int join_threads(t_data *data)
{
    for (int i = 0; i < data->num_philosophers; i++)
    {
        if (pthread_join(data->threads[i], NULL) != 0)
            return (1);
    }
    return (0);
}

// simulation.c

// Función para verificar si algún filósofo ha muerto o si todos han comido lo suficiente
int start_simulation(t_data *data)
{
    int             i;
    long long       current_time;
    int             all_ate;

    // Crear hilos de filósofos
    if (create_threads(data))
        return (1);

    while (1)
    {
        for (i = 0; i < data->num_philosophers; i++)
        {
            pthread_mutex_lock(&data->print_lock);
            current_time = get_time_in_ms();
            if ((current_time - data->philosophers[i].last_meal) > data->time_to_die)
            {
                printf("%lld %d died\n", current_time - data->start_time, data->philosophers[i].id);
                pthread_mutex_unlock(&data->print_lock);
                // Terminar la simulación
                return (1);
            }
            pthread_mutex_unlock(&data->print_lock);
        }

        // Verificar si todos los filósofos han comido la cantidad requerida
        if (data->must_eat_count != -1)
        {
            all_ate = 1;
            for (i = 0; i < data->num_philosophers; i++)
            {
                if (data->philosophers[i].eat_count < data->must_eat_count)
                {
                    all_ate = 0;
                    break;
                }
            }
            if (all_ate)
            {
                // Indicar que todos han comido lo suficiente
                pthread_mutex_lock(&data->print_lock);
                data->all_ate = 1;
                pthread_mutex_unlock(&data->print_lock);
                return (1);
            }
        }

        usleep(1000); // Pequeña pausa para reducir el uso de CPU
    }
    return (0);
}

// exit.c

// Función para liberar recursos
void free_resources(t_data *data)
{
    // Destruir mutexes de los tenedores
    for (int i = 0; i < data->num_philosophers; i++)
    {
        pthread_mutex_destroy(&data->forks[i]);
    }

    // Destruir mutex de impresión
    pthread_mutex_destroy(&data->print_lock);

    // Liberar memoria
    free(data->forks);
    free(data->threads);
    free(data->philosophers);
}
