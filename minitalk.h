#ifndef MINITALK_H
#define MINITALK_H

#include "libft/libft.h"
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

#define BUFFER_SIZE 4096

typedef struct s_minitalk
{
    char buffer[BUFFER_SIZE];

    bool all_done;
    int top_bit;
    int top_byte;
    /* data */
}       t_minitalk;

t_minitalk g_mini;

#endif
