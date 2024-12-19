#include <assert.h>
#include <stdlib.h>
#include "melodie.h"

Melodie createMelodie(char* titlu, char* artist, double durata)
{
	Melodie m;
	size_t nrCaractereTitlu = strlen(titlu)+1;
	m.titlu = malloc(nrCaractereTitlu * sizeof(char));
	strcpy_s(m.titlu, nrCaractereTitlu, titlu);

	size_t nrCaractereArtist = strlen(artist) + 1;
	m.artist = malloc(nrCaractereArtist * sizeof(char));

	strcpy_s(m.artist, nrCaractereArtist, artist);
	m.durata = durata;
	return m;

}

void destroyMelodie(Melodie* m)
{
	free(m->artist);
	free(m->titlu);

	m->artist = NULL;
	m->titlu = NULL;
	m->durata = -1;
}

Melodie copyMelodie(Melodie* m)
{
	return createMelodie(m->titlu, m->artist, m->durata);
}

void testCreateDestroyMelodie() {
	Melodie m = createMelodie("When the Levee Breaks", "Led Zeppelin", 5.22);
	assert(strcmp(m.artist, "Led Zeppelin")==0);
	assert(strcmp(m.titlu, "When the Levee Breaks")==0);
	assert(m.durata == 5.22);

	destroyMelodie(&m);
	assert(m.titlu == NULL);
	assert(m.artist == NULL);
	assert(m.durata == -1);



}