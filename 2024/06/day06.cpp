#include "../util/chronoMessage.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdlib>

// #define DEBUG0
// #define DEBUG
// #define DEBUG2

const char GUARD_START = 1;
const char OBSERVED = 2;
const char OBSTRUCTION = 4;
const char TURN_NORTH = 16;
const char TURN_EAST = 32;
const char TURN_WEST = 64;
const char TURN_SOUTH = 128;

const char GUARD_NORTH = 1;
const char GUARD_EAST = 2;
const char GUARD_SOUTH = 3;
const char GUARD_WEST = 4;

const int GUARD_EXIT = 0;
const int GUARD_LOOP = -1;


ChronoMessage cm;

int turnRight(char &dir, int x, int y, std::vector<std::vector<char> > &map ){
    switch(dir) {
        case GUARD_NORTH:
            if(map[y][x] & TURN_EAST)   return GUARD_LOOP;
            map[y][x] = map[y][x] | TURN_EAST;
            break;
        case GUARD_SOUTH:
            if(map[y][x] & TURN_WEST)   return GUARD_LOOP;
            map[y][x] = map[y][x] | TURN_WEST;
            break;
        case GUARD_EAST:
            if(map[y][x] & TURN_SOUTH)   return GUARD_LOOP;
            map[y][x] = map[y][x] | TURN_SOUTH;
            break;
        case GUARD_WEST:
            if(map[y][x] & TURN_NORTH)   return GUARD_LOOP;
            map[y][x] = map[y][x] | TURN_NORTH;
            break; 
    }
    if(++dir > 4) dir = 1;
    return dir;
}

void printMap(std::vector<std::vector<char> > &map){
    for(int y = 0; y < map.size(); y++){
        std::cout << cm.beginLog() << "   OBS++: ";
        for(int x = 0; x < map[y].size(); x++){
            if(map[y][x] & OBSERVED)
                std::cout <<  "X";
            else if(map[y][x]==0)
                std::cout << ".";
            else if(map[y][x] & OBSTRUCTION)
                std::cout << "@";
            else
                std::cout << " " << "[" << (int)map[y][x] << "]";
        }
        std::cout << std::endl;
    }
}

const char * getDir (int guardDirection){
    if(guardDirection == GUARD_NORTH) return "NORTH";
    if(guardDirection == GUARD_EAST)  return "EAST";
    if(guardDirection == GUARD_SOUTH) return "SOUTH";
    if(guardDirection == GUARD_WEST)  return "WEST";
    return "";
}

void printObstruction(int x, int y, int guardX, int guardY, int guardDirection, const std::vector<std::vector<char> > &guardMap){
    std::cout << cm.beginLog() << "   >>>OBSTRUCTION MET: " << (int) guardMap[y][x]
        << " (" << x << ", "<< y << ").";
    std::cout << " GuardDir: " << getDir(guardDirection);
    std::cout << " GuardLoc: (" << guardX << ", " << guardY << ").";
}

int countObsCell(std::vector<std::vector<char> > &map){
    int obs = 0;

    for(int y = 0; y < map.size(); y++){
        for(int x = 0; x < map[y].size(); x++){
            if(map[y][x] & OBSERVED){
                obs++;

                #ifdef DEBUG0
                    std::cout << cm.beginLog() << ">>>OBS " << obs << "(" << x << ", " << y << ")" << std::endl;
                #endif
            }
        }
    }

    return obs;
}

int guardTour(std::vector<std::vector<char> > &guardMap, int &guardX, int &guardY, char &guardDirection){
    #ifdef DEBUG
        std::cout << cm.beginLog() << "   GUARD DIRECTION: (" << guardX << ", " << guardY << ") " 
            << (int) guardDirection << ":" << getDir(guardDirection) << "." << std::endl;
    #endif

    while(true){
        int x = guardX;
        int y = guardY;

        switch(guardDirection) {
            case GUARD_NORTH:
                y--;
                break;
            case GUARD_SOUTH:
                y++;
                break;
            case GUARD_EAST:
                x++;
                break;
            case GUARD_WEST:
                x--;
                break;
        }

        if(y < 0 || x < 0){
            guardX = x;
            guardY = y;
            return GUARD_EXIT;
        }
        if(y >= guardMap.size()){
            guardY = y;
            return GUARD_EXIT;
        }
        if(x >= guardMap[guardY].size()){
            guardX = x;
            return GUARD_EXIT;
        }

        if(guardMap[y][x] & OBSTRUCTION){
            #ifdef DEBUG
                printObstruction(x, y, guardX, guardY, guardDirection, guardMap);
            #endif

            if(turnRight(guardDirection, guardX, guardY, guardMap) < 0){
                return GUARD_LOOP;
            };
            
            #ifdef DEBUG
                std::cout << " NewGuardDir: " << getDir(guardDirection) << std::endl;
            #endif
        } else {
            guardMap[y][x] = guardMap[y][x] | OBSERVED;
            guardX = x;
            guardY = y;
        }
    }
    return 0;
}

