#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>

#include "SongCollection.h"

using namespace std;

bool isInteger(const std::string& s) {
	try {
		std::stoi(s);
		return true;
	} 
	catch (const std::invalid_argument& e) {
		return false;
	} 
	catch (const std::out_of_range& e) {
		return false;
	}
}
bool inList(SongCollection* s, int id){
	for(int i = 0; i < s->getCurrSize(); i++){
		if(s->at(i).getSongId() == id){
			return true;
		}
	}
	return false;
}
bool inCollection(vector<SongCollection*> s, int id){
	for(int i = 0; i < s.size(); i++){
		if(s.at(i)->getSongId() == id){
			return true;
		}
	}
	return false;
}

int main(int argc, char *argv[]){
	string input;
	vector<string> words;
	
	SongCollection* songs = new SongCollection();
	vector<SongCollection*> playlists;
	cout << "Input command: " << endl;
	cout << ": ";
	
	while(getline(cin, input)) {
		if(input == "quit"){
			return 0;
		}
		int position = 0;
		input += " ";
		while((position = input.find(" ")) != -1){
			string word = input.substr(0, position);
			if(word.front() == '\"'){
				size_t closingPair = input.find('\"', 1);
				if(closingPair != -1){
					word = input.substr(1, closingPair - 1);
					input.erase(0, closingPair + 2);
				}
			}
			else{
				input.erase(0, position + 1);
			}
			words.push_back(word);
		}
		if(words[0] == "song"){
			if((int)words.size() < 5){
				cout << "Too few arguments" << endl;
				cout << ": ";
			}
			else if(isInteger(words[1]) == false){
				cout << "song id " << words[1] << " is not an integer" << endl;
				cout << ": ";
			}
			else if(isInteger(words[3]) == false){
				cout << "duration " << words[3] << " is not an integer" << endl;
				cout << ": ";
			}
			else{
				bool check = inList(songs, stoi(words[1]));
				
				if(check){
					int pos = 0;
					for(int i = 0; i < songs->getCurrSize(); i++){
						if(songs->at(i).getSongId() == stoi(words[1])){
							pos = i;
						} 
					}
					cout << "song id " << words[1] << " already used for " << songs->at(pos).getSongTitle() << " by " << songs->at(pos).getArtist() << endl;
					cout << ": ";
				}
				else{
					int min = stoi(words[3]) / 60;
					int sec = stoi(words[3]) % 60;
					cout << "new song " << words[1] << " " << words[4] << " by " << words[2] << " " << min << ":";
					if(sec < 10){
						cout << "0" << sec << endl;
					}
					else{
						cout << sec << endl;
					}
					Song a(stoi(words[1]), words[4], stoi(words[3]), words[2]);
					songs->add(a);
					//cout<< "CHECK: Size of songs: " << songs->getCurrSize()<<endl;
					cout << ": ";
				}
			}
			/*
			bool check = inList(songs, stoi(words[1]));
			if((int)words.size() != 5){
				cout << "Wrong amount of arguments" << endl;
				cout << ": ";
			}
			else if(isInteger(words[1]) == false){
				cout << "song id " << words[1] << " is not an integer" << endl;
				cout << ": ";
			}
			else if(isInteger(words[3]) == false){
				cout << "duration " << words[3] << " is not an integer" << endl;
				cout << ": ";
			}
			else if(check){
				int pos = 0;
				for(int i = 0; i < songs->getCurrSize(); i++){
					if(songs->at(i).getSongId() == stoi(words[1])){
						pos = i;
					} 
				}
				cout << "song id " << words[1] << " already used for " << songs->at(pos).getSongTitle() << " by " << songs->at(pos).getArtist() << endl;
				cout << ": ";
			}
			else{
				int min = stoi(words[3]) / 60;
				int sec = stoi(words[3]) % 60;
				cout << "new song " << words[1] << " " << words[4] << " by " << words[2] << " " << min << ":";
				if(sec < 10){
					cout << "0" << sec << endl;
				}
				else{
					cout << sec << endl;
				}
				Song a(stoi(words[1]), words[4], stoi(words[3]), words[2]);
				songs->add(a);
				cout<< "CHECK: Size of songs: " << songs->getCurrSize()<<endl;
				cout << ": ";
			}
			*/
		}
		else if(words[0] == "remove"){
			if((int)words.size() < 2){
				cout << "Too few arguments" << endl;
				cout << ": ";
			}
			else if(isInteger(words[1]) == false){
				cout << "song id " << words[1] << " is not an integer" << endl;
				cout << ": ";
			}
			else{
				bool check1 = inList(songs, stoi(words[1]));
				bool check2 = inCollection(playlists, stoi(words[1]));

				if(!check1){
				cout << "song id " << words[1] << " not found" << endl;
				cout << ": ";
				}
				else{
					int pos1 = 0;
					if(check1){
						for(int i = 0; i < songs->getCurrSize(); i++){
							if(songs->at(i).getSongId() == stoi(words[1])){
								pos1 = i;
							}
						}
					}
					int pos2 = 0;
					if(check2){
						for(int i = 0; i < playlists.size(); i++){
							if(playlists.at(i)->getSongId() == stoi(words[1])){
								pos2 = i;
							}
						}
					}
					for(int i=0;i<playlists.size(); i++){
						if(playlists.at(i)->exists(songs->at(pos2))){
							playlists.at(i)->removeBySong(songs->at(pos2));
						}
					}
					songs->removeByIndex(pos1);
					cout << "song " << words[1] << ", " << songs->at(pos1).getSongTitle() << " by " << songs->at(pos1).getArtist() << ", removed" << endl;
					//cout<< "CHECK: Size of songs: " << songs->getCurrSize()<<endl;
					cout << ": ";
				}
			}
			/*
			bool check1 = inList(songs, stoi(words[1]));
			bool check2 = inCollection(playlists, stoi(words[1]));
			cout << "removing song " << words[1] << endl;
			if((int)words.size() != 2){
				cout << "Wrong amount of arguments" << endl;
				cout << ": ";
			}
			else if(!check1){
				cout << "song id " << words[1] << " not found" << endl;
				cout << ": ";
			}
			else{
				int pos1 = 0;
				if(check1){
					for(int i = 0; i < songs->getCurrSize(); i++){
						if(songs->at(i).getSongId() == stoi(words[1])){
							pos1 = i;
						}
					}
				}
				
				int pos2 = 0;
				if(check2){
					for(int i = 0; i < playlists.size(); i++){
						if(playlists.at(i)->getSongId() == stoi(words[1])){
							pos2 = i;
						}
					}
				}
				for(int i=0;i<playlists.size(); i++){
					if(playlists.at(i)->exists(songs->at(pos2))){
						playlists.at(i)->removeBySong(songs->at(pos2));
					}
				}
				songs->removeByIndex(pos1);
				cout << "song " << words[1] << ", " << songs->at(pos1).getSongTitle() << " by " << songs->at(pos1).getArtist() << ", removed" << endl;
				cout<< "CHECK: Size of songs: " << songs->getCurrSize()<<endl;
				cout << ": ";
			}
			*/
		}
		else if(words[0] == "playlist"){
			if((int)words.size() < 3){
				cout << "Too few arguments" << endl;
				cout << ": ";
			}
			else if(isInteger(words[1]) == false){
				cout << "playlist id " << words[1] << " is not an integer" << endl;
				cout << ": ";
			}
			else{
				bool check = inCollection(playlists, stoi(words[1]));
				if(check){
					int pos = 0;
					for(int i = 0; i < playlists.size(); i++){
						if(playlists.at(i)->getSongId() == stoi(words[1])){
							pos = i;
						}
					}
					cout << "playlist id " << words[1] << " already used" << endl;
				}
				else{
					SongCollection *a = new SongCollection();
					a->setSongId(stoi(words[1]));
					a->setSongName(words[2]);
					bool greatest = true;
					for(int i = 0; i < playlists.size(); i++){
						if(playlists.at(i)->getSongId() > stoi(words[1])){
							playlists.insert(playlists.begin()+i, a);
							greatest = false;
							i = i + playlists.size();
						}
					}
					if(greatest){
						playlists.push_back(a);
					}
					cout << "new playlist " << words[1] << " called " << words[2] << endl;
					//cout<< "CHECK: Size of playlists: " << playlists.size()<<endl;
					cout << ": ";
				}
			}
			/*
			bool check = inCollection(playlists, stoi(words[1]));
			if((int)words.size() != 3){
				cout << "Wrong amount of arguments" << endl;
				cout << ": ";
			}
			else if(check){
				int pos = 0;
				for(int i = 0; i < playlists.size(); i++){
					if(playlists.at(i)->getSongId() == stoi(words[1])){
						pos = i;
					}
				}
				cout << "playlist id " << words[1] << " already used" << endl;
			}
			else{
				SongCollection *a = new SongCollection();
				a->setSongId(stoi(words[1]));
				a->setSongName(words[2]);
				bool greatest = true;
				for(int i = 0; i < playlists.size(); i++){
					if(playlists.at(i)->getSongId() > stoi(words[1])){
						playlists.insert(playlists.begin()+i, a);
						greatest = false;
						i = i + playlists.size();
					}
				}
				if(greatest){
					playlists.push_back(a);
				}
				cout << "new playlist " << words[1] << " called " << words[2] << endl;
				cout<< "CHECK: Size of playlists: " << playlists.size()<<endl;
				cout << ": ";
			}
			*/
		}
		else if(words[0] == "add"){
			if((int)words.size() < 3){
				cout << "Too few arguments" << endl;
				cout << ": ";
			}
			else if(isInteger(words[1]) == false){
				cout << "song id " << words[1] << " is not an integer" << endl;
				cout << ": ";
			}
			else if(isInteger(words[2]) == false){
				cout << "playlist id " << words[2] << " is not an integer" << endl;
				cout << ": ";
			}
			else{
				bool check1 = inList(songs, stoi(words[1]));
				int pos1 = 0;
				if(check1){
					for(int i = 0; i < songs->getCurrSize(); i++){
						if(songs->at(i).getSongId() == stoi(words[1])){
							pos1 = i;
						}
					}
				}
				bool check2 = inCollection(playlists, stoi(words[2]));
				int pos2 = 0;
				if(check2){
					for(int i = 0; i < playlists.size(); i++){
						if(playlists.at(i)->getSongId() == stoi(words[1])){
							pos2 = i;
						}
					}
				}
				bool check3 = true;
				if(check1 && check2){
					if(playlists.at(pos2)->exists(songs->at(pos1))){
						check3 = true;
					}
					check3 = false;
				}

				if(!check1){
					cout << "song " << words[1] << " does not exist" << endl;
					cout << ": ";
				}
				else if(!check2){
					cout << "playlist " << words[2] << " does not exist" << endl;
					cout << ": ";
				}
				else if(check3){
					cout << "song " << words[1] << " is already in playlist " << words[2] << endl;
					cout << ": ";
				}
				else{
					playlists.at(pos2)->add(songs->at(pos1));
					cout << "add song " << words[1] << " to playlist " << words[2] << endl;
					cout << ": ";
				}
			}
			/*
			bool check1 = inList(songs, stoi(words[1]));
			int pos1 = 0;
			if(check1){
				for(int i = 0; i < songs->getCurrSize(); i++){
					if(songs->at(i).getSongId() == stoi(words[1])){
						pos1 = i;
					}
				}
			}
			bool check2 = inCollection(playlists, stoi(words[2]));
			int pos2 = 0;
			if(check2){
				for(int i = 0; i < playlists.size(); i++){
					if(playlists.at(i)->getSongId() == stoi(words[1])){
						pos2 = i;
					}
				}
			}
			bool check3 = true;
			if(check1 && check2){
				if(playlists.at(pos2)->exists(songs->at(pos1))){
					check3 = true;
				}
				check3 = false;
			}
			
			if((int)words.size() != 3){
				cout << "Wrong amount of arguments" << endl;
				cout << ": ";
			}
			else if(!check1){
				cout << "song " << words[1] << " does not exist" << endl;
				cout << ": ";
			}
			else if(!check2){
				cout << "playlist " << words[2] << " does not exist" << endl;
				cout << ": ";
			}
			else if(check3){
				cout << "song " << words[1] << " is already in playlist " << words[2] << endl;
				cout << ": ";
			}
			else{
				playlists.at(pos2)->add(songs->at(pos1));
				cout << "add song " << words[1] << " to playlist " << words[2] << endl;
				cout << ": ";
			}
			*/
		}
		else if(words[0] == "drop"){
			if((int)words.size() < 3){
				cout << "Too few arguments" << endl;
				cout << ": ";
			}
			else if(isInteger(words[1]) == false){
				cout << "song id " << words[1] << " is not an integer" << endl;
				cout << ": ";
			}
			else if(isInteger(words[2]) == false){
				cout << "playlist id " << words[2] << " is not an integer" << endl;
				cout << ": ";
			}
			else{
				bool check1 = inList(songs, stoi(words[1]));
				int pos1 = 0;
				if(check1){
					for(int i = 0; i < songs->getCurrSize(); i++){
						if(songs->at(i).getSongId() == stoi(words[1])){
							pos1 = i;
						}
					}
				}
				bool check2 = inCollection(playlists, stoi(words[2]));
				int pos2 = 0;
				if(check2){
					for(int i = 0; i < playlists.size(); i++){
						if(playlists.at(i)->getSongId() == stoi(words[1])){
							pos2 = i;
						}
					}
				}
				bool check3 = true;
				if(check1 && check2){
					if(playlists.at(pos2)->exists(songs->at(pos1))){
						check3 = true;
					}
					else{
						check3 = false;
					}
				}

				if(!check1){
					cout << "song " << words[1] << " does not exist" << endl;
					cout << ": ";
				}
				else if(!check2){
					cout << "playlist " << words[2] << " does not exist" << endl;
					cout << ": ";
				}
				else if(!check3){
					cout << "song " << words[1] << " is not in playlist " << words[2] << endl;
					cout << ": ";
				}
				else{
					playlists.at(pos2)->removeBySong(songs->at(pos1));
					cout << "drop song " << words[1] << " from playlist " << words[2] << endl;
					//cout<< "CHECK: Size of songs in playlist: " << playlists.at(pos2)->getCurrSize()<<endl;
					cout << ": ";
				}
			}
			/*
			bool check1 = inList(songs, stoi(words[1]));
			int pos1 = 0;
			if(check1){
				for(int i = 0; i < songs->getCurrSize(); i++){
					if(songs->at(i).getSongId() == stoi(words[1])){
						pos1 = i;
					}
				}
			}
			bool check2 = inCollection(playlists, stoi(words[2]));
			int pos2 = 0;
			if(check2){
				for(int i = 0; i < playlists.size(); i++){
					if(playlists.at(i)->getSongId() == stoi(words[1])){
						pos2 = i;
					}
				}
			}
			bool check3 = true;
			if(check1 && check2){
				if(playlists.at(pos2)->exists(songs->at(pos1))){
					check3 = true;
				}
				else{
					check3 = false;
				}
			}
			
			if((int)words.size() != 3){
				cout << "Wrong amount of arguments" << endl;
				cout << ": ";
			}
			else if(!check1){
				cout << "song " << words[1] << " does not exist" << endl;
				cout << ": ";
			}
			else if(!check2){
				cout << "playlist " << words[2] << " does not exist" << endl;
				cout << ": ";
			}
			else if(!check3){
				cout << "song " << words[1] << " is not in playlist " << words[2] << endl;
				cout << ": ";
			}
			else{
				playlists.at(pos2)->removeBySong(songs->at(pos1));
				cout << "drop song " << words[1] << " from playlist " << words[2] << endl;
				cout<< "CHECK: Size of songs in playlist: " << playlists.at(pos2)->getCurrSize()<<endl;
				cout << ": ";
			}
			*/
		}
		else if(words[0] == "seesong"){
			if((int)words.size() < 2){
				cout << "Too few arguments" << endl;
				cout << ": ";
			}
			else if(isInteger(words[1]) == false){
				cout << "song id " << words[1] << " is not an integer" << endl;
				cout << ": ";
			}
			else{
				bool check = inList(songs, stoi(words[1]));
				int pos = 0;
				if(!check){
					cout << "song " << words[1] << " does not exist" << endl;
					cout << ": ";
				}
				else{
					for(int i = 0; i < songs->getCurrSize(); i++){
						if(songs->at(i).getSongId() == stoi(words[1])){
							pos = i;
						}
					} 
					cout << "song " << songs->at(pos).getSongTitle() << " by " << songs->at(pos).getArtist() << endl;
					cout << ": ";
				}
			}
			/*
			if((int)words.size() != 2){
				cout << "Wrong amount of arguments" << endl;
				cout << ": ";
			}
			bool check = inList(songs, stoi(words[1]));
			int pos = 0;
			if(!check){
				cout << "song " << words[1] << " does not exist" << endl;
				cout << ": ";
			}
			else{
				for(int i = 0; i < songs->getCurrSize(); i++){
					if(songs->at(i).getSongId() == stoi(words[1])){
						pos = i;
					}
				} 
				cout << "song " << songs->at(pos).getSongTitle() << " by " << songs->at(pos).getArtist() << endl;
				cout << ": ";
			}
			*/
		}
		else if(words[0] == "seeplaylist"){
			if((int)words.size() < 2){
				cout << "Too few arguments" << endl;
				cout << ": ";
			}
			else if(isInteger(words[1]) == false){
				cout << "playlist id " << words[1] << " is not an integer" << endl;
				cout << ": ";
			}
			else{
				bool check = inCollection(playlists, stoi(words[1]));
				if(!check){
					cout << "playlist " << words[1] << " does not exist" << endl;
					cout << ": ";
				}
				else{
					int index = 0;
					for(int i = 0; i < playlists.size(); i++){
						if(playlists.at(i)->getSongId() == stoi(words[1])){
							index = i;
						}
					}
					cout << "Songs in playlist " << words[1] << " " << playlists.at(index)->getSongName() << endl;
					for(int i = 0; i < playlists.at(index)->getCurrSize(); i++){
						cout << playlists.at(index)->at(i).getSongTitle() << " by " << playlists.at(index)->at(i).getArtist()<< endl;
					}
					
					cout << ": ";
				}
			}
			/*
			bool check = inCollection(playlists, stoi(words[1]));
			if((int)words.size() != 2){
				cout << "Wrong amount of arguments" << endl;
				cout << ": ";
			}
			else if(!check){
				cout << "playlist " << words[1] << " does not exist" << endl;
				cout << ": ";
			}
			else{
				int index = 0;
				for(int i = 0; i < playlists.size(); i++){
					if(playlists.at(i)->getSongId() == stoi(words[1])){
						index = i;
					}
				}
				cout << "Songs in playlist " << words[1] << " " << playlists.at(index)->getSongName() << endl;
				for(int i = 0; i < playlists.at(index)->getCurrSize(); i++){
					cout << playlists.at(index)->at(i).getSongTitle() << " by " << playlists.at(index)->at(i).getArtist()<< endl;
				}
				
				cout << ": ";
			}
			*/
		}
		else if(words[0] == "deleteplaylist"){
			if((int)words.size() < 2){
				cout << "Too few arguments" << endl;
				cout << ": ";
			}
			else if(isInteger(words[1]) == false){
				cout << "playlist id " << words[1] << " is not an integer" << endl;
				cout << ": ";
			}
			else{
				bool check = inCollection(playlists, stoi(words[1]));
				int pos = 0;
				if(check){
					for(int i = 0; i < playlists.size(); i++){
						if(playlists.at(i)->getSongId() == stoi(words[1])){
							pos = i;
						}
					}
				}
				if(!check){
					cout << "playlist " << words[1] << " does not exist" << endl;
				}
				else{
					playlists.at(pos)->~SongCollection();
					playlists.erase(playlists.begin() + pos);
					cout << "playlist " << words[1] << " successfully deleted" << endl;
					cout << ": ";
				}
			}
			/*
			bool check = inCollection(playlists, stoi(words[1]));
			int pos = 0;
			if(check){
				for(int i = 0; i < playlists.size(); i++){
					if(playlists.at(i)->getSongId() == stoi(words[1])){
						pos = i;
					}
				}
			}
			if((int)words.size() != 2){
				cout << "Wrong amount of arguments" << endl;
				cout << ": ";
			}
			else if(!check){
				cout << "playlist " << words[1] << " does not exist" << endl;
			}
			else{
				playlists.at(pos)->~SongCollection();
				playlists.erase(playlists.begin() + pos);
				cout << "playlist " << words[1] << " successfully deleted" << endl;
				cout << ": ";
			}
			*/
		}
		else if(words[0] == "copyplaylist"){
			if((int)words.size() < 4){
				cout << "Too few arguments" << endl;
				cout << ": ";
			}
			else if(isInteger(words[1]) == false){
				cout << "playlist id " << words[1] << " is not an integer" << endl;
				cout << ": ";
			}
			else if(isInteger(words[2]) == false){
				cout << "playlist id " << words[2] << " is not an integer" << endl;
				cout << ": ";
			}
			else{
				bool check1 = inCollection(playlists, stoi(words[1]));
				bool check2 = inCollection(playlists, stoi(words[2]));
				if(!check1){
					cout << "playlist " << words[1] << " does not exist" << endl;
				}
				else if(check2){
					cout << "playlist " << words[2] << " already exists" << endl;
				}
				else{
					int pos = 0;
					for(int i = 0; i < playlists.size(); i++){
						if(playlists.at(i)->getSongId() == stoi(words[1])){
							pos = i;
						}
					}
					SongCollection *copy = new SongCollection(*playlists.at(pos));
					copy->setSongId(stoi(words[2]));
					copy->setSongName(words[3]);
					playlists.push_back(copy);
					cout << "playlist " << words[1] << " successfully copied to playlist " << words[2] << " " << words[3] << endl;
					cout << ": ";
				}
			}
			/*
			bool check1 = inCollection(playlists, stoi(words[1]));
			bool check2 = inCollection(playlists, stoi(words[2]));
			if((int)words.size() != 4){
				cout << "Wrong amount of arguments" << endl;
				cout << ": ";
			}
			else if(!check1){
				cout << "playlist " << words[1] << " does not exist" << endl;
			}
			else if(check2){
				cout << "playlist " << words[2] << " already exists" << endl;
			}
			else{
				int pos = 0;
				for(int i = 0; i < playlists.size(); i++){
					if(playlists.at(i)->getSongId() == stoi(words[1])){
						pos = i;
					}
				}
				SongCollection *copy = new SongCollection(*playlists.at(pos));
				copy->setSongId(stoi(words[2]));
				copy->setSongName(words[3]);
				playlists.push_back(copy);
				cout << "playlist " << words[1] << " successfully copied to playlist " << words[2] << " " << words[3] << endl;
				cout << ": ";
			}
			*/
		}
		else if(words[0] == "renameplaylist"){
			if((int)words.size() < 3){
				cout << "Too few arguments" << endl;
				cout << ": ";
			}
			else if(isInteger(words[1]) == false){
				cout << "playlist id " << words[1] << " is not an integer" << endl;
				cout << ": ";
			}
			else{
				int pos = 0;
				for(int i = 0; i < playlists.size(); i++){
					if(playlists.at(i)->getSongId() == stoi(words[1])){
						pos = i;
					}
				}
				playlists.at(pos)->setSongName(words[2]);
				//cout << playlists.at(pos)->getSongName();
				cout << "playlist " << words[1] << " name successfully changed to " << words[2] << endl;
				cout << ": ";
			}
			/*
			if((int)words.size() != 3){
				cout << "Wrong amount of arguments" << endl;
				cout << ": ";
			}
			else{
				int pos = 0;
				for(int i = 0; i < playlists.size(); i++){
					if(playlists.at(i)->getSongId() == stoi(words[1])){
						pos = i;
					}
				}
				playlists.at(pos)->setSongName(words[2]);
				cout << playlists.at(pos)->getSongName();
				cout << "playlist " << words[1] << " name successfully changed to " << words[2] << endl;
				cout << ": ";
			}
			*/
		}
		else{
			cout << "Command not recognized, please try again." << endl;
			cout << ": ";
		}
		words.clear();
	}
	words.clear();
	return 0;
} 
