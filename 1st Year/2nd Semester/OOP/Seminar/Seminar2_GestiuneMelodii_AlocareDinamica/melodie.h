#pragma once
#include <string.h>

typedef struct {
	char* titlu;
	char* artist;
	double durata;
} Melodie;

///<summary>Creeaza o melodie</summary>
///<param name="titlu">Titlul melodiei (sir de caractere)</param>
///<param name="artist">Artistul melodiei (sir de caractere)</param>
///<param name="durata">Durata melodiei</param>
///<returns>Returneaza melodia creata</returns>
Melodie createMelodie(char* titlu, char* artist, double durata);


///<summary>Distruge melodie</summary>
///<param name="m">Melodia care va fi distrusa</param>
void destroyMelodie(Melodie* m);

/// <summary>
/// Creeaza o noua melodie pe baza melodiei date
/// </summary>
/// <param name="m">melodia care se copiaza (Melodie*)</param>
/// <returns>copie a melodiei (Melodie)</returns>
Melodie copyMelodie(Melodie* m);


void testCreateDestroyMelodie();