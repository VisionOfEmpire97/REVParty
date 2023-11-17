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

FILE *begin_to_log(const char *filename)
{
    FILE *logfp;
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
    fprintf(logfp, "**\tDébut du programme\n\n**");
    return logfp;
}

void append_to_log_file(const char *textToLog, FILE *logfp)
{
    fprintf(logfp, "%s", textToLog);
}

void close_log_file(FILE *logfp)
{
    fprintf(logfp, "**\n\tFin du programme\n**");
    if (logfp != stdout)
    {
        fclose(logfp);
    }
}
