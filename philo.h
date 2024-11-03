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
#include <errno.h>    // errno

/*
** ANSI Escape Sequences for Bold Text Colors
** Usage:
** printf(R "This is red text." RST);
** printf(B "This is blue text." RST);
** Remember to use RST to reset the color after setting it.*/

#define RST "\033[0m"    // Reset to default color
#define RED "\033[1;31m" /* Bold Red */
#define G "\033[1;32m"   /* Bold Green */
#define Y "\033[1;33m"   /* Bold Yellow */
#define B "\033[1;34m"   /* Bold Blue */
#define M "\033[1;35m"   /* Bold Magenta */
#define C "\033[1;36m"   /* Bold Cyan */
#define W "\033[1;37m"   /* Bold White */
#define DEBUG_MODE 0

/*
 * OPCODE for mutex | thread functions
 */
typedef enum e_opcode
{
    LOCK,
    UNLOCK,
    INIT,
    DESTROY,
    CREATE,
    JOIN,
    DETACH,
} t_opcode;
/*
 * CODES for gettime
 */
typedef enum e_time_code
{
    SECOND,
    MILLISECOND,
    MICROSECOND,
} t_time_code;

typedef enum e_status
{
    EATING,
    SLEEPING,
    THINKING,
    TAKE_FIRST_FORK,
    TAKE_SECOND_FORK,
    DIED,
} t_philo_status;

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
    t_fork *first_fork;
    t_fork *second_fork;
    t_mtx philo_mutex; 
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
    bool end_simulation; // triggers philo die or all philos are full
    bool all_theads_ready;
    t_mtx table_mutex; // avoid races while reading from the table
    t_mtx write_lock;
    t_fork *forks;
    t_philo *philos;
};

// utils
long get_time(t_time_code time_code);
void error_exit(const char *error);
long get_elapsed_time_microseconds(struct timeval start, struct timeval end);
void precise_usleep(long usec);
// parsing
void parse_input(t_table *table, char **av);
// safe functions
void *safe_malloc(size_t bytes);
// static void handle_mutex_error(int status, t_opcode opcode);
void safe_mutex_handle(pthread_mutex_t *mutex, t_opcode opcode);
// static void handle_thread_error(int status, t_opcode opcode);
void safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode);
void error_exit(const char *message);
// init
void data_init(t_table *table);

// getters and setters
void set_bool(t_mtx *mutex, bool *dest, bool value);
bool get_bool(t_mtx *mutex, bool *src);
void set_long(t_mtx *mutex, long *dest, long value);
long get_long(t_mtx *mutex, long *src);
bool simulation_finished(t_table *table);

// synchro utils
void wait_all_threads(t_table *table);

// dining
void dinner_start(t_table *table);
void *dinner_simulation(void *data);

// write
void write_status(t_philo_status status, t_philo *philo, bool debug);

#endif // PHILO_H