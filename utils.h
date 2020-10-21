#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <time.h>


typedef int SOCKET;
typedef int PORT;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define RECV_ERROR -1
#define SND_ERROR -1
#define INVALID_PARAM -2
#define PORT_REGEX "[0-9]{4,5}"

void check_args_server(int n, char** args);

int check_args_client(int n, char** args);

void display_log();