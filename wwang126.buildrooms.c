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

//Main fucntion that runs
int main(int argc, char* argv[]){
    struct room* rooms[6];//Array of rooms
    //Create and allocate memory for 7 rooms
    for(int i = 0; i < 7; i++){
        //Allocate space for room
        //Initilize room with i as id
        //Add room to rooms Array
    }
    // Create all connections in graph
    while (IsGraphFull() == false) {
        AddRandomConnection();
    }
    //TODO: Write rooms onto text file
}

// Returns true if all rooms have 3 to 6 outbound connections, false otherwise
bool IsGraphFull() {
    //TODO
}

// Adds a random, valid outbound connection from a Room to another Room
void AddRandomConnection() {
    //TODO
}

// Returns a random Room, does NOT validate if connection can be added
struct room GetRandomRoom() {
    //TODO
}

// Returns true if a connection can be added from Room x, false otherwise
int CanAddConnectionFrom(struct room x) {
    if (x.connectOut < 6) {
        return 1;
    }
    return 0;
}

// Connects Rooms x and y together, does not check if this connection is valid
void ConnectRoom(struct room x, struct room y) {
    //TODO
}

// Returns true if Rooms x and y are the same Room, false otherwise
int IsSameRoom(struct room x, struct room y) {
    if(x.id == y.id){
        return 1;
    }
    return 0;
}
