#include <stdio.h>

#include "log.h"

int main(int argc, char **argv)
{
    log(LOG_NOTICE, "hello world!"); 
    return 0;
}