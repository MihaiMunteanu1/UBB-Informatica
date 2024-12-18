#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define MAX_SIZE 100

int main(int argc,char* argv[]){
	char sir[]="aeiouBAEIOUC";
	char vocale[]="aeiouAEIOU";

	for(int i=0;i<strlen(sir);i++)
	{
		//deschid FIFO pentru scriere
		int pd=open("fifo1",O_WRONLY);
		if(pd<0){
			perror("open");
			exit(1);
		}

		//scriu vocala si sirul curent
		write(pd,&vocale[i],sizeof(char));
		sleep(1);
		write(pd,sir,MAX_SIZE);
		sleep(2);
		close(pd);

		//deschid FIFO pentru citire
                pd=open("fifo1",O_RDONLY);
                if(pd<0){
                        perror("open");
                        exit(1);
                }

		//citesc sirul primit
		char *tmp=malloc(MAX_SIZE*sizeof(char));
		read(pd,tmp,MAX_SIZE);
		strcpy(sir,tmp);
		printf("Sir: %s\n",sir);

		close(pd);
	}

	return 0;
}
