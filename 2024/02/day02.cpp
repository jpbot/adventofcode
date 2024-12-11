#include "../util/chronoMessage.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdlib>

#define DEBUG

ChronoMessage cm;

void problemOne(std::vector<std::vector<int> > &report){
    std::cout << cm.beginLog() << "AoC 2024 - Day 02: PROBLEM 1" << std::endl;

    std::cout << cm.beginLog() << "Checking for 'safe' reports" << std::endl;
    int safeReports = 0;
    int last, direction;
    bool safeReport = false;
    for(int i = 0; i < report.size(); i++){
        if(report[i].size() > 1){
            safeReport = true;
        
            for(int p = 0; p < report[i].size(); p++){
                if(p > 0){
                    //check consistent direction (and !zero change)
                    if(report[i][p] == last){       //values must not repeat
                        safeReport = false;
        #ifdef DEBUG
        std::cout << cm.beginLog() << "problemOne: " << "check for repeated value fails (" << 
            i <<", " << p << ")." << std::endl;
        #endif
                        break;
                    }
                    if(p==1){
                        //determine direction (1 increasing, -1 decreasing)
                        direction = report[i][p]>last?1:-1;
                    } else if(direction != (report[i][p]>last?1:-1)) {
                        //if direction changed, not a safe report
                        safeReport = false;
        #ifdef DEBUG
        std::cout << cm.beginLog() << "problemOne: " << "check for direction change fails (" << 
            i <<", " << p << "). DIR=" << direction << " thisDIR=" << (report[i][p]>last?1:-1) << std::endl;
        #endif
                        break;
                    }
                    //check magnitute of change is not more than 3
                    if(abs(report[i][p]-last) > 3){
                        safeReport = false;
        #ifdef DEBUG
        std::cout << cm.beginLog() << "problemOne: " << "check for change magnitute > 3 (" << 
            i <<", " << p << "). comp (" << report[i][p] << ", " << last << 
            "), Change magnitute: " << abs(report[i][p]-last) << std::endl;
         #endif
                        break;
                    }
                }
                last = report[i][p];
            }
            if(safeReport) safeReports++;
        }

        #ifdef DEBUG
        // print a sample
        if(i < 10){
            std::cout << "  " << i << ": " << report[i][0];
            for(int p = 1; p < report[i].size(); p++){
                std::cout << ", " << report[i][p];
            } 
            std::cout << std::endl << "     |" << safeReport <<
                " reports: " << safeReports << std::endl;
        }
        #endif
    }
    std::cout << cm.beginLog() << "PROBLEM 1 SAFE REPORT COUNT:" << safeReports << std::endl;
}

void problemTwo(std::vector<std::vector<int> > &report){
    std::cout << cm.beginLog() << "AoC 2024 - Day 02: PROBLEM 2" << std::endl;

    std::cout << cm.beginLog() << "Checking for 'safe' reports" << std::endl;
    int safeReports = 0;
    int last, direction;
    bool safeReport = false;
    bool problemBuffer = false;
    for(int i = 0; i < report.size(); i++){
        if(report[i].size() > 1){
            safeReport = true;
            problemBuffer = false;
        
            for(int p = 0; p < report[i].size(); p++){
                if(p > 0){
                    //check consistent direction (and !zero change)
                    if(report[i][p] == last){       //values must not repeat
                        if(problemBuffer){
                            safeReport = false;
        #ifdef DEBUG
        std::cout << cm.beginLog() << "problemOne: " << "check for repeated value fails (" << 
            i <<", " << p << ")." << std::endl;
        #endif
                            break;
                        }
                        problemBuffer = true;
                    }
                    if(p==1){
                        //determine direction (1 increasing, -1 decreasing)
                        direction = report[i][p]>last?1:-1;
                    } else if(direction != (report[i][p]>last?1:-1)) {
                        //if direction changed, not a safe report
                        if(problemBuffer){
                            safeReport = false;
        #ifdef DEBUG
        std::cout << cm.beginLog() << "problemOne: " << "check for direction change fails (" << 
            i <<", " << p << "). DIR=" << direction << " thisDIR=" << (report[i][p]>last?1:-1) << std::endl;
        #endif
                            break;
                        }
                        problemBuffer = true;
                    }
                    //check magnitute of change is not more than 3
                    if(abs(report[i][p]-last) > 3){
                        if(problemBuffer){
                            safeReport = false;
        #ifdef DEBUG
        std::cout << cm.beginLog() << "problemOne: " << "check for change magnitute > 3 (" << 
            i <<", " << p << "). comp (" << report[i][p] << ", " << last << 
            "), Change magnitute: " << abs(report[i][p]-last) << std::endl;
         #endif
                          break;
                        }
                        problemBuffer = true;
                    }
                }
                if(!problemBuffer) last = report[i][p];
            }
            if(safeReport) safeReports++;
        }

        #ifdef DEBUG
        // print a sample
        if(i < 10){
            std::cout << "  " << i << ": " << report[i][0];
            for(int p = 1; p < report[i].size(); p++){
                std::cout << ", " << report[i][p];
            } 
            std::cout << std::endl << "     |" << safeReport <<
                " reports: " << safeReports << std::endl;
        }
        #endif
    }
    std::cout << cm.beginLog() << "PROBLEM 2 SAFE REPORT COUNT:" << safeReports << std::endl;
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
//        if(c < 5){
//            std::cout << "  " << c << ">" << s << std::endl;
//            std::cout << "    ->";
//                for(int i=0; i< t.size(); i++)
//                    if(i > 0)
//                        std::cout << ", " << t[i];
//                    else
//                        std::cout << t[i];
//                std::cout << "\n";
//        }
        report.push_back(t);
    }
    std::cout << cm.beginLog() << "Read " << c << " lines from file" << std::endl;

    problemOne(report);
    problemTwo(report);
    
    return 0;
}
