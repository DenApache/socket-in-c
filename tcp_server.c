#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>


int main(void){
    int network_socket;
    int connection_status;
    char server_response[256];
    network_socket = socket(AF_INET, SOCK_STREAM, 0); 
    
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9000);
    server_address.sin_addr.s_addr = INADDR_ANY;

    connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    //check for error
    if (connection_status == -1){
        printf("There was an error making a connection to the remote socket \r\n\n");
    }
    //recieve data from server
    recv(network_socket, &server_response, sizeof(server_response), 0);

    //print server response
    printf("The server sent the data : %s", server_response);

    close(network_socket);

    return 0;
}