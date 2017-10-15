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
