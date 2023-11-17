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

FILE *begin_to_log(const char *filename) // will check if filename exists, and open it in write
{
    FILE *logfp;
    if (filename != NULL)
    {
        logfp = fopen(filename, "wt");
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
    return logfp;
    // something should happen here, dunno what tho
    // probably should add stdout and stderr to file
}

void append_to_log_file(const char *nomMethode,const char *textToLog, FILE *logfp)
{

    fprintf(logfp, "**\tDébut du programme %s\n\n**", nomMethode); //?
    fprintf(logfp, "%s", textToLog);
    fprintf(logfp, "**\tFin du programme %s\n\n**", nomMethode); //?
}

void close_log_file(FILE *logfp) {
    if (logfp != stdout) {
        fclose(logfp);
    }
}
