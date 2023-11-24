#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include "util_log.h"

int main(int argc, char const *argv[])
{
    
    FILE *logfp = begin_to_log(argv[1]);
    append_to_log_file("test");
    close_log_file();
    return 0;
}
