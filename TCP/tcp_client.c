#include "../utils.h"


int main(int argc, char** argv){
    //checks the validity of the arguments
    check_args_client(argc, argv);
    
    
    SOCKET network_socket;
    PORT port = atoi(argv[2]);
    int connection_status;
    char server_response[256];
    char message[256];

    //Get client message
    strcpy(message,argv[3]);

    //Create the socket and checks if there is an error
    if ((network_socket = socket(AF_INET6, SOCK_STREAM, 0)) == INVALID_SOCKET){
        perror("error create socket");
        return 1;
    }
    
    //define client socket
    SOCKADDR_IN6 server_address;
    server_address.sin6_family = AF_INET6;
    server_address.sin6_port = htons(port);
    if (!inet_pton(AF_INET6, argv[1], &server_address.sin6_addr)){
        inet_pton(AF_INET, argv[1], &server_address.sin6_addr);
    }

    //Open the connection with the remote server
    connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    
    //checks for error
    if (connection_status == -1){
        printf("There was an error making a connection to the remote socket\n");
        return 1;
    }

    display_log();
    printf("Connection etablished with %s on port %d\n", argv[1], port);
    //Sends a message to the server
    send(network_socket,message, sizeof(message), 0);
    display_log();
    printf("Sent to %s : %s\n", argv[1], message);
    
    //recieve data from server
    recv(network_socket, &server_response, sizeof(server_response), 0);
    //print server response
    display_log();
    printf("Receive from %s : %s\n", argv[1], server_response);

    // Close the socket
    close(network_socket);
    return 0;
}