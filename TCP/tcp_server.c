// #include<stdio.h>
// #include<stdlib.h>
// #include<sys/types.h>
// #include<sys/socket.h>
// #include<netinet/in.h>
// #include<unistd.h>
#include "../utils.h"


int main(int argc, char** argv){
    
    
    //checks the validity of the arguments     
    check_args_server(argc, argv);

    PORT port = atoi(argv[1]);
    SOCKET server_socket;
    SOCKET client_socket;
    char server_message[256] = "You have reached the server \n";

    //create the server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    //define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;

    display_log();
    printf("TCP Server starts\n");
    bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    display_log();
    printf("Listening...\n");
    listen(server_socket, 5);
    while (1){
        client_socket = accept(server_socket, NULL, NULL);    
        display_log();
        printf("New client in \n");
        send(client_socket, server_message, sizeof(server_message),0);
    }

    close(server_socket);
    return 0;
}