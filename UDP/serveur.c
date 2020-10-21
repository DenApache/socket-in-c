#include "../utils.h"

int main(int argc, char *argv[]){

    if(argc != 2){
        fprintf(stderr, "Usage : %s PORT\n", argv[0]);
        exit(INVALID_PARAM);
    }
    
    regex_t reg;
    regcomp(&reg, PORT_REGEX, REG_NOSUB | REG_EXTENDED);

    if(regexec(&reg, argv[1], 0, NULL, 0)){
        fprintf(stderr,"Invalid port\n");
        exit(INVALID_PARAM);
    }

    PORT port = atoi(argv[1]);
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock == INVALID_SOCKET){
        perror("error create socket");
        exit(-1);
    }

    char buffer[BUFSIZ];

    // Creation de l'interface
    SOCKADDR_IN serv = { 0 };
    serv.sin_family =  AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(port);
    
        // Liaison socket + interface
    if(bind(sock, (SOCKADDR *) &serv, sizeof(serv)) == SOCKET_ERROR){
        perror("error bind");
        exit(-1);
    }

    SOCKADDR_IN clt = {0};
    u_int32_t l_clt = sizeof(clt);

    printf("Start listening %s:%i :\n", inet_ntoa(serv.sin_addr), htons(serv.sin_port));
    /*----------- Reception -----------*/
    while(1) {
        int l_mess;
        if((l_mess = recvfrom(sock, buffer, sizeof(buffer) - 1, MSG_WAITALL,(SOCKADDR *)&clt, &l_clt)) == RECV_ERROR)
            perror("error recvfrom");
        printf("Client : %s:%i\n", inet_ntoa(clt.sin_addr), ntohs(clt.sin_port));
        
        buffer[l_mess] = '\0';
        //Echo to client
        sendto(sock, buffer, strlen(buffer), MSG_CONFIRM, (SOCKADDR *)&clt, l_clt);
    }
    return 0;
}