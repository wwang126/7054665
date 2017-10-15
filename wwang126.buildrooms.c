#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Room struct that defines the room
struct room {
    int roomType;//Type of room
    char *name;//Name of room
    int connectOut;//Number of outbound connections
    struct room* connections[6];//List of connections
};
