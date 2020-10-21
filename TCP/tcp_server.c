// #include<stdio.h>
// #include<stdlib.h>
// #include<sys/types.h>
// #include<sys/socket.h>
// #include<netinet/in.h>
// #include<unistd.h>
#include "../utils.h"


int main(int argc, char** argv){    
    int port = check_args_server(argc, argv);
    char server_message[256] = "You have reached the server \n";
    int server_socket;
    int client_socket;

    //create the server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    //define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    listen(server_socket, 5);

    client_socket = accept(server_socket, NULL, NULL);

    send(client_socket, server_message, sizeof(server_message),0);

    close(server_socket);
    return 0;
}