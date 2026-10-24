#specify target
all: cp2_songs

cp2_songs: cp2_songs.o Song.o SongCollection.o
	#g++ -fsanitize=undefined -fsanitize=address Song.o SongCollection.o cp2_songs.o -o cp2_songs
	g++ Song.o SongCollection.o cp2_songs.o -o cp2_songs

cp2_songs.o: cp2_songs.cpp
	g++ -c cp2_songs.cpp -o cp2_songs.o

# Specify how the object files should be created from source files
	
Song.o: Song.cpp Song.h
	g++ -c Song.cpp
	
SongCollection.o: SongCollection.cpp
	g++ -c SongCollection.cpp

#removes executables
clean:
	rm -rf *.o cp2_songs *out.
	rm -f *.o song
	
	
	



	

