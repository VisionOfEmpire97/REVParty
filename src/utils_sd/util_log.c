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
#include "arg_parse_util.h"
#include "util_log.h"

FILE *logfp;
char *RED = "\033[1;31m";
char *GREEN = "\033[1;32m";
char *END_COLOR = "\e[00m";

FILE *begin_to_log(const char *filename)
{
    
    if (filename != NULL)
    {
        logfp = fopen(filename, "w");
        if (logfp == NULL)
        {
            perror("Echec d'ouverture du fichier de logs");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        logfp = stdout;
    }
    fprintf(logfp, "%s*****\tDébut du programme\t*****%s\n",GREEN,END_COLOR);
    return logfp;
}

void append_to_log_file(const char *textToLog)
{
    fprintf(logfp, "%s\n", textToLog);
}

void close_log_file()
{
    fprintf(logfp, "\n%s*****\tFin du programme\t*****%s\n",GREEN,END_COLOR);
    if (logfp != stdout)
    {
        fclose(logfp);
    }
}
