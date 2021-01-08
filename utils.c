#include "utils.h"

// Checks if the port is valid
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
        printf("The port must be included between 2014 and 65535\n");
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

int check_server_address(char* IP ){
    char buffer[16];
    if (inet_pton(AF_INET, IP, buffer)){
        return 1;
    }
    else if (inet_pton(AF_INET6, IP, buffer)){
        return 1;
    }
    return 0;
}


void check_args_client(int n, char** args){
    //checks the number of arguments
    if (n != 4){
        printf("USAGE : %s SERVER_ADDRESS PORT MESSAGE\n", args[0] );
        exit(0);
    }
    // Checks validity of the port
    check_port(args[2]);
    if (!check_server_address(args[1])){
        printf("IP address is not valid\n");
        exit(1);
    }
    // checks if the size of the message doesn't exceed 255 bytes
    if (strlen(args[3])>= MSG_SIZE){
        printf("Size must not exceed 255 bytes\n");
        exit(2);
    }
}

//This function displays log : date + time
void display_log(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("[%d-%02d-%02d %02d:%02d:%02d] [+] ", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

// Create an UDP socket and checks if there are errors.
SOCKET create_socket(){
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock == INVALID_SOCKET){
        perror("error create socket");
        exit(-1);
    }
    return sock;
}