#include "philo.h"

/*
* 0) wait all philos, synchro start
⭑
* 1) endless loop philo
*/
void *dinner_simulation(void *data)
{
    t_philo *philo;
    philo = (t_philo *)data;
    // spinlocker
    wait_all_threads (philo->table);
    return (NULL)
}

/*
* actual meat
*
* ./philo 5 800 200 200 [5]
⭑
* 0) If no meals, return ->[0]
* 0.1) If only one philo-> ad hoc function
* 1) Create all threads, all philos
* 2) Create a monitor thread ->
* 3) Synchronize the begginning of the simulation
⭑ pthread_create-> philo starts running!
⭑ every philo start simultaneously
* 4) JOIN everyone
*/
void dinner_start(t_table *table)
{
    int i;
    i = -1;
    if (0 == table->nbr_limit_meals)
        return ; // back to main, clean
    else if (1 == table->philo_nbr) I
        ;//TODO
    else
    {
        while (++i < table->philo_nbr)
        safe_thread_handle(&table->philos[i].thread_id, dinner_simulation,
        &table->philos[i], CREATE);
    }
    // start_of_simulation
    table->start_of_simulation = get_time(MILLISECOND)
    set_bool(&table->table_mutex, &table->all_theads_ready, true);
    // Wait for all 
    i = -1;
    while(++i < table->nbr_of_philos)
        safe_thread_handle(&table->philos[i], NULL, NULL, JOIN)
}