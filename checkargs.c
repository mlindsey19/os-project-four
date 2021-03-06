//Mitch Lindsey
//cs 4760
//3-16-19
//
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "checkargs.h"


static void helpMenu(){
    printf("\n\t\tHelp\n");
    printf("Default - max: 4, live: 2\n");
    printf("-h show help menu\n");
    printf("-n processes limit\n");
    printf("-s alive process limit\n");
    printf("-o specify output file name\n");
}

int checkArgs(char outFilename[], int argc, char **argv, int * processLimit, int * activeLimit ) {

    int c, i;

    opterr = 0;

    while ((c = getopt(argc, argv, "ho:s:n:")) != -1)
        switch (c) {
            case 'h':
                helpMenu();
                break;
            case 'n':
                *processLimit = atoi(optarg);
                break;
            case 's':
                *activeLimit = atoi(optarg);
                break;
            case 'o':
                *outFilename = *optarg;
                break;
            case '?':
                if ( optopt == 'i' || optopt == 'o' )
                    fprintf( stderr, "Options -o and -i require an argument.\n");
                else if ( isprint( optopt ) )
                    fprintf( stderr, "Unknown option `-%c'.\n", optopt );
                else
                    fprintf( stderr, "Unknown option character `\\x%x'.\n", optopt );
                return 1;
            default:
                abort();
        }

    *activeLimit = *activeLimit > 20 ? 20 : *activeLimit;
    *processLimit = *processLimit > 20 ? 20 : *processLimit;
    *activeLimit = *processLimit < *activeLimit ? *processLimit : *activeLimit;

    for (i = optind; i < argc; i++)
        fprintf(stderr, "Non-option argument %s\n", argv[i]);
    return 0;
}