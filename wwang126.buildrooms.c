#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

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
    "Makin Atoll",
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
// Create an array of 0-9 shuffled
int randomVal(int arrayIn[]){
    //Fill array
    for(int i = 0; i < 10; i++){
        arrayIn[i] = i;
    }
    //Shuffle array
    for (int i = 0; i < 10; i++) {    // shuffle array
        int tempVal = arrayIn[i];
        int randIndex = rand() % 10;

        arrayIn[i] = arrayIn[randIndex];
        arrayIn[randIndex] = tempVal;
    }
}

//Main fucntion that runs
int main(int argc, char* argv[]){
    //Create and allocate memory for 7 rooms
    struct room* rooms = malloc(7*sizeof(struct room));
    //Create array of non-duplicated Random numbers
    int names[10];
    //Seed random number generator
    srand(time(NULL));
    randomVal(names);
    for(int i = 0; i < 7; i++){
        //add room id
        rooms[i].id = i;
        //copy string from names to room
        printf("Room name = %s\n", room_names[names[i]]);
        //strcpy(rooms[i].name,room_names[names[i]]);
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
