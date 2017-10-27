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
    char *name;//Name of room
    int connectOut;//Number of outbound connections
    struct room* connections[7];//List of connections
};
//Index of names, since I know the max size I just hard code the size
struct room rooms[7];
int startRoom;
int endRoom;
int currId;
int steps[100];
int stepCnt;

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
void printWin(){
    //Add end room to List
    steps[stepCnt] = endRoom;
    stepCnt++;
    //Print end message
    printf("YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
    printf("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n", stepCnt);
    int i = 0;
    while(i < stepCnt){
        printf("%s\n",rooms[steps[i]].name);
        i++;
    }
}
//prints a list of all connections
void printConnections(struct room roomIn){
    int i = 0;
    while(i < roomIn.connectOut - 1){
        printf("%s, ",roomIn.connections[i]->name);
        i++;
    }
    //Special handling for last item
    printf("%s.\n",roomIn.connections[i]->name);
}

//Checks if room is connected, 0 if connected, 1 if not
int isConnected(char* name,struct room roomIn){
    int i = 0;
    while(i < roomIn.connectOut){
        if(strcmp(roomIn.connections[i]->name,name) == 0){
            return 0;
        }
        i++;
    }
    return 1;
}

//Returns 0 if there is a room by that name, 1 otherwise
int isRoom(char* name){
    int i = 0;
    while (i < 7){
        if(strcmp(rooms[i].name,name) == 0){
            return 0;
        }
        i++;
    }
    return 1;
}
//Get room give the name of a room
struct room* getRoom(char* name){
    int i = 0;
    while (i < 7){
        if(strcmp(rooms[i].name,name) == 0){
            return &rooms[i];
        }
        i++;
    }
    return 0;
}
//connect the rooms
void connectRooms(char* name){
    char temp[15];
    int connectIndex = 0;
    //Open file
    FILE *file = fopen(name, "r");
    //Move line pointer past first line
    fscanf(file, "ROOM NAME: %s\n", temp);
    if(strcmp(rooms[currId].name,temp) != 0){
        printf("Error!\n");
    }
    //Create int to read
    int read;
    do {
        read = fscanf(file, "CONNECTION %d: %s\n",&connectIndex, temp);
        printf("read is %d",read);
        printf(" Temp is %s\n",temp);
        rooms[currId].connections[connectIndex-1] = getRoom(temp);
    } while(read != 0);
    rooms[currId].connectOut = connectIndex;
    fscanf(file, "ROOM TYPE: %s\n", temp);
    printf("Room type is %s\n",temp);
    if (strcmp(temp, "START_ROOM") == 0) {
        printf("it's a Start Room!");
        startRoom = currId;
    }
    if (strcmp(temp, "END_ROOM") == 0) {
        printf("it's a End Room!");
        endRoom = currId;
    }
    fclose(file);
}


    /*------------------------------------
    fseek(file,11,SEEK_CUR);
    fgets(temp,13,file);

    do {
        //Move cursor to room name
        fseek(file,14,SEEK_CUR);
        //Grab name
        fgets(temp,13,file);
        //remove the new line
        strtok(temp, "\n");
        printf("Reading %s\n",temp);
        output.connections[connectIndex-1] = getRoom(temp);
        printf("Connect index %d\n",connectIndex);
    } while(strstr(temp,"_ROOM") != NULL);
    //CLose file
    fclose(file);
    */


//Read in the names and populate the array
void createRooms(char* name){
    //Allocate space for name of node
    char* tempName = malloc(sizeof(char)*strlen(name));
    //Allocate space for tempType
    //char* tempType = malloc(sizeof(char)*11);
    //Open file
    FILE *file = fopen(name, "r");
    //Read in name
    fscanf(file, "ROOM NAME: %s\n", tempName);
    rooms[currId].name = tempName;
    //set id
    rooms[currId].id = currId;

/*---------------------------------------------------
    //Read in type
    fscanf(file, "ROOM TYPE: %s\n", tempType);
    //Save start and end nodes
    printf("Type is :%s\n",tempType);
    //if end node
    if(strcmp(tempType, "END_ROOM") == 0){
        printf("End room is %s", rooms[currId].name);
        endRoom = currId;
    }
    //if start node
    if (strcmp(tempType,"START_ROOM") == 0){
        printf("start room is %s\n", rooms[currId].name);
        startRoom = currId;
    }
----------------------------------*/
    fclose(file);

    //test to see if wrote successfully
    printf("Added %s\n",rooms[currId].name);
}
//Read rooms from directory specified in dir
void readRooms(struct room* rooms, char* dir){
    //switch to directory
    chdir(dir);
    DIR *srcDir;
    DIR *srcDir2;
    struct dirent *currDir;
    //set srcDir and srcDir2 to current directory
    srcDir = opendir (".");
    srcDir2 = opendir (".");

    currId = 0;
    //Create rooms
    while ((currDir = readdir (srcDir))) {
        //Only read if isn't system file
        if(strstr(currDir->d_name, ".") == 0){
            createRooms(currDir->d_name);
            currId++;
        }
    }

    int i = 0;
    while(i<7){
        printf("Rooms %s at %d\n",rooms[i].name,rooms[i].id );
        i++;
    }

    //Read thru all files to add in connections
    currId = 0;
    while ((currDir = readdir (srcDir2))) {
        //Only read if isn't system file
        if(strstr(currDir->d_name, ".") == 0){
            printf("Reading 2: %s\n", currDir->d_name);
            connectRooms(currDir->d_name);
            currId++;
        }
    }

    //Clean up and return to original directory
    closedir(srcDir);
    closedir(srcDir2);
    chdir("..");
}
//Main function that runs
int main(int argc, char* argv[]){
    //Grab newest directory
    char* dir = getDirName();
    printf("Grabbing %s\n", dir );
    readRooms(rooms,dir);
    int gameCont = 1;
    currId = startRoom;
    char input[15];
    int stepCnt = 0;
    while(gameCont != 0){
        //Print info about room
        printf("CURRENT LOCATION: %s\n", rooms[currId].name );
        printf("POSSIBLE CONNECTIONS: ");
        printConnections(rooms[currId]);
        printf("WHERE TO?>");

        //Get user input
        fgets(input, 15, stdin);
        //Get rid of newline
        strtok(input, "\n");
        //Input validation, if connected
        if(isConnected(input,rooms[currId]) == 0){
            //Add current room to steps taken and increment steps
            steps[stepCnt] = currId;
            stepCnt++;
            //Set curr room to new room
            currId = getRoom(input)->id;
            //Check for win
            if(currId == endRoom){
                printWin();
            }
        }
        printf("HUH? I DON’T UNDERSTAND THAT ROOM. TRY AGAIN.\n");
    }
    //TODO Free memory
    return 0;
}
