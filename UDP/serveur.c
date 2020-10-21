#include "../utils.h"

int main(int argc, char *argv[]){

    check_args_server(argc, argv);
    PORT port = atoi(argv[1]);

    SOCKET sock = create_socket();

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

    printf("Start listening %s:%i :\n\n", inet_ntoa(serv.sin_addr), htons(serv.sin_port));
    /*----------- Reception -----------*/
    while(1) {
        int l_mess;
        if((l_mess = recvfrom(sock, buffer, sizeof(buffer) - 1, MSG_WAITALL,(SOCKADDR *)&clt, &l_clt)) == RECV_ERROR)
            perror("error recvfrom");
        
        display_log();
        printf(" %s:%i\n", inet_ntoa(clt.sin_addr), ntohs(clt.sin_port));
        
        buffer[l_mess] = '\0';
        //Echo to client
        sendto(sock, buffer, strlen(buffer), MSG_CONFIRM, (SOCKADDR *)&clt, l_clt);
    }
    return 0;
}