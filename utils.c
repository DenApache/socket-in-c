#include "utils.h"

void check_port(char* sport){
    regex_t reg;
    regcomp(&reg, PORT_REGEX, REG_NOSUB | REG_EXTENDED);

    if(regexec(&reg, sport, 0, NULL, 0)){
        fprintf(stderr,"Invalid port\n");
        exit(INVALID_PARAM);
    }
    //Checks port's interval
    int port = atoi(sport);
    if (!(port>1024) || !(port<=65535)){
        printf("The TCP port must be included between 2014 and 65535\n");
        exit(1);
    }
}

void check_args_server(int n, char** args){
    //checks the number of arguments
    if (n != 2){
        printf("USAGE : %s PORT\n", args[0] );
        exit(0);
    }
    //Checks port's format
    check_port(args[1]);
}

int check_args_client(int n, char** args){
    if (n != 4){
        printf("USAGE : %s ADRESSE PORT MESSAGE\n", args[0] );
        exit(0);
    }
    check_port(args[2]);
    
    return 0;
}

void display_log(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("[%d-%02d-%02d %02d:%02d:%02d] [+] ", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}