void problemOne(std::vector<std::vector<char> > &guardMap, int guardX, int guardY, char guardDirection){
    int tourResult;
    std::cout << cm.beginLog() << "AoC 2024 - Day 06: PROBLEM 1" << std::endl;

    tourResult = guardTour(guardMap, guardX, guardY, guardDirection);

    std::cout << cm.beginLog() << "   GUARD TOUR ENDS: " << (int) tourResult << " ";
    if(tourResult == 0){
        std::cout << "GUARD EXITS (" << guardX << ", " << guardY << ")." << std::endl;
    } else if(tourResult == GUARD_LOOP){
        std::cout << "LOOP DETECTED (" << guardX << ", " << guardY << ")." << std::endl;
    }

    std::cout << cm.beginLog() << "   GUARD DIRECTION: " << (int) guardDirection << " " << getDir(guardDirection) << "." << std::endl;
    std::cout << cm.beginLog() << "   GUARD OBSERVES " << countObsCell(guardMap) << " cells." << std::endl;
}

void problemTwo(std::vector<std::vector<char> > &guardMap, int startX, int startY, char startDirection, std::vector<std::vector<char> > cleanMap){
    int tourResult;
    int loop = 0;
    int guardX = startX;
    int guardY = startY;
    char guardDirection = startDirection;
    #ifdef DEBUG2
        int c = 0;
        bool mapPrint = false;
        printMap(guardMap);
    #endif

    std::cout << cm.beginLog() << "AoC 2024 - Day 06: PROBLEM 2" << std::endl;

    //scan map for observed area, test adding obstruction
    for(int y = 0; y < guardMap.size(); y++){
        for(int x = 0; x < guardMap[y].size(); x++){
            if(startX == x && startY == y)  continue;  //guard starting position can't be obstruction
            if(guardMap[y][x] & OBSERVED){
                guardX = startX;
                guardY = startY;
                guardDirection = startDirection;
                std::vector<std::vector<char> > tempMap = cleanMap;
                tempMap[y][x] = tempMap[y][x] | OBSTRUCTION;

                #ifdef DEBUG2
                    std::cout << cm.beginLog() << ">>>TESTING " << ++c << "(" << x << ", " << y << ") ";
                    if(!mapPrint){
                        mapPrint = true;
                        printMap(tempMap);
                    }
                #endif
                tourResult = guardTour(tempMap, guardX, guardY, guardDirection);
                
                if(tourResult == GUARD_LOOP){
                    #ifdef DEBUG2
                        std::cout << "LOOP DETECTED (" << guardX << ", " << guardY << ")." << std::endl;
                    #endif
                    loop++;
                }
                #ifdef DEBUG2
                    if(tourResult == 0){
                        std::cout << "GUARD EXITS (" << guardX << ", " << guardY << ")." << std::endl;
                    }
                #endif
            }
        }
    }

    std::cout << cm.beginLog() << "SINGLE ADDED OBSTRUCTION CELLS TO LOOP GUARD: " << loop << "." << std::endl;
}

int main(int argc, char** argv){
    char* inputFile;
    char guardDirection = GUARD_NORTH;
    int guardX = -1;
    int guardY = -1;
    
    if(argc > 1){
        inputFile = argv[1];
    } else {
        inputFile = "input";
    }

    //storage for map
    std::vector<std::vector<char> > guardMap;
    std::vector<std::vector<char> > cleanMap;
        
    std::cout << cm.beginLog() << "AoC 2024 - Day 06" << std::endl;
    std::cout << cm.beginLog() << "Opening file: " << inputFile << "." << std::endl;
    std::ifstream infile(inputFile);

    std::cout << cm.beginLog() << "Reading file." << std::endl;
    std::string s;
 
     while (std::getline(infile, s)){
        std::vector<char> t (s.begin(), s.end());
        guardMap.push_back(t);
    }
    std::cout << cm.beginLog() << "Read " << guardMap.size() << " lines from file." << std::endl;
    std::cout << cm.beginLog() << "Initializing map data." << std::endl;

    for(int y = 0; y < guardMap.size(); y++){
        for(int x = 0; x < guardMap[y].size(); x++){
            switch(guardMap[y][x]){
                case '^':
                    std::cout << cm.beginLog() << "Guard located at: " << x << ", " << y << std::endl;
                    guardMap[y][x] = GUARD_START + OBSERVED;
                    guardX = x;
                    guardY = y;
                    break;
                case '#':
                    guardMap[y][x] = OBSTRUCTION;
                    break;
                default:
                    guardMap[y][x] = 0;
            }
        }
    }

    std::cout << cm.beginLog() << "Initializing map data: COMPLETE." << std::endl;

    if(guardX == -1 && guardY == -1){
        std::cout << cm.beginLog() << "Guard not located, exiting..." << std::endl;
        return -1;
    }

    std::cout << cm.beginLog() << "Copy map data." << std::endl;
    cleanMap = guardMap;

    problemOne(guardMap, guardX, guardY, guardDirection);
    problemTwo(guardMap, guardX, guardY, guardDirection, cleanMap);
    
    return 0;
}
