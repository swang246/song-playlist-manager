#include <iostream>
#include <stdlib.h>
#include "SongCollection.h"
using namespace std;

SongCollection::SongCollection(){
	list = new Song[2];
	space = 1;
	currSize = space;
	songName = "";
	songId = 0;
}

SongCollection::SongCollection(const SongCollection& copy){
	space = copy.space;
	currSize = copy.currSize;
	list = new Song[space];
	for (int i = 0; i < currSize; i++) {
		list[i] = copy.list[i];
	}
}

SongCollection& SongCollection:: operator=(const SongCollection& copy){
	if(this != &copy){
		currSize = copy.currSize;
		space = copy.space;
		delete[] list;
		list = new Song[space];
		for(int i = 0; i < currSize; i++){
			list[i] = copy.list[i];
		}
	}
	return *this;
}
SongCollection::~SongCollection(){
	delete[] list;
}
int SongCollection::getCurrSize(){
	return currSize - space;
}
int SongCollection::getSpace(){
	return space;
}
string SongCollection::getSongName(){
	return songName;
}
int SongCollection::getSongId(){
	return songId;
}
void SongCollection::setSongName(string n){
	songName = n;
}
void SongCollection::setSongId(int i){
	songId = i;
}
void SongCollection::resize(){
	space = space + currSize;

	currSize = currSize * 2;
	Song* newList = new Song[currSize];
	for (int i = 0; i < currSize/2; ++i) {
		newList[i] = list[i];
	}
	delete[] list;
	list = newList;
}
void SongCollection::add(Song s){
	if(space <= 0){
		resize();
	}
	int location = 0;
	bool greatest = true;
	for(int i = 0; i < currSize/2; i++){
		if(list[i].getSongId() > s.getSongId()){
			location = i;
			greatest = false;
			i = i + currSize/2;
		}
	}
	if(greatest){
		location = currSize - space;
	}
	else if(currSize > 1){
		int a = currSize - space - 1;
		while(a >= location){
			list[a + 1] = list[a];
			a--;
		}
	}
	list[location] = s;
	space--;
}
void SongCollection::removeBySong(Song s){
	if(currSize == 1){
		space = 1;
		return;
	}
	int location = -1;
	for(int i = 0; i < currSize; i++){
		if(list[i].getSongId() == s.getSongId()){
			location = i;
			break;
		}
	}
	if(location != -1){
		int i = location;
		while(i < currSize-1){
			list[i] = list[i + 1];
			i++;
        	}
        currSize--;
        }
}
void SongCollection::removeByIndex(int i){ 
	if(currSize == 1 && i == 0){
		space = 1;
		return;
	}
	while(i < currSize-space-1){
		list[i] = list[i + 1];
		i++;
	}
	space++;
}
Song SongCollection::at(int i){
	return list[i];
}
bool SongCollection::exists(Song s){
	for(int i = 0; i < currSize-space; i++){
		if(list[i].getSongId() == s.getSongId()){
			return true;
		}
	}
	return false;
}
