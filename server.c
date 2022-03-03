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

void    true_bit_handler(int signo, siginfo_t *info, void *context)
{
    (void)signo;
    (void)context;
}

void    false_bit_handler(int signo, siginfo_t *info, void *context)
{
    (void)signo;
    (void)context;
}

int main(void)
{
    struct sigaction true_bit; // when the server receive SIGUSR1 
    struct sigaction false_bit; // when the server receive SIGUSR2 

    true_bit.sa_flags = SA_SIGINFO;
    false_bit.sa_flags = SA_SIGINFO;
    true_bit.sa_sigaction = &true_bit_handler;
    false_bit.sa_sigaction = &false_bit_handler;
    if (sigaction(SIGUSR1, &true_bit, NULL) == -1)
    {
        ft_putstr_fd("error", 2);
        exit(1);
    }
    if (sigaction(SIGUSR2, &false_bit, NULL) == -1)
    {
        ft_putstr_fd("error", 2);
        exit(1);
    }
    main_server();
    return (0);
}