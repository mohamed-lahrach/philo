#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>    // printf
#include <unistd.h>   // sleep usleep write
#include <stdlib.h>   // malloc free
#include <string.h>   // memset
#include <pthread.h>  // threads : create, join, detach mutex: init , lock , unlock, destroy
#include <sys/time.h> // gettimeofday
#include <stdbool.h>  // bool
#include <limits.h>   // INT_MAX


/*
** ANSI Escape Sequences for Bold Text Colors
** Usage:
** printf(R "This is red text." RST);
** printf(B "This is blue text." RST);
** Remember to use RST to reset the color after setting it.*/

# define RST "\033[0m" //Reset to default color 
# define RED "\033[1;31m" /* Bold Red */
# define G "\033[1;32m" /* Bold Green */
# define Y "\033[1;33m" /* Bold Yellow */
# define B "\033[1;34m" /* Bold Blue */
#define M "\033[1;35m" /* Bold Magenta */
# define C "\033[1;36m" /* Bold Cyan */
# define W "\033[1;37m" /* Bold White */

typedef pthread_mutex_t t_mtx;
typedef struct s_table t_table;

// fork struct
typedef struct s_fork
{
    t_mtx fork;
    int fork_id;
} t_fork;

// struct to hold the data of the philo
// ./philo 5 800 200 200 [5]

typedef struct s_philo
{
    int id;
    long meals_counter;
    bool full;
    long last_meal_time;
    t_mtx *left_fork;
    t_mtx *right_fork;
    pthread_t thread_id;
    t_table *table;

} t_philo;

// the table struct
struct s_table
{
    int nbr_of_philos;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    long nbr_limit_meals;
    long start_simulation;
    long end_simulation; // triggers philo die or all philos are full
    t_fork *forks;
    t_philo *philos;
};

// utils
void error_exit(const char *error);
// parsing
void parse_input(t_table *table, char **av);

#endif // PHILO_H