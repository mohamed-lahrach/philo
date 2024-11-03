#include "philo.h"


void set_bool(t_mtx *mutex, bool *dest, bool value) {
    safe_mutex_handle(mutex, LOCK);   // Lock the mutex to ensure thread safety
    *dest = value;               // Set the boolean value
    safe_mutex_handle(mutex, UNLOCK); // Unlock the mutex
}

bool get_bool(t_mtx *mutex, bool *src) {
    bool value;
    safe_mutex_handle(mutex, LOCK);   // Lock the mutex to ensure thread safety
    value = *src;                // Get the boolean value
    safe_mutex_handle(mutex, UNLOCK); // Unlock the mutex
    return value;
}

void set_long(t_mtx *mutex, long *dest, long value) {
    safe_mutex_handle(mutex, LOCK);   // Lock the mutex to ensure thread safety
    *dest = value;               // Set the long value
    safe_mutex_handle(mutex, UNLOCK); // Unlock the mutex
}

long get_long(t_mtx *mutex, long *src) {
    long value;
    safe_mutex_handle(mutex, LOCK);   // Lock the mutex to ensure thread safety
    value = *src;                // Get the long value
    safe_mutex_handle(mutex, UNLOCK); // Unlock the mutex
    return value;
}

bool simulation_finished(t_table *table)
{
    return (get_bool(&table->table_mutex, &table->end_simulation));
}
