#include "philo.h"

/*
* 1) check for negatives
* 2) Check if the number is legit
"I +77$%"
"I +&%42"
* 3) Check for INT_MAX
* 43274897238629374893274720947903274917047397
* check for len 2_147_483_647 if len > 10 sure > INT_MAX!
* (2_147_483_647 -> 9_999_999_999) still to check
* function will return a pointer to the first valid number "       +323fsdf"
*                                                                   ^
*/
static inline bool is_space(char c)
{
    return ((c >= 9 && c <= 13) || 32 == c);
}

static inline bool is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

static const char *valid_input(const char *str)
{
    int len;
    const char *number;

    len = 0;
    while (is_space(*str))
        str++;
    if (*str == '+')
        str++;
    else if (*str == '-')
        error_exit("Negative number");
    if (!is_digit(*str))
        error_exit("Invalid number");
    number = str;
    while (is_digit(number[len]))
        len++;
    if (len > 10)
        error_exit("Number > INT_MAX");
    return (number);
}

long ft_atol(const char *str)
{
    long num;

    num = 0;
    str = valid_input(str);
    while (is_digit(*str))
    {
        num = num * 10 + *str - '0';
        str++;
    }
    if (num > INT_MAX)
        error_exit("Number > INT_MAX");
    return (num);
}
/*
* ./philo 5 800 200 200 [5]
⭑ av[1] av[2] av[3]
* 1) actual numbers
* 2) not > INT_MAX
* 3) timestamps > 60ms
*/
void parse_input(t_table *table, char **av)
{
    table->nbr_of_philos = ft_atol(av[1]);
    table->time_to_die = ft_atol(av[2]) * 1e3;
    table->time_to_eat = ft_atol(av[3]) * 1e3;
    table->time_to_sleep = ft_atol(av[4]) * 1e3;
    if (table->time_to_die < 6e4 || 
        table->time_to_eat < 6e4 || 
        table->time_to_sleep < 6e4)
        error_exit("Use timestamps major than 60ms");
    if(av[5])
        table->nbr_limit_meals = ft_atol(av[5]);
    else
        table->nbr_limit_meals = -1;
}