#include "philo.h"
// think routine

static void thinking(t_philo *philo)
{
    write_status(THINKING, philo, DEBUG_MODE);
}
/*
* eat routine
*
* 1) grab the forks: here first & second fork is handy
* i don t worry about left right
* 2) eat : write eat, update last meal, update meals counter
eventually bool full
* 3) release the forks
*/
static void eat(t_philo *philo)
{
    // 1)
    safe_mutex_handle(&philo->first_fork->fork, LOCK);
    write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
    safe_mutex_handle(&philo->second_fork->fork, LOCK);
    write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
    // 2)
    set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MILLISECOND));
    philo->meals_counter++;
    write_status(EATING, philo, DEBUG_MODE);
    precise_usleep(philo->table->time_to_eat);
    if (philo->table->nbr_limit_meals > 0 && philo->meals_counter == philo->table->nbr_limit_meals)
        set_bool(&philo->philo_mutex, &philo->full, true);

    safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
    safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}
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
    wait_all_threads(philo->table);
    while (!simulation_finished(philo->table))
    {

        // 1) am i full?
        if (philo->full) // TODO thread safe?
            break;
        // 2) eat
        eat(philo);

        // 3) sleep ->write_status & precise usleep
        write_status(SLEEPING, philo, DEBUG_MODE);
        precise_usleep(philo->table->time_to_sleep);

        // 4) think
        thinking(philo); // TODO
    }
    return (NULL);
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
        return; // back to main, clean
    else if (1 == table->nbr_of_philos)
        ; // TODO
    else
    {
        while (++i < table->nbr_of_philos)
            safe_thread_handle(&table->philos[i].thread_id, dinner_simulation,
                               &table->philos[i], CREATE);
    }
    // start_of_simulation
    table->start_simulation = get_time(MILLISECOND);
    set_bool(&table->table_mutex, &table->all_theads_ready, true);
    // Wait for all
    i = -1;
    while (++i < table->nbr_of_philos)
        safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
}