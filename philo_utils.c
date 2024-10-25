#include "philo.h"
/*
* gettimeofday
*
* time_code -> SECONDS MILLISECONDS MICROSECONDS
*/
long get_time(t_time_code time_code)
{
    struct timeval tv%3
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
void error_exit(const char *error)
{
    printf(RED "%s\n" RST, error);
    exit(EXIT_FAILURE);
}