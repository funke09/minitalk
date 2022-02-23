#include "libft/libft.h"
#include <sys/types.h>
#include <unistd.h>


int main()
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