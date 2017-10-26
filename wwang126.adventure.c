#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>

//Room struct that defines the room
struct room {
    int id;//Room ID, for debugging
    int roomType;//Type of room
    char *name;//Name of room
    int connectOut;//Number of outbound connections
    int connections[7];//List of connections
};

//Return start room name
char* getDirName(){
    //Create dirent struct
    struct dirent* temp = NULL;
    //Grab current directory
    DIR * srcDirr = opendir(".");
    time_t currTime = 0;
    char* dirName = malloc(sizeof(char)*50);
    while ((temp = readdir(srcDirr)) != NULL){
        //Check if file complies to the naming system for directories
        if(strstr(temp->d_name, "wwang126.rooms") != 0){
            //Create stat structure to store stats in
            struct stat fileStats;
            //Get stats for new directory
            stat(temp->d_name ,&fileStats);

            //Compare time, if greater than zero must be newer
            if (difftime(fileStats.st_mtime,currTime) > 0){
                strcpy(dirName, temp->d_name);
                currTime = fileStats.st_mtime;
            }
        }
    }
    return dirName;
}

//Main function that runs
int main(int argc, char* argv[]){
    //Grab newest directory
    char* dir = getDirName();
    printf("Grabbing %s\n", dir );
    //Allocate space for rooms
    struct room* rooms = malloc(7*sizeof(struct room));
    free(rooms);
    return 0;
}
