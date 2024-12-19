#include "Playlist.h"
using std::shuffle;

void Playlist::addMelodieToPlaylist(const Melodie& s) {
	this->playlistMelodies.push_back(s);
}
void Playlist::emptyPlaylist() {
	this->playlistMelodies.clear();
}

void Playlist::addRandomMelodies(vector<Melodie> originalMelodies, int howMany) {
	shuffle(originalMelodies.begin(), originalMelodies.end(), std::default_random_engine(std::random_device{}())); //amesteca vectorul v
	while (playlistMelodies.size() < howMany && originalMelodies.size() > 0) {
		playlistMelodies.push_back(originalMelodies.back());
		originalMelodies.pop_back();
	}
}
const vector<Melodie>& Playlist::getAllPlaylistMelodies() {
	return this->playlistMelodies;
}