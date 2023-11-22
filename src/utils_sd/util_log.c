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
#include "util_log.h"

FILE *logfp;

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
    fprintf(logfp, "*****\tDébut du programme\t*****\n\n");
    return logfp;
}

void append_to_log_file(const char *textToLog)
{
    fprintf(logfp, "%s\n", textToLog);
}

void close_log_file()
{
    fprintf(logfp, "\n*****\tFin du programme\t*****\n");
    if (logfp != stdout)
    {
        fclose(logfp);
    }
}
