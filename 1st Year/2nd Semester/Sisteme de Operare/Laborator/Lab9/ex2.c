#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


// 2. Se dă un fișier ce conține primele N numere naturale în ordine crescătoare.
// Fie P(i) procesul care elimină toți multiplii lui i cuprinși între 2 și N.
// Folosind un număr adecvat de astfel de procese, să se scrie un program care determină toate numerele prime cuprinse între 1 și N dat.
int main(int argc, char *argv[])
{
	int N = 20;
	for(int i = 2; i < N/2; i++)
	{
		int pid = fork();
		if(pid == -1)
		{
			perror("fork()");
			exit(EXIT_FAILURE);
		}

		// in procesul copil
		if(pid == 0)
		{
			// deschid fisierul pentru citire
			FILE* fd = fopen("numere","r");
			if(fd == NULL)
			{
				perror("fopen()");
				exit(EXIT_FAILURE);
			}

			int k = 0;
			int num = 0;
			int *numere = malloc(N * sizeof(int));
			while(fscanf(fd, "%d", &num) > 0)
				if((num % i) != 0 || num == i)
					numere[k++] = num;

			fclose(fd);

			// redeschid fisierul pentru scriere
            fd = fopen("numere","w");
            if(fd == NULL)
            {
                perror("fopen()");
                exit(EXIT_FAILURE);
            }

			for(int j = 0; j < k; j++)
				fprintf(fd, "%d ", numere[j]);

			fclose(fd);
			free(numere);

			exit(EXIT_SUCCESS);
		}

		// in procesul parinte
		wait(NULL);

	}

	return 0;
}
