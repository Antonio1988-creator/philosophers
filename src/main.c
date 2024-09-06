//HEADER!!!

#include "../include/philosophers.h"

int ft_argum_comprobation(int argc, char **argv);

int main(int argc, char **argv)
{
    // Check if the number of arguments is correct
    if (ft_argum_comprobation(argc, argv) == 1)
        return (1);

    return (0);
}

int ft_argum_comprobation(int argc, char **argv)
{
    int i;
    int j;

    i = 1;
    if (argc != 5 && argc != 6)
    {
        printf("Error: Wrong number of arguments\n");
        return (1);
    }
    while (i < argc)
    {
        j = 0;
        while (argv[i][j])
        {
            if (argv[i][j] < '0' || argv[i][j] > '9')
            {
                printf("Error: Argument %d is not a number\n", i);
                return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}
