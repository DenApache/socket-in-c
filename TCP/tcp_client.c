#include "../utils.h"


int main(int argc, char** argv){
    //checks the validity of the arguments
    check_args_client(argc, argv);

    SOCKET network_socket;
    PORT port = atoi(argv[2]);
    int connection_status;
    char server_response[256];
    char message[256];
    strcpy(message,argv[3]);
    network_socket = socket(AF_INET, SOCK_STREAM, 0); 
    
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = inet_addr(argv[1]);

    connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    //check for error
    if (connection_status == -1){
        printf("There was an error making a connection to the remote socket\n");
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

    close(network_socket);

    return 0;
}