#include "../utils.h"


int main(int argc, char *argv[]){

    check_args_client(argc, argv);
    PORT port = atoi(argv[2]);

    SOCKET sock = create_socket();
    char *message = argv[3];
    char buffer[BUFSIZ];
    
    SOCKADDR_IN serv = {0};
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr(argv[1]) ;
    serv.sin_port = htons(port);

    u_int32_t l_serv;
    int l_mess;

    if(sendto(sock, message, strlen(message),MSG_CONFIRM, (SOCKADDR *) &serv, sizeof(serv))== -1)
        perror("error sendto");

    if( (l_mess = recvfrom(sock, buffer, BUFSIZ, MSG_WAITALL, (SOCKADDR *) &serv, &l_serv)) == RECV_ERROR)
        perror("error recvfrom");
    buffer[l_mess] = '\0';
    display_log();
    printf("echo : %s\n",buffer);

    close(sock);
    return 0;

}