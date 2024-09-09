#include "../include/philosophers.h"
// main.c

int main(int argc, char **argv)
{
    t_data  data;

    // Inicializar datos
    if (init_data(&data, argc, argv))
    {
        printf("Error en la inicialización de datos.\n");
        return (1);
    }
    // Inicializar filósofos
    if (init_philosophers(&data))
    {
        printf("Error en la inicialización de filósofos.\n");
        free_resources(&data);
        return (1);
    }
    // Iniciar simulación
    if (start_simulation(&data))
    {
        printf("Error en la simulación.\n");
        free_resources(&data);
        return (1);
    }
    // Limpiar recursos
    free_resources(&data);
    return (0);
}
