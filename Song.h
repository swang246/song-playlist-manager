#include <iostream>
#include <stdlib.h>
using namespace std;

class Song{
	public:
		Song(int id, string title, int dur, string artist_p);
		Song();
		
		int getSongId();
		string getSongTitle();
		string getArtist();
		
		Song& operator=(const Song& copy);
		~Song();
	private:
		int songId = 0;
		string songTitle = "";
		int duration = 0;
		string artist = "";
};
