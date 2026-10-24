#include <iostream>
#include <stdlib.h>
#include "Song.h"
using namespace std;

class SongCollection{
	private:
		Song* list;
		int space;
		int currSize;
		string songName;
		int songId;
		

	public:
		SongCollection();
		SongCollection(const SongCollection& other);
		SongCollection& operator=(const SongCollection& copy);
		~SongCollection();
		
		int getCurrSize();
		int getSpace();
		string getSongName();
		int getSongId();
		
		void setSongName(string n);
		void setSongId(int i);
		
		void resize();
		void add(Song s);
		void removeBySong(Song s);
		void removeById(int i);
		void removeByIndex(int i);
		Song at(int i);
		bool exists(Song s);
};
