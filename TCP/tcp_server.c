#include "../utils.h"


int main(int argc, char** argv){

    //checks the validity of the arguments
    check_args_server(argc, argv);

    PORT port = atoi(argv[1]);
    SOCKET server_socket;
    SOCKET client_socket;
    char client_message[256];
    bzero(client_message, 256);

    //create the server socket and checks if there is an error
    if((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET){
        perror("error create socket");
        return 1;
    }

    //define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;

    //define client adress
    struct sockaddr_in new_client;
    socklen_t new_client_size = sizeof(new_client);

    display_log();
    printf("TCP Server starts\n");

    //Bin the socket
    if ((bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)))==SOCKET_ERROR){
        perror("error bind");
        return 2;
    }

    //Listening on port $port
    listen(server_socket, 5);
    display_log();
    printf("Listening on port %d...\n", port);

    //As long there is a client in the queue
    while ((client_socket = accept(server_socket, (struct sockaddr *) &new_client, &new_client_size)) > 0 ){
        //Get the client's hotsname
        char hostname[64];
        bzero(hostname, 64);
        getnameinfo((struct sockaddr *) &new_client, new_client_size, hostname, 64-1, NULL, 0,0);
        

        //New connection from a client
        display_log();
        printf("New connection from %s : %s\n", inet_ntoa(new_client.sin_addr),hostname);

            //While the client steel connected, get the client's message
            while (recv(client_socket,client_message, sizeof(client_message),0)!=0){
        
            //Display client message
            display_log();
            printf("Receive from %s (%s) : %s\n", inet_ntoa(new_client.sin_addr),hostname, client_message);
            
            //Sends the message receveid from the client
            display_log();
            printf("Sent to %s (%s) : %s\n", inet_ntoa(new_client.sin_addr),hostname, client_message);
            send(client_socket, client_message, sizeof(client_message),0);

            // Clear the buffer of client_message
            bzero(client_message, 256);
            }
        }
    // Close the server socket
    close(server_socket);
    return 0;
}