#include "philo.h"

void wait_all_threads(t_table *table)
{
    while (atomic_flag_test_and_set(&lock))
        ;
}