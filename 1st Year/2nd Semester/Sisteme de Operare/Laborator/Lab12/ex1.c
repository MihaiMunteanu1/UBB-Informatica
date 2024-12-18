// Se dau 100000 de numere aleatoare. Folosind un număr potrivit de thread-uri și cele mai potrivite mecanisme de sincronizare, să se determine cea mai mică diferență dintre 2 numere din fiecare interval de 2000 de numere.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include <time.h>

#define MAX_NUM 100000
#define MAX_THR 50

//pthread_mutex_t mtx;

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

int numere[MAX_NUM];
int minDif = INT_MAX;

void * doDif(void* arg) {
	int id = *(int*)arg;
	free(arg);

	int st = id * MAX_NUM/MAX_THR;
	int dr = st + MAX_NUM/MAX_THR;

	int dif = INT_MAX;
	for (int i = st; i < dr - 1; i++) {
		for (int j = i + 1; j < dr; j++) {
			if (dif > abs(numere[i] - numere[j]))
				dif = abs(numere[i] - numere[j]);
		}
	}

	pthread_mutex_lock(&mtx);
	if (dif < minDif)
		minDif = dif;
	pthread_mutex_unlock(&mtx);

	return NULL;
}

int main(int argc, char** argv) {

	//generare 100000 numere aleatoare
	srand(time(NULL));

	for (int i = 0; i < MAX_NUM; i++) {
		numere[i] = rand();
	}

	// creez mutex
	//pthread_mutex_init(&mtx, NULL);

	pthread_t tid[MAX_THR];
	for (int i = 0; i < MAX_THR; i++) {
		int *id = malloc(sizeof(int));
		*id = i;
		pthread_create(&tid[i], NULL, doDif, id);
	}

	for (int i = 0; i < MAX_THR; i++) {
		pthread_join(tid[i], NULL);
	}

	printf("Diferenta minima: %d\n", minDif);

	// distrug mutex
	//pthread_mutex_destroy(&mtx);

	return 0;
}
