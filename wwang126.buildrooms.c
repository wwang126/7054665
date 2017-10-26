#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

//Room struct that defines the room
struct room {
    int id;//Room ID, for debugging
    int roomType;//Type of room
    char *name;//Name of room
    int connectOut;//Number of outbound connections
    struct room* connections[6];//List of connections
};
//Hard coded names
const char *room_names[10] = {
    "Wake Island",
    "Coral Sea",
    "Guadalcanal",
    "Tarawa Atoll",
    "Makin Atoll"
    "Truk Island",
    "Saipan",
    "Tinian",
    "Peleiu",
    "Leyte Gulf"
};

// Returns true if all rooms have 3 to 6 outbound connections, false otherwise
int IsGraphFull() {
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

// Appends a room to file given a room struct
void printRoom( struct room roomIn){
    //Test print statement
    printf("Room %d, Name: %s\n", roomIn.id, roomIn.name);
}

//Main fucntion that runs
int main(int argc, char* argv[]){
    //Create and allocate memory for 7 rooms
    struct room* rooms = malloc(7*sizeof(struct room));
    for(int i = 0; i < 7; i++){
        //Initialize rooms
        printf("Test\n");
    }
    // Create all connections in graph
    while (IsGraphFull() != 0) {
        AddRandomConnection();
    }
    //Write rooms onto text file
    for(int i = 0; i < 7; i++){
        //Grab room
        struct room temp = rooms[i];
        //Print room to file
        printRoom(temp);
    }
    free(rooms);//Free memory
}
