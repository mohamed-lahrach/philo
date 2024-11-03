#include "philo.h"

// ./philo 5 800 200 200 [5]

int main(int argc, char **argv)
{
    t_table table;

    if (argc == 5 || argc == 6)
    {
        //correct input
        // 1) check if the input is correct filling the table struct
        parse_input(&table, argv);

        // 2) initialize the table
        data_init(&table);

        // 3) dinner starts
        dinner_start(&table);

        // 4) no leaks | philos full | a philo dead
        //clean(&table);
    }
    else
    {
        error_exit("Wrong input: \n"
                G"Correct is ./philo 5 800 200 200 [5]" RST);
    }
}