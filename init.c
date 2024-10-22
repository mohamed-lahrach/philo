#include "philo.h"

static void assign_forks(t_philo *philo, t_fork *forks,
                         int philo_position)
{
    int nbr_of_philos;
    nbr_of_philos = philo->table->nbr_of_philos;
    philo->first_fork = &forks[(philo_position + 1) % nbr_of_philos];
    philo->second_fork = &forks[philo_position];
    if (philo->id % 2 == 0)
    {
        philo->first_fork = &forks[philo_position];
        philo->second_fork = &forks[(philo_position + 1) % nbr_of_philos];
    }
}
static void philo_init(t_table *table)
{
    int i;
    t_philo *philo;
    i = -1;
    while (++i < table->nbr_of_philos)
    {
        philo = table->philos + i;
        philo->id = i + 1;
        philo->full = false;
        philo->meals_counter = 0;
        philo->table = table;
        assign_forks(philo, table->forks, i);
    }
}
void data_init(t_table *table)
{
    int i;
    i = -1;
    table->end_simulation = false;
    table->philos = safe_malloc(sizeof(t_philo) * table->nbr_of_philos);
    table->forks = safe_malloc(sizeof(t_fork) * table->nbr_of_philos);
    while (++i < table->nbr_of_philos)
    {
        safe_mutex_handle(&table->forks[i].fork, INIT);
        table->forks[i].fork_id = i; // super for debug
    }
    philo_init(table); // TODO
}