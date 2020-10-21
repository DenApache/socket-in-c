#include "../utils.h"

SOCKET create_socket(){
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock == INVALID_SOCKET){
        perror("error create socket");
        exit(-1);
    }
    return sock;
}

int main(int argc, char *argv[]){

    if(argc != 4){
        fprintf(stderr, "Usage : %s HOST PORT MESSAGE\n", argv[0]);
        exit(INVALID_PARAM);
    }
    
    regex_t reg;
    regcomp(&reg, PORT_REGEX, REG_NOSUB | REG_EXTENDED);

    if(regexec(&reg, argv[2], 0, NULL, 0)){
        fprintf(stderr,"Invalid port\n");
        exit(INVALID_PARAM);
    }
    regfree(&reg);

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
    printf("Message sent\n");

    if( (l_mess = recvfrom(sock, buffer, BUFSIZ, MSG_WAITALL, (SOCKADDR *) &serv, &l_serv)) == RECV_ERROR)
        perror("error recvfrom");
    buffer[l_mess] = '\0';
    printf("Server : %s\n",buffer);

    close(sock);
    return 0;

}