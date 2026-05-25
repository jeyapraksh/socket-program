#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[BUFFER_SIZE];
    int bytes;

    FILE *fp;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd,
         (struct sockaddr*)&server_addr,
         sizeof(server_addr));

    listen(server_fd, 5);

    printf("Waiting for client...\n");

    addr_size = sizeof(client_addr);

    client_fd = accept(server_fd,
                      (struct sockaddr*)&client_addr,
                      &addr_size);

    fp = fopen("received.txt", "w");

    while ((bytes = recv(client_fd, buffer,
                        BUFFER_SIZE, 0)) > 0) {

        fwrite(buffer, 1, bytes, fp);
    }

    printf("File Transfer Successful\n");

    fclose(fp);
    close(client_fd);
    close(server_fd);

    return 0;
}
