#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>


// 3. Se dă un fișier care conține un text (șiruri de caractere separate prin spații).
// Fie P(i) procesul care determină frecvența de apariție a literei i într-un text dat.
// Folosind un număr adecvat de astfel de procese, să se scrie un program care afișează frecvența de apariție a fiecarei litere.
int main(int argc, char** argv)
{
	// am definit aici textul (nu l-am citit din fisier)
	char text[] = "Aa bBbB cccCCC";

	for(char ch = 'a'; ch <= 'z'; ch++)
	{
		int pd[2];
		if(pipe(pd) < 0)
		{
			perror("pipe()");
			exit(EXIT_FAILURE);
		}

		// creez procesul copil P(i)
		int pid = fork();
		if(pid == -1)
		{
			perror("fork()");
			exit(EXIT_FAILURE);
		}

		// in procesul copil P(i)
		if(pid == 0)
		{
			close(pd[0]);

			int count_small = 0;
			int count_upper = 0;
			for(int j = 0; j < strlen(text); j++)
				if(text[j] == ch)
					count_small++;
				else
					if (text[j] == toupper(ch))
						count_upper++;

			int count = count_small + count_upper;
			write(pd[1], &count, sizeof(int));

			close(pd[1]);
			exit(EXIT_SUCCESS);
		}

		// in procesul parinte
		close(pd[1]);

		int count = 0;
		read(pd[0], &count, sizeof(int));
		printf("%c: %d\n", ch, count);

		close(pd[0]);
		wait(NULL);
	}

	return 0;
}
