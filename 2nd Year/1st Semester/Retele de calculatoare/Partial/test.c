#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
Serverul va trimite acest enunt. Serverul asteapta apoi un numar care reprezinta lungimea enuntului. 
Apoi, pe aceeasi conexiune, serverul trimite un sir de caractere pe bucati. 
Fiecare bucata are maxim 255 de caractere, dar minimul nu este garantat. 
Dupa ce serverul a trimis tot sirul de caractere dorit, 
asteapta sa primeasca un numar care reprezinta lungimea totala a sirului trimis. 
Odata confirmat, serverul asteapta suma pozitiilor absolute din sir unde se gasesc litere mici sau mari.
*/
char sir[1024];
int main() {
        int c = socket(AF_INET, SOCK_STREAM, 0);
        if (c < 0) {
                printf("socket err.");
                return 1;
        }
        struct sockaddr_in server;
        memset(&server, 0, sizeof(server));
        server.sin_port = htons(8889);
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr("172.30.240.4");
        if (connect(c, (struct sockaddr*) &server, sizeof(server)) < 0) {
                printf("connect err.");
                return 1;
        }
        short int id = 34784;
	short int lg;
	char* cerinta;
	id = htons(id);
	send(c, &id, sizeof(id), 0);
	recv(c, &lg, sizeof(lg), 0);
	send(c, &lg, sizeof(lg), 0);
	lg = ntohs(lg);
	cerinta = malloc(lg * sizeof(char));
	recv(c, cerinta, lg * sizeof(char), 0);
	
        printf("%s\n", cerinta);
	free(cerinta);
		
	while (1) {
		char s[256];
		uint8_t lg;
		recv(c, &lg, sizeof(lg), 0);
		if (lg == 0)
			break;
		recv(c, s, lg, 0);
		s[lg] = '\0';
		strcat(sir, s);
	}

	sir[strlen(sir)] = '\0';

	int sumaPoz = 0;
	int nrlitere = 0;
	for (int i = 0; i < strlen(sir); i++)
		if ((sir[i] >= 'a' && sir[i] <= 'z') || (sir[i] >= 'A' && sir[i] <= 'Z'))
		{
			sumaPoz += i;
			nrlitere++;
		}
	
	printf("%s\n%d\n", sir, nrlitere);
	printf("%d %d\n", strlen(sir), sumaPoz); 
	uint16_t poz = strlen(sir);
	poz = htons(poz);
	send(c, &poz, sizeof(poz), 0);
	sumaPoz = htonl(sumaPoz);
	send(c, &sumaPoz, sizeof(sumaPoz), 0);
	close(c);
        return 0;
}
