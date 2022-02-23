#include "libft/libft.h"
#include <sys/types.h>
#include <unistd.h>

#define ERR_SYNTX "Usage: ./client [PID] [message]\n"

void    print_err(char *err)
{
    ft_putstr_fd(ERR_SYNTX, 2);
    exit(1);
}

int     checker(char *pid, char *message)
{
    if ((*pid == '0' && *(pid + 1) == '\0') || *pid == '-')
        print_err(ERR_SYNTX);
    while (*pid)
    {
        if (!ft_isdigit(*pid))
        {
            print_err(ERR_SYNTX);
            return (-1);
        }
        pid++;
    }
    if (!message || message[0] == '\0')
    {
        print_err(ERR_SYNTX);
        return (-1);
    }
    return (0);
}

void    received(int signo)
{
    ft_putstr_fd("the message has been received by the server\n");
}

void    send_message(char *pid, char *message)
{
    int counter;

    counter = 1 << 7;

}

int main(int ac, char **av)
{
    signal(SIGUSR1, received);
    if (ac == 3)
    {
       if (checker(av[1], av[2]) == -1)
        return (1);
        send_message(av[1], av[2]);
    }
    else
     print_err(ERR_SYNTX);
    return (0);
}
