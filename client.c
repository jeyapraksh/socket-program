#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[1024] = {0};

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);

    inet_pton(AF_INET, "127.0.0.1",
              &server_addr.sin_addr);

    connect(sock,
           (struct sockaddr*)&server_addr,
           sizeof(server_addr));

    send(sock, "Hello Server",
         strlen("Hello Server"), 0);

    recv(sock, buffer, sizeof(buffer), 0);

    printf("Server Reply: %s\n", buffer);

    close(sock);

    return 0;
}
