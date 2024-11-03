#include "philo.h"
/*
 * gettimeofday
 *
 * time_code -> SECONDS MILLISECONDS MICROSECONDS
 */
long get_time(t_time_code time_code)
{
    struct timeval tv;
    if (gettimeofday(&tv, NULL))
        error_exit("Gettimeofday failed");
    if (SECOND == time_code)
        return (tv.tv_sec + (tv.tv_usec / 1e6));
    else if (MILLISECOND == time_code)
        return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
    else if (MICROSECOND == time_code)
        return ((tv.tv_sec * 1e6) + tv.tv_usec);
    else
        error_exit("Wrong input to gettime!");
    return (1337);
}

long get_elapsed_time_microseconds(struct timeval start, struct timeval end)
{
    return (end.tv_sec - start.tv_sec) * 1000000L + (end.tv_usec - start.tv_usec);
}

void precise_usleep(long usec)
{
    struct timeval start, current;
    long elapsed;
    long rem;

    gettimeofday(&start, NULL);
    do
    {
        gettimeofday(&current, NULL);
        elapsed = get_elapsed_time_microseconds(start, current);
        rem = usec - elapsed;
        if (rem > 1000)
            usleep(rem / 2); // Sleep for half the remaining time
    } while (elapsed < usec);
}

void error_exit(const char *error)
{
    printf(RED "%s\n" RST, error);
    exit(EXIT_FAILURE);
}