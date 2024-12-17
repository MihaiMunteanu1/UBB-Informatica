#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>

int main() {
    int s;
    int l;
    struct sockaddr_in server, client;
    uint16_t nr,div[100];

    s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s < 0) {
        printf("Eroare la crearea socketului server\n");
        return 1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
        printf("Eroare la bind\n");
        return 1;
    }

    l = sizeof(client);
    memset(&client, 0, sizeof(client));
    while(1){
        recvfrom(s, &nr, sizeof(nr), 0, (struct sockaddr *) &client, &l);
        nr = ntohs(nr);
        uint16_t count=0;
        for(int i=1;i<=nr;i++){
            if(nr%i==0){
                    div[count++]=ntohs(i);
            }
        }
        count=ntohs(count);
        sendto(s, &count, sizeof(count), 0, (struct sockaddr *)&client, l);
        sendto(s, div, count * sizeof(uint16_t), 0, (struct sockaddr *)&client, l);
    }
    close(s);

}
