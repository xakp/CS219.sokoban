#include <stdlib.h>
#include <stdio.h>
#include "log.h"

int main (int argc, char* argv[]) 
{
    int data = 25;
    log_t *log = log_create(); 
    log_insertAfter( log, data );
    printf ("%d"\n, log->selected );
    return (0);
}