#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>

int main() {
  int c;
  struct sockaddr_in server;
  uint16_t a,div;

  c = socket(AF_INET, SOCK_STREAM, 0);
  if (c < 0) {
    printf("Eroare la crearea socketului client\n");
    return 1;
  }

  memset(&server, 0, sizeof(server));
  server.sin_port = htons(53576);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("172.30.240.4");

  if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la conectarea la server\n");
    return 1;
  }

  printf("Numar = ");
  scanf("%hu", &a);
  a = htons(a);
  send(c, &a, sizeof(a), 0);
  printf("Sirul divizorilor este: ");
  while(recv(c,&div, sizeof(div), MSG_WAITALL)){
        div=ntohs(div);
        printf("%hu ",div);
  }
  printf("\n");
  close(c);
}
