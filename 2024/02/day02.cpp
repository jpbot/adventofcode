#include "../util/chronoMessage.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdlib>

#define DEBUG

ChronoMessage cm;

// Test individual AoC 2024 Day2 report
// input:   single report vector
// returns: 0 no problems found
//          -1 only 0 or 1 levels
//          >1 level where problem occurs 
int testReport(std::vector<int> &r, int skipLevel = -1){
    long reportLen = r.size();
    int level, direction;
    int p = 1;
    int lastLevel = r[0];

    // must have > 1 levels to check. 
    if(reportLen < 2) return -1;        //untested
    
    if(skipLevel == 0){
        p++;
        lastLevel = r[1];
    }
          
    for(; p < reportLen; p++){
        if(p != skipLevel && !(p == 1 && skipLevel == 0)){
            level = r[p];

            //check consistent direction (and !zero change)
            if(level == lastLevel){       //values must not repeat
                return p;
            }
        
            if((p == 1 && skipLevel != 1) || (skipLevel == 0 && p == 2) || (skipLevel == 1 && p == 2)){
                //determine direction (1 increasing, -1 decreasing)
                direction = level>lastLevel?1:-1;
            } else if(direction != (level>lastLevel?1:-1)) {
                //if direction changed, not a safe report
                return p;
            }

            //check magnitute of change is not more than 3
            if(abs(level-lastLevel) > 3){
                return p;
            }
        
            lastLevel = level;
        }
    }

    return 0;
}

void problemOne(std::vector<std::vector<int> > &report){
    std::cout << cm.beginLog() << "AoC 2024 - Day 02: PROBLEM 1" << std::endl;

    std::cout << cm.beginLog() << "Checking for 'safe' reports" << std::endl;
    int safeReports = 0;
    
    for(int i = 0; i < report.size(); i++){
        if(testReport(report[i]) == 0)
            safeReports++;
    }
    std::cout << cm.beginLog() << "PROBLEM 1 SAFE REPORT COUNT: " << safeReports << std::endl;
}

void problemTwo(std::vector<std::vector<int> > &report){
    std::cout << cm.beginLog() << "AoC 2024 - Day 02: PROBLEM 2" << std::endl;

    std::cout << cm.beginLog() << "Checking for 'safe' reports" << std::endl;
    int safeReports = 0;
    
    for(int i = 0; i < report.size(); i++){
        int s = testReport(report[i]);
        if(s == 0){
            //safe without exceptions
            safeReports++;
        }
        
        if(s > 0){
            for(int s = 0; s < report[i].size(); s++){    //unsafe at level 2 (0, >1<) or higher
                if(testReport(report[i], s) == 0){
                    safeReports++;
                    break;
                };
            }
        }
   
    }
    std::cout << cm.beginLog() << "PROBLEM 2 SAFE REPORT COUNT: " << safeReports << std::endl;
}


bool check(std::size_t pos){
    return pos != std::string::npos;
}

std::vector<int> tokenize(const std::string &line, const std::string &delimiters = " "){
    std::vector<int> t;

    std::size_t start_pos;
    std::size_t end_pos = 0;

    while(check(start_pos = line.find_first_not_of(delimiters, end_pos))){
        end_pos = line.find_first_of(delimiters, start_pos);
        t.push_back(atoi(line.substr(start_pos, end_pos - start_pos).c_str()));
    }
    
    return t;
}

int main(int argc, char** argv){
    char* inputFile;
    
    if(argc > 1){
        inputFile = argv[1];
    } else {
        inputFile = "input.txt";
    }

    //storage for reports
    std::vector<std::vector<int> > report;
        
    std::cout << cm.beginLog() << "AoC 2024 - Day 02" << std::endl;
    std::cout << cm.beginLog() << "Opening file: " << inputFile << std::endl;
    std::ifstream infile(inputFile);

    std::cout << cm.beginLog() << "Reading file." << std::endl;
    std::string s;
    int c = 0;
    while (std::getline(infile, s)){
        std::vector<int> t = tokenize(s);
        c++;
        report.push_back(t);
    }
    std::cout << cm.beginLog() << "Read " << c << " lines from file" << std::endl;

    problemOne(report);
    problemTwo(report);
    
    return 0;
}
