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
    int validity, byte, IP_len, dotCount;
       
    validity = 1;
    IP_len = strlen(IP);
    dotCount = 0;
   
    // Checks the length of the chain
    if( !IP_len || IP_len > 15)
        validity = 0;
    else{
        /* We recover the first byte  */
        byte = atoi(IP);
        /* If it is greater than 255 then it is not a valid IP */
        if(byte > 255)
            validity = 0;    
        /* We go through the chain */
        for(int i = 0; i < IP_len && validity; i++){
            /* We check if each character is only a number or a dot */
            if(!(IP[i] >= '0' && IP[i] <= '9') && IP[i] != '.')
                validity = 0;
          
            /* Count the number of dots*/
            if(IP[i] == '.'){
                dotCount ++;
                /* We check if the byte we retrieve is valid */
                byte = atoi(&IP[i+1]);
                if(byte > 255){
                    validity = 0;
                }
            }
        }
        /* if there are not three points in the ip then it is not a valid ip */
        if(dotCount != 3)
            validity = 0;         
    } 
    return validity; 
}

void check_args_client(int n, char** args){
    if (n != 4){
        printf("USAGE : %s SERVER_ADDRESS PORT MESSAGE\n", args[0] );
        exit(0);
    }
    check_port(args[2]);
    if (!check_server_address(args[1])){
        printf("Address IP is not valid\n");
        exit(1);
    }
    if (strlen(args[3])>= MSG_SIZE){
        printf("Size must not exceed 255 bytes\n");
        exit(2);
    }
}

void display_log(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("[%d-%02d-%02d %02d:%02d:%02d] [+] ", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

SOCKET create_socket(){
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock == INVALID_SOCKET){
        perror("error create socket");
        exit(-1);
    }
    return sock;
}