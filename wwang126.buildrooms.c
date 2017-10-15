#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

//Room struct that defines the room
struct room {
    int id; //Room ID
    int roomType;//Type of room
    char *name;//Name of room
    int connectOut;//Number of outbound connections
    struct room* connections[6];//List of connections
};

int main(int argc, char* argv[]){
    // Create all connections in graph
    while (IsGraphFull() == false) {
        AddRandomConnection();
    }
}

// Returns true if all rooms have 3 to 6 outbound connections, false otherwise
bool IsGraphFull() {
    //TODO
}

// Adds a random, valid outbound connection from a Room to another Room
void AddRandomConnection() {
    Room A;  //Maybe a struct, maybe global arrays of ints
    Room B;

    while(true)
    {
    A = GetRandomRoom();

    if (CanAddConnectionFrom(A) == true)
        break;
    }

    do
    {
    B = GetRandomRoom();
    }
    while(CanAddConnectionFrom(B) == false || IsSameRoom(A, B) == true);

    ConnectRoom(A, B);
    ConnectRoom(B, A);
}

// Returns a random Room, does NOT validate if connection can be added
Room GetRandomRoom() {
    //TODO
}

// Returns true if a connection can be added from Room x, false otherwise
bool CanAddConnectionFrom(Room x) {
    //TODO
}

// Connects Rooms x and y together, does not check if this connection is valid
void ConnectRoom(Room x, Room y) {
    //TODO
}

// Returns true if Rooms x and y are the same Room, false otherwise
bool IsSameRoom(Room x, Room y) {
    //TODO
}
