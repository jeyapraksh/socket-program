#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[1024];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr*)&server_addr,
         sizeof(server_addr));

    listen(server_fd, 5);

    printf("Waiting for client...\n");

    addr_size = sizeof(client_addr);

    client_fd = accept(server_fd,
                      (struct sockaddr*)&client_addr,
                      &addr_size);

    printf("Client Connected: %s\n",
           inet_ntoa(client_addr.sin_addr));

    while (1) {

        memset(buffer, 0, sizeof(buffer));
        recv(client_fd, buffer, sizeof(buffer), 0);

        printf("[Client]: %s", buffer);

        if (strncmp(buffer, "exit", 4) == 0)
            break;

        printf("[Server]: ");
        fgets(buffer, sizeof(buffer), stdin);

        send(client_fd, buffer, strlen(buffer), 0);

        if (strncmp(buffer, "exit", 4) == 0)
            break;
    }

    close(client_fd);
    close(server_fd);

    return 0;
}
