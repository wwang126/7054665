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
    int connections[7];//List of connections
};
//Hard coded names, got rid of const as this stores the acutal name
char *room_names[10] = {
    "Wake_Island",
    "Coral_Sea",
    "Guadalcanal",
    "Tarawa_Atoll",
    "Makin_Atoll",
    "Truk_Island",
    "Saipan",
    "Tinian",
    "Peleiu",
    "Leyte_Gulf"
};

// Returns true if all rooms have 3 to 6 outbound connections, false otherwise
int IsGraphFull(struct room rooms[]) {
    //iterate thru checking to see if any have less than 3 connections
    int i = 0;
    while(i < 7){
        //if less than 3 connects graph isn't full
        if(rooms[i].connectOut < 3){
            return 0;
        }
        i++;
    }
    return 1;
}

// Returns a random index, does NOT validate if connection can be added
int GetRandomRoom() {
    int out = rand() % 7;
    return out;
}

// Adds a valid connection from a Room to another Room
void AddConnection(struct room* room1,struct room* room2) {
    //If the id's are the same exit.
    if(room1->id == room2->id){
        return;
    }
    //Check if the rooms is maxed out
    if(room1->connectOut > 5){
        return;
    }
    if(room2->connectOut > 5){
        return;
    }
    //Check if the connection already exists
    int i = 0;
    while(i < room1->connectOut){
        //if a connection has the same id as room2 exit
        if(room1->connections[i] == room2->id){
            return;
        }
        i++;
    }
    //Just incase I'll check room 2 also
    i = 0;
    while(i < room2->connectOut){
        //if a connection has the same id as room2 exit
        if(room1->connections[i] == room2->id){
            return;
        }
        i++;
    }
    //If they have less than 6 connetions, create the connection
    room1->connections[room1->connectOut] = room2->id;
    room1->connectOut++;
    room2->connections[room2->connectOut] = room1->id;
    room2->connectOut++;
}

void writeRoomsToDisk(struct room rooms[]){
    //Get process id for direcotry name
    pid_t pid = getpid();
    printf("wwang126.rooms.%d",pid);
    //Figure out how long the string is
    unsigned int name = strlen("wwang126.rooms.") + sizeof(pid) + 5;
    //Create memory to store directory in
    char *dirName = malloc(name);
    //Create and store directory name
    sprintf(dirName, "wwang126.rooms.%d",pid);
    //Create the directory
    mkdir(dirName,0777);
    //Enter directory
    chdir(dirName);
    int i = 0;
    while (i < 7){
        //Create file, just call it by room name to make it easier
        FILE* fp = fopen(rooms[i].name, "w");
        struct room roomIn = rooms[i];
        //Print room name
        fprintf(fp,"ROOM NAME: %s\n", roomIn.name);
        //Print connections
        int k = 0;
        while(k < roomIn.connectOut){
            int j = k + 1;
            fprintf(fp, "CONNECTION %d: %s\n",j,rooms[roomIn.connections[k]].name);
            k++;
        }
        //Print room types doesn't have to be random
        if(roomIn.id == 0){
            fprintf(fp,"ROOM TYPE: START_ROOM\n");
        }
        else if(roomIn.id == 6){
            fprintf(fp, "ROOM TYPE: END_ROOM\n");
        }
        else{
            fprintf(fp, "ROOM TYPE: MID_ROOM\n");
        }
        //exit file
        fclose(fp);
        i++;
    }
    //Exit directory
    chdir("..");
    //Free memory
    free(dirName);

}

// Appends a room to file given a room struct
void printRoom( struct room roomIn, struct room rooms[]){
    //Print name
    printf("ROOM NAME: %s\n", roomIn.name);
    //Print connections
    int i = 0;
    while(i < roomIn.connectOut){
        int j = i + 1;
        printf("CONNECTION %d: %s\n",j,rooms[roomIn.connections[i]].name);
        i++;
    }
    //Print room types
    if(roomIn.id == 0){
        printf("ROOM TYPE: START_ROOM\n");
    }
    else if(roomIn.id == 6){
        printf("ROOM TYPE: END_ROOM\n");
    }
    else{
        printf("ROOM TYPE: MID_ROOM\n");
    }
}
// Create an array of 0-9 shuffled
void randomVal(int arrayIn[]){
    //Fill array
    int i = 0;
    while(i < 10){
        arrayIn[i] = i;
        i++;
    }
    //Shuffle array
    i = 0;
    while (i < 10) {    // shuffle array
        int tempVal = arrayIn[i];
        int randIndex = rand() % 10;

        arrayIn[i] = arrayIn[randIndex];
        arrayIn[randIndex] = tempVal;
        i++;
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
    int i = 0;
    while(i < 7){
        //add room id
        rooms[i].id = i;
        //set connections to 0
        rooms[i].connectOut = 0;
        //Pointing name at hardcoded name
        rooms[i].name = room_names[names[i]];
        //Set type to MID_ROOM
        rooms[i].roomType = 0;
        //Increment i for loop
        i++;
    }
    // Create all connections in graph
    while (IsGraphFull(rooms) != 1) {
        AddConnection(&rooms[GetRandomRoom()],&rooms[GetRandomRoom()]);
    }
    writeRoomsToDisk(rooms);
    /* For testing output
    //Write rooms onto text file
    for(int i = 0; i < 7; i++){
        //Grab room
        struct room temp = rooms[i];
        //Print room to file
        printRoom(temp,rooms);
    }
    */
    free(rooms);//Free memory
    //exit properly
    return 0;
}
