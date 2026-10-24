# song-playlist-manager
A C++ command-line application for managing song collections and playlists, with commands to add and remove songs, organize playlists, and view or copy collections.

## Features

- Add, view, and remove songs
- Create and manage playlists
- Add songs to and remove songs from playlists
- Rename and copy playlists
- View playlist contents
- Interactive command-line interface

### Compile

```bash
g++ cp2_songs.cpp Song.cpp SongCollection.cpp -o cp2_songs
```

### Run

**Windows (PowerShell):**

```powershell
.\cp2_songs
```

**Linux/macOS:**

```bash
./cp2_songs
```

## Commands

### Song Management

| Command | Description |
|---|---|
| `song <song id> "<song artist>" <song duration in seconds> "<song title>"` | Add a song to the collection |
| `seesong <song id>` | View a song's details |
| `remove <song id>` | Remove a song from the collection |

Example:

```text
song 1 "Taylor Swift" 210 "Cruel Summer"
seesong 1
remove 1
```

### Playlist Management

| Command | Description |
|---|---|
| `playlist <playlist id> "<playlist name>"` | Create a playlist |
| `seeplaylist <playlist id>` | View a playlist's contents |
| `renameplaylist <playlist id> "<new name>"` | Rename a playlist |
| `copyplaylist <existing playlist id> <new playlist id> "<new playlist name>"` | Copy a playlist |
| `deleteplaylist <playlist id>` | Delete a playlist |

Example:

```text
playlist 10 "Favorites"
renameplaylist 10 "Road Trip"
copyplaylist 10 11 "Road Trip Copy"
seeplaylist 11
deleteplaylist 11
```

### Playlist Song Organization

| Command | Description |
|---|---|
| `add <song id> <playlist id>` | Add a song to a playlist |
| `drop <song id> <playlist id>` | Remove a song from a playlist |

Example:

```text
song 1 "Taylor Swift" 210 "Cruel Summer"
playlist 10 "Favorites"
add 1 10
seeplaylist 10
drop 1 10
```

### Exit

| Command | Description |
|---|---|
| `quit` | Exit the program |

## Example Workflow

```text
song 1 "Taylor Swift" 210 "Cruel Summer"
song 2 "The Weeknd" 200 "Blinding Lights"
playlist 10 "Favorites"
add 1 10
add 2 10
seeplaylist 10
copyplaylist 10 11 "Favorites Copy"
seeplaylist 11
quit
```

## Notes

- Song durations are specified in seconds.
- Song and playlist IDs are numeric identifiers.
- Names and titles containing spaces should be enclosed in double quotes.
- Data is stored in memory and is not automatically saved between program runs.
- The application manages song information and playlists; it does not play audio.

## Purpose

This project demonstrates C++ programming concepts, including object-oriented design, data structure management, command parsing, and operations for organizing songs into playlists.
