#include "../utils.h"


int main(int argc, char** argv){
    //checks the validity of the arguments
    check_args_client(argc, argv);
    
    //declare the socket
    SOCKET network_socket;
    
    //Get tcp port
    PORT port = atoi(argv[2]);
    
    int connection_status;
    char server_response[256];
    char message[256];

    
    struct addrinfo hints, *serv_addr; 
    memset(&hints, 0, sizeof(hints)); //CLear the structure hints
    hints.ai_family = AF_UNSPEC; // Both IPV4 and IPV6 addresses 
    hints.ai_socktype = SOCK_STREAM; // Type of socket SOCK_STREAM for TCP conneciton
    getaddrinfo(argv[1], argv[2], &hints, &serv_addr); // Identify remote host with hints info, port and hostname(or IP address) 
     
    
    //Get client message
    strcpy(message,argv[3]);

    //Create the socket and checks if there is an error
    printf("%d\n",serv_addr->ai_socktype);
    if ((network_socket = socket(serv_addr->ai_family, serv_addr->ai_socktype, 0)) == INVALID_SOCKET){
        perror("error create socket");
        return 1;
    }
    
    struct addrinfo *server_address = serv_addr;

    // Open TCP connection
    connection_status = connect(network_socket, server_address->ai_addr, server_address->ai_addrlen);
    //checks for error
    if (connection_status == -1){
        perror("There was an error making a connection to the remote host\n");
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