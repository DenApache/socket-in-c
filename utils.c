#include "utils.h"

int check_args_server(int n, char** args){
    //checks the number of arguments
    if (n != 2){
        printf("USAGE : %s PORT\n", args[0] );
        exit(0);
    }
    //Checks port's format
    regex_t reg;
    regcomp(&reg, PORT_REGEX, REG_NOSUB | REG_EXTENDED);

    if(regexec(&reg, args[1], 0, NULL, 0)){
        fprintf(stderr,"Invalid port\n");
        exit(INVALID_PARAM);
    }
    //Checks port's interval
    int port = atoi(args[1]);
    if (!(port>1024) || !(port<=65535)){
        printf("The TCP port must be included between 2014 and 65535\n");
        exit(1);
    }
    return port;
}

int check_args_client(int n, char** args){
    if (n != 4){
        printf("USAGE : %s PORT\n", args[0] );
        exit(0);
    }
    return 0;
}