#include "../util/chronoMessage.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

ChronoMessage cm;

void problemOne(std::vector<int> &listA, std::vector<int> &listB){
    std::cout << cm.beginLog() << "AoC 2024 - Day 01: PROBLEM 2" << std::endl;

    std::cout << cm.beginLog() << "Computing distance (displaying first 5 calculations)" << std::endl;
    int d = 0;
    for(int i = 0; i < listA.size(); i++){
        d += abs(listA[i] - listB[i]);
        if(i < 5){
            std::cout << "  " << i << ": " << listA[i] << "|" << listB[i] 
                << " dist: " << abs(listA[i] - listB[i]) << " [" << d << "]" << std::endl;
        }
    }
    std::cout << cm.beginLog() << "PROBLEM 1 TOTAL DISTANCE:" << d << std::endl;
}

void problemTwo(std::vector<int> &listA, std::vector<int> &listB){
    std::cout << cm.beginLog() << "AoC 2024 - Day 01: PROBLEM 1" << std::endl;

    std::cout << cm.beginLog() << "Computing similarity score (displaying first 5 calculations)" << std::endl;
    int s = 0;
    int b = 0;
    int lastA, bOccurance;
    for(int i = 0; i < listA.size(); i++){
        if(i == 0 || (i > 0 && listA[i] != lastA)){
            bOccurance = 0;
            lastA = listA[i];
    
            for(; b < listB.size(); b++){
                if(listB[b] == listA[i])
                    bOccurance++;
                if(listB[b] > listA[i])
                    break;
            }
        }
        s += bOccurance * lastA;

        if(i < 5){
            std::cout << "  " << i << ": " << listA[i] << "|" << bOccurance * lastA <<
                "[" << s << "]" << std::endl;
        }
    }
    std::cout << cm.beginLog() << "PROBLEM 2 SIMILARITY:" << s << std::endl;
}

int main(int argc, char** argv){
    char* inputFile;
    
    if(argc > 1){
        inputFile = argv[1];
    } else {
        inputFile = "input";
    }

    std::vector<int> listA;
    std::vector<int> listB;
    
    std::cout << cm.beginLog() << "AoC 2024 - Day 01" << std::endl;
    std::cout << cm.beginLog() << "Opening file: " << inputFile << std::endl;
    std::ifstream infile(inputFile);

    std::cout << cm.beginLog() << "Reading file" << std::endl;
    int a, b, c = 0;
    while (infile >> a >> b){
        c++;
        listA.push_back(a);
        listB.push_back(b);
    }
    std::cout << cm.beginLog() << "Read " << c << " lines from file" << std::endl;

    std::cout << cm.beginLog() << "Sorting" << std::endl;
    std::sort(listA.begin(), listA.end());
    std::sort(listB.begin(), listB.end());
    std::cout << cm.beginLog() << "Sorting Complete" << std::endl;

    problemOne(listA, listB);
    problemTwo(listA, listB);
    
    return 0;
}
