#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

int main() {
    int c;
    struct sockaddr_in server;
    uint16_t nr;
    uint16_t count;

    c = socket(AF_INET, SOCK_DGRAM, 0);
    if (c < 0) {
        printf("Eroare la crearea socketului client\n");
        return 1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Numar: ");
    scanf("%hu", &nr);
    uint16_t n = htons(nr);
    sendto(c, &n, sizeof(n), 0, (struct sockaddr *)&server, sizeof(server));

    recvfrom(c, &count, sizeof(count), 0, NULL, NULL);
    count = ntohs(count);

    uint16_t div[count+1];
    recvfrom(c, div, count * sizeof(div), 0, NULL, NULL);

    printf("Divizorii: ");
    for (int i = 0; i < count; i++) {
        printf("%hu ", ntohs(div[i]));
    }
    printf("\n");

    close(c);
    return 0;
}
