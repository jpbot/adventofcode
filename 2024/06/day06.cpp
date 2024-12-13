#include "../util/chronoMessage.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdlib>

#define DEBUG

const char OBS = 'X';
const int GUARD_NORTH = 1;
const int GUARD_SOUTH = 3;
const int GUARD_EAST = 4;
const int GUARD_WEST = 2;


ChronoMessage cm;

int turnRight(int dir){
    if(++dir > 4) dir = 1;
    return dir;
}

int countObsCell(std::vector<std::vector<char> > guardMap){
    int obs = 0;

    for(int y = 0; y < guardMap.size(); y++){
        for(int x = 0; x < guardMap[y].size(); x++){
            if(guardMap[y][x] == OBS)
                obs++;
        }
    }

    return obs;
}

void problemOne(std::vector<std::vector<char> > guardMap, int guardX, int guardY, char guardDirection){
    std::cout << cm.beginLog() << "AoC 2024 - Day 06: PROBLEM 1" << std::endl;

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
                x--;
                break;
            case GUARD_WEST:
                x++;
                break;
        }

        if(y >= guardMap.size()){
            guardY = y;
            std::cout << cm.beginLog() << "   GUARD EXITS MAP: (" << x << ", "<< y << ")." << std::endl;
            break;
        }
        if(x >= guardMap[guardY].size()){
            guardX = x;
            std::cout << cm.beginLog() << "   GUARD EXITS MAP: (" << x << ", "<< y << ")." << std::endl;
            break;
        }

        if(guardMap[y][x] == '#'){
            guardDirection = turnRight(guardDirection);
        } else {
            if(false) std::cout << cm.beginLog() << "   GUARD OBS: (" << x << ", "<< y << ")." << std::endl;
            guardMap[y][x] = OBS;
            guardX = x;
            guardY = y;
        }
    }

    std::cout << cm.beginLog() << "   GUARD OBSERVES " << countObsCell(guardMap) << " cells." << std::endl;
}

void problemTwo(std::vector<std::vector<char> > guardMap){
    std::cout << cm.beginLog() << "AoC 2024 - Day 06: PROBLEM 2" << std::endl;


}



int main(int argc, char** argv){
    char* inputFile;
    char guardDirection = GUARD_NORTH;
    int guardX, guardY;
    
    if(argc > 1){
        inputFile = argv[1];
    } else {
        inputFile = "input";
    }

    //storage for map
    std::vector<std::vector<char> > guardMap;
        
    std::cout << cm.beginLog() << "AoC 2024 - Day 06" << std::endl;
    std::cout << cm.beginLog() << "Opening file: " << inputFile << std::endl;
    std::ifstream infile(inputFile);

    std::cout << cm.beginLog() << "Reading file." << std::endl;
    std::string s;
    int c = 0;
    while (std::getline(infile, s)){
        std::vector<char> t (s.begin(), s.end());
        c++;
        guardMap.push_back(t);
    }
    std::cout << cm.beginLog() << "Read " << c << " lines from file" << std::endl;
    std::cout << cm.beginLog() << "Searching for guard location" << std::endl;

    for(guardY = 0; guardY < guardMap.size(); guardY++){
        for(guardX = 0; guardX < guardMap[guardY].size(); guardX++){
            if(guardMap[guardY][guardX] == '^') break;
        }
        if(guardMap[guardY][guardX] == '^') break;
    }
    if(guardMap[guardY][guardX] == '^'){
        guardMap[guardY][guardX] = OBS;
        std::cout << cm.beginLog() << "Guard located at: " << guardX << ", " << guardY << std::endl;

        problemOne(guardMap, guardX, guardY, guardDirection);
        problemTwo(guardMap);
    } else {
        std::cout << cm.beginLog() << "Guard not located, exiting..." << std::endl;
    }
    
    return 0;
}
