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

//Main function that runs
int main(int argc, char* argv[]){
}
