#include "minitalk.h"


void    main_server()
{
    pid_t    pid;

    pid = getpid();
    while (1)
    {
        ft_putnbr_fd(pid, 1);
        ft_putchar_fd('\n', 1);
        pause();
    }
}

int main(void)
{
    struct sigaction true_bit; // when the server receive SIGUSR1 
    struct sigaction false_bit; // when the server receive SIGUSR2 
    
    main_server();
}