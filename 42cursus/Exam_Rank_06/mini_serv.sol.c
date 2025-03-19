#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

typedef struct client
{
    int id;
    char msg[10000];
} cli;

cli clients[2048];
fd_set read_set, write_set, active_set;
int max_fd = 0;
int next_id = 0;
char send_bf[120000], recv_bf[120000];

void err(char *msg)
{
    if (msg)
        write(2, msg, strlen(msg));
    else
        write(2, "Fatal error", 11);
    write(2, "\n", 1);
    exit(1);
}

void broadcast(int sender_fd, int server_socket)
{
    for (int fd = 0; fd <= max_fd; fd++){
        if (fd != server_socket && FD_ISSET(fd, &write_set) && fd != sender_fd)
            if (send(fd, send_bf, strlen(send_bf), 0) < 0)
                err(NULL);
    }
}

void handle_connection(int server_socket)
{
    struct sockaddr_in client_socket;
    socklen_t len = sizeof(client_socket);
    int client_fd = accept(server_socket, (struct sockaddr *)&client_socket, &len);

    if (client_fd < 0)
        return;

    FD_SET(client_fd, &active_set);
    if (client_fd > max_fd)
        max_fd = client_fd;

    clients[client_fd].id = next_id++;
    sprintf(send_bf, "server: client %d just arrived\n", clients[client_fd].id);
    broadcast(client_fd, server_socket);
}

void handle_msg(int client_fd, int server_socket)
{
    int bytes_received = recv(client_fd, recv_bf, sizeof(recv_bf), 0);

    if (bytes_received < 0)
        return;
    else if (bytes_received == 0){
        sprintf(send_bf, "server: client %d just left\n", clients[client_fd].id);
        broadcast(client_fd, server_socket);
        FD_CLR(client_fd, &active_set);
        close(client_fd);
        memset(clients[client_fd].msg, 0, sizeof(clients[client_fd].msg));
    }
    else{
        for (int i = 0, j = strlen(clients[client_fd].msg); i < bytes_received; i++, j++){
            clients[client_fd].msg[j] = recv_bf[i];
            if (clients[client_fd].msg[j] == '\n') {
                clients[client_fd].msg[j] = '\0';
                sprintf(send_bf, "client %d: %s\n", clients[client_fd].id, clients[client_fd].msg);
                broadcast(client_fd, server_socket);
                memset(clients[client_fd].msg, 0, sizeof(clients[client_fd].msg));
                j = -1;
            }
        }
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
        err("Wrong number of arguments");

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
        err(NULL);
    
    max_fd = server_socket;

    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    server_addr.sin_port = htons(atoi(argv[1]));

    if (bind(server_socket, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0 || listen(server_socket, 100) < 0)
        err(NULL);

    FD_ZERO(&active_set);
    FD_SET(server_socket, &active_set);
    memset(clients, 0, sizeof(clients));

    while (1){
        read_set = active_set;
        write_set = active_set;

        if (select(max_fd + 1, &read_set, &write_set, NULL, NULL) < 0) 
            continue;

        for (int fd = 0; fd <= max_fd; fd++){
            if (FD_ISSET(fd, &read_set))
            {
                if (fd == server_socket)
                    handle_connection(server_socket);
                else
                    handle_msg(fd, server_socket);
            }
        }
    }
    return (0);
}
