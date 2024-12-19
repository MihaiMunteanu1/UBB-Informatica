#pragma once
#include "Song.h"
#include <vector>
#include <algorithm>
#include <random>    // std::default_random_engine
#include <chrono>    // std::chrono::system_clock

using std::vector;
class Playlist {
private:
	vector<Melodie> playlistMelodies;
public:
	Playlist()=default;
	/*
	* Adauga o melodie in playlist
	* @param s: melodia care se adauga (Melodie)
	* 
	* post: melodia va fi adaugata la playlist
	*/
	void addMelodieToPlaylist(const Melodie& s);
	/*
	* Elimina toate melodiile din playlist
	* post: playlist-ul este gol
	*/
	void emptyPlaylist();
	/*
	* Adauga un numar random de melodii in playlist
	* 
	* @param originalMelodies: melodiile din care se alege (vector<Melodie>)
	* @param howMany: cate melodii se adauga (int)
	* 
	* post: melodiile sunt adaugate in playlist-ul curent
	*/
	void addRandomMelodies(vector<Melodie> originalMelodies, int howMany);
	/*
	* Returneaza un vector care contine toate melodiile din playlist
	*/
	const vector<Melodie>& getAllPlaylistMelodies();
};
