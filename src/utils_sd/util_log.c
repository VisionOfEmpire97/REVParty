/**
 * @file util_log.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-11-06
 * 
 */

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
void begin_to_log(const char *filename) // will check if filename exists, and open it in write
{
    FILE *file;
    if (filename != NULL)
    {
        file = fopen(filename, "wt");
    }
    else
    {
        file = stdout;
    }
    // something should happen here, dunno what tho
    //probably should add stdout and stderr to file 
}