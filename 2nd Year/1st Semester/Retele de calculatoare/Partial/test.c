/*
Serverul va trimite acest enunt. Serverul asteapta apoi un numar care reprezinta lungimea enuntului. 
Apoi, pe aceeasi conexiune, serverul trimite un sir de caractere pe bucati. 
Fiecare bucata are maxim 255 de caractere, dar minimul nu este garantat. 
Dupa ce serverul a trimis tot sirul de caractere dorit, 
asteapta sa primeasca un numar care reprezinta lungimea totala a sirului trimis. 
Odata confirmat, serverul asteapta suma pozitiilor absolute din sir unde se gasesc litere mici sau mari.
*/
#include <sys/types.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>

char sir[1024];

int main() {
  int c;
  struct sockaddr_in server;
  uint16_t a=3576,lung_enunt;
  char *enunt;

  c = socket(AF_INET, SOCK_STREAM, 0);
  if (c < 0) {
    printf("Eroare la crearea socketului client\n");
    return 1;
  }

  memset(&server, 0, sizeof(server));
  server.sin_port = htons(8889);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");

  if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la conectarea la server\n");
    return 1;
  }

  a=htons(a);
  send(c, &a, sizeof(a), 0);

  recv(c, &lung_enunt, sizeof(lung_enunt), 0);
  lung_enunt=ntohs(lung_enunt);

  enunt=(char*)malloc(lung_enunt*sizeof(enunt));

  recv(c, enunt, lung_enunt*sizeof(enunt), 0);

  printf("%s\n",enunt);

  printf("%hu\n",lung_enunt);

  lung_enunt=htons(lung_enunt);

  send(c, &lung_enunt, sizeof(lung_enunt), 0);

  free(enunt);

  while(1){
        uint8_t lung;
        recv(c, &lung, sizeof(lung), 0);
        if(lung==0)
                break;

        char s[256];
        recv(c ,s, lung, 0);
        s[lung]='\0';
        strcat(sir,s);
  }
  sir[strlen(sir)]='\0';
  printf("%s\n",sir);

  uint16_t lung_sir=strlen(sir);
  printf("Lungime sir: %hu\n",lung_sir);

  lung_sir=htons(lung_sir);
  send(c, &lung_sir, sizeof(lung_sir), 0);

  int sumPoz=0;
  for(int i=0;i<strlen(sir);i++){
        if((sir[i]>='a' && sir[i]<='z') || (sir[i]>='A' && sir[i]<='Z'))
                sumPoz=sumPoz + i;
  }
  printf("Suma poz: %d\n",sumPoz);

  sumPoz=htonl(sumPoz);
  send(c, &sumPoz, sizeof(sumPoz), 0);

  close(c);
}
