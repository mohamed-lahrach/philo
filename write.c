#include "philo.h"

static void write_status_debug(t_philo_status status, t_philo *philo, long elapsed)
{
    if (TAKE_FIRST_FORK == status && !simulation_finished(philo->table))
        printf("%ld " RST " %d has taken the 1° fork"
               "\t\t\t " B "[if %d if ] \n" RST,
               elapsed, philo->id, philo->first_fork->fork_id);

    else if (TAKE_SECOND_FORK == status && !simulation_finished(philo->table))
        printf("%ld " RST " %d has taken the 2° fork"
               "\t\t\tn° " B "[ if %d if ] \n" RST,
               elapsed, philo->id, philo->second_fork->fork_id);

    else if (EATING == status && !simulation_finished(philo->table))
        printf("%ld " C " %d is eating "
               "\t\t\t" Y "[ %ld 6] \n" RST,
               elapsed, philo->id, philo->meals_counter);
    else if (SLEEPING == status && !simulation_finished(philo->table))
        printf("%ld " RST " %d is sleeping \n", elapsed, philo->id);
    else if (THINKING == status && !simulation_finished(philo->table))
        printf("%ld " RST " %d is thinking \n", elapsed, philo->id);
    else if (DIED == status)
        printf(RED "\t\t %ld %d died \n" RST, elapsed, philo->id);
}

void write_status(t_philo_status status, t_philo *philo, bool debug)
{
    long elapsed;

    safe_mutex_handle(&philo->table->write_lock, LOCK);
    if (philo->full)
        return;
    elapsed = get_time(MILLISECOND) - philo->table->start_simulation;
    if (debug)
    {
        write_status_debug(status, philo, elapsed);
    }
    else
    {
        if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status) && !simulation_finished(philo->table))
            printf("%-6ld " RST " %d has taken a fork\n", elapsed, philo->id);
        else if (EATING == status && !simulation_finished(philo->table))
            printf("%-6ld " C " %d is eating\n" RST, elapsed, philo->id);
        else if (SLEEPING == status && !simulation_finished(philo->table))
            printf("%-6ld" RST " %d is sleeping\n", elapsed, philo->id);
        else if (THINKING == status && !simulation_finished(philo->table))
            printf("%-6ld " RST " %d is thinking\n", elapsed, philo->id);
        else if (DIED == status)
            printf(RED "%-6ld %d died\n" RST, elapsed, philo->id);
    }
    safe_mutex_handle(&philo->table->write_lock, LOCK);
}