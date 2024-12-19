#pragma once
#include "mylist.h"
#include "validator.h"
//Va trebui sa avem lista de undo in Lab 5
//ne este util daca creem o structura de service
//pentru moment este doar lista de melodii
//ulterior aici punem si lista de undo

typedef struct {
	List listaMelodii;
} ManagerMelodii;

/// <summary>
/// Creeaza un manager de melodii 
/// </summary>
/// <returns>manager-ul de melodii creat (ManagerMelodii)</returns>
ManagerMelodii createManagerMelodii();

/// <summary>
/// Adauga melodie
/// </summary>
/// <param name="lista">manager-ul de melodii (ManagerMelodii*)</param>
/// <param name="titlu">titlul melodiei (sir de caractere)</param>
/// <param name="artist">artistul melodiei (sir de caractere)</param>
/// <param name="durata">durata melodiei (double)</param>
/// <returns>Cod 0..3 care semnaleaza succesul sau esecul operatiei de adaugare</returns>
int adaugaMelodie(ManagerMelodii* lista, char* titlu, char* artist, double durata);

/// <summary>
/// Creeaza o noua lista cu melodiile ale caror artisti
/// contin sirul de caractere dat 
/// </summary>
/// <param name="lista">manager-ul de melodii (ManagerMelodii)</param>
/// <param name="artist">sirul de caractere care va fi cautat in artistii melodiilor din lista (sir de caractere)</param>
/// <returns>o lista care contine doar melodiile care respecta conditia (List)</returns>
/// 
List filtreazaMelodie(ManagerMelodii* lista, char* artist);

/// <summary>
/// Distruge tot ce tine de manager-ul de melodii
/// </summary>
/// <param name="">manager-ul care va fi distrus (ManagerMelodii*)</param>
void destroyManager(ManagerMelodii* manager);

void testAddService();
void testFiltrareService();

