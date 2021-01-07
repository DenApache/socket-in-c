#include "../utils.h"


void *handle_client(void *pclient);

int main(int argc, char** argv){
    //checks the validity of the arguments
    check_args_server(argc, argv);
    PORT port = atoi(argv[1]);
    SOCKET server_socket;
    SOCKET client_socket;
    

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
    while (1){
        //Declare a new client structure
        client_t* client = malloc(sizeof(client_t));
        //Accept a new connection from a client
        client_socket = accept(server_socket, (struct sockaddr *) &new_client, &new_client_size);

        client->socket = client_socket;
        client->address = new_client;
        //Get the client's hotsname
        getnameinfo((struct sockaddr *) &new_client, new_client_size, client->hostname, 64-1, NULL, 0,0);    
        
        //New thread for each client with client structure in param
        pthread_t t;
        pthread_create(&t, NULL, handle_client, (void*) client);

    }
    // Close the server socket
    close(server_socket);
    return 0;
}

void* handle_client(void* pclient){
    client_t* client = (client_t*) pclient;
    display_log();
    printf("New connection from %s (%s)\n", inet_ntoa(client->address.sin_addr),client->hostname);
    char client_message[256];
    bzero(client_message, 256);
    
    //While the client steel connected, get the client's message
    while (recv(client->socket,client_message, sizeof(client_message),0)!=0){
    
        //Display client message
        display_log();
        printf("Receive from %s (%s) : %s\n", inet_ntoa(client->address.sin_addr),client->hostname, client_message);
        
        //Sends the message receveid from the client
        display_log();
        printf("Sent to %s (%s) : %s\n", inet_ntoa(client->address.sin_addr),client->hostname, client_message);
        send(client->socket, client_message, sizeof(client_message),0);

        // Clear the buffer of client_message
        bzero(client_message, 256);
    }
    close(client->socket);
    free(client);
    pthread_exit(NULL);
}