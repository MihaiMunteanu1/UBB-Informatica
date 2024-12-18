#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_SIZE 100

// 1. Se dă un șir de litere. Folosind câte un proces pentru fiecare vocală,
// să se elimine toate vocalele din acest șir.
int main(int argc, char *argv[])
{
	char sir[] = "aeioubAEIOUC";

	char vocale[] = "aeiouAEIOU";
	for (int i = 0; i < strlen(vocale); i++)
	{
		int pd[2];
		if (pipe(pd) == -1)		// deschid pipe
		{
			perror("pipe()");
			exit(EXIT_FAILURE);
		}

		int pid = fork();		// creez proces copil
		if (pid == -1)
		{
			perror("fork()");
			exit(EXIT_FAILURE);
		}

		// in procesul copil
		if (pid == 0)
		{

			close(pd[0]);		// inchid capatul de citire

			int k = 0;
			char* tmp = malloc(MAX_SIZE * sizeof(char));
			for (int j = 0; j < strlen(sir); j++)
			{
				if (sir[j] != vocale[i])
					tmp[k++] = sir[j];
			}
			tmp[k] = '\0';
			write(pd[1], tmp, MAX_SIZE);

			close(pd[1]);
			free(tmp);
			exit(EXIT_SUCCESS);
		}

		// in procesul parinte
		close(pd[1]);			// inchid capatul de scriere

		char *tmp = malloc(MAX_SIZE * sizeof(char));
		read(pd[0], tmp, MAX_SIZE);

		strcpy(sir, tmp);		// suprascriu sirul initial

		close(pd[0]);
		free(tmp);
		wait(NULL);				// astept terminarea procesului copil
	}

	printf("Sir final: %s\n", sir);
	return 0;
}
