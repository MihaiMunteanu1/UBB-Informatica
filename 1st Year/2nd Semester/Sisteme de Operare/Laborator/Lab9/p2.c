#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#define MAX_SIZE 100

int main(int argc,char* argv[]){
        while(true)
        {
                //deschid FIFO pentru citire
                int pd=open("fifo1",O_RDONLY);
                if(pd<0){
                        perror("open");
                        exit(1);
                }

                //scriu vocala si sirul curent
                char vocala;
		read(pd,&vocala,sizeof(char));
		char* sir=malloc(MAX_SIZE*sizeof(char));
                write(pd,sir,MAX_SIZE);
		sleep(3);
                close(pd);

		//prelucrez sirul
		int j=0;
		char *tmp=malloc(MAX_SIZE*sizeof(char));
		for(int i=0;i<strlen(sir);i++){
			if(sir[i]!=vocala)
				tmp[j++]=sir[i];
		}
		tmp[j]='\0';

                //deschid FIFO pentru scriere
                pd=open("fifo1",O_WRONLY);
                if(pd<0){
                        perror("open");
                        exit(1);
                }

                //scriu sirul obtinut
		write(pd,tmp,MAX_SIZE);
                printf("Sir: %s\n",sir);
            	free(tmp);
		close(pd);
        }

        return 0;
}
