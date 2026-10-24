#include <iostream>
#include <stdlib.h>
#include "Song.h"
using namespace std;

Song::Song(int id, string title, int dur, string artist_p){
	songId = id;
	songTitle = title;
	duration = dur;
	artist = artist_p;
}

Song::Song(){
	songId = 0;
	songTitle = "";
	duration = 0;
	artist = "";
}

Song& Song:: operator=(const Song& copy){
	if(this != &copy){
		this->songId = copy.songId;
		this->songTitle = copy.songTitle;
		this->duration = copy.duration;
		this->artist = copy.artist;

	}
	return *this;
}
Song::~Song(){
}

int Song::getSongId(){
	return songId;
}
string Song::getSongTitle(){
	return songTitle;
}
string Song::getArtist(){
	return artist;
}
