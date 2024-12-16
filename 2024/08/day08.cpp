#include "../util/chronoMessage.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <set>
#include <string>
#include <cstdlib>

ChronoMessage cm;

class Coord{
    public:
        int x;
        int y;
        Coord(int x = 0, int y = 0){this->x = x; this->y = y;}
        
        bool operator<(const Coord &other) const {
            if(this->y == other.y)
                return this->x < other.x;
            return this->y  < other.y;
        }
};

class Antennas{
    private:
        bool calculated;
        char frequency;
        int xsize;
        int ysize;
        unsigned long validAntinodes;
        std::deque<Coord> coords;
        std::deque<Coord> antiNodes;

        unsigned long calcAntinode(bool addHead = false, bool verbose = false){
            int x, y;
            int xSlope, ySlope;

            //generate list of antinodes
            if(!addHead){
                validAntinodes = 0;
                antiNodes.clear();
            }
            
            //need to know map size
            if(xsize < 1 || ysize < 1)
                return -1;
            
            for(int a = 0; a < (addHead?1:coords.size()); a++){
                for(int b = a + 1; b < coords.size(); b++){
                    if(verbose){
                        std::cout << "antenna(1): (" << coords[a].x << ", " << coords[a].y << ")   ";
                        std::cout << "antenna(2): (" << coords[b].x << ", " << coords[b].y << ")" << std::endl;
                    }

                    //slope
                    xSlope = coords[a].x - coords[b].x;
                    ySlope = coords[a].y - coords[b].y;

                    //figure out antinode 1
                    x = coords[a].x + xSlope;
                    y = coords[a].y + ySlope;
                    if(x < xsize && y < ysize && x >= 0 && y >= 0){
                        Coord a1 (x, y);
                        antiNodes.push_back(a1);
                        validAntinodes++;
                        if(verbose)
                            std::cout << "   antinode(1): (" << x << ", " << y << ")";
                    }
                    else if(verbose)
                        std::cout << "   antinode(-): (" << x << ", " << y << ")";
                

                    //figure out antinode 2
                    x = coords[b].x - xSlope;
                    y = coords[b].y - ySlope;
                    if(x < xsize && y < ysize && x >= 0 && y >= 0){
                        Coord a2 (x, y);
                        antiNodes.push_back(a2);
                        validAntinodes++;
                        if(verbose)
                            std::cout << "   antinode(2): (" << x << ", " << y << ")";
                    }
                    else if(verbose)
                        std::cout << "   antinode(-): (" << x << ", " << y << ")";

                    if(verbose)
                        std::cout << std::endl;
                }
            }

            calculated = true;
            return validAntinodes;
        }

    public:
        char getFrequency()         {return frequency;}
        char setFrequency(char f)   {return frequency = f;}
        void setMapSize(int x, int y)   {xsize = x;  ysize = y;}
        unsigned long getCoordCount()         {return coords.size();}
        unsigned long getAntinodeCount(){
            if(!calculated)
                return calcAntinode();
            return validAntinodes;
        }

        Antennas(){
            validAntinodes = 0;
            calculated = false;
            frequency = 0;
            xsize = 0;
            ysize = 0;
        }

        Antennas(char f){
            Antennas();
            setFrequency(f);
        }

        Antennas(char f, int x, int y){
            Antennas();
            setFrequency(f);
            pushAntenna(x, y, false);
        }

        Antennas(char f, int x, int y, int mapSizeX, int mapSizeY){
            Antennas();
            setFrequency(f);
            pushAntenna(x, y, false);
            setMapSize(mapSizeX, mapSizeY);
        }


        Coord pushAntenna(int x, int y, bool calc = false){
            Coord c (x, y);
            if(calc){
                coords.push_front(c);
                calcAntinode(true);
            } else {
                coords.push_back(c);
                calculated = false;
            }
            return c;
        }

        void debug(){
            std::cout << cm.beginLog() << "frequency: " << frequency << " (" << coords.size() << ")"<< std::endl;
            calcAntinode(false, true);
        }
        
        std::deque<Coord> & getAntinodes()  {
            if(!calculated)
                calcAntinode();

            return antiNodes;
        }
            
};

void printAntennaCounts(std::map<char, Antennas> frequencies){
    int c = 0;
    int totalAntinodes = 0;

    for(std::map<char, Antennas>::iterator i = frequencies.begin(); i != frequencies.end(); i++){
        totalAntinodes = totalAntinodes + (int) i->second.getAntinodeCount();
        std::cout << cm.beginLog() << "Antenna " << ++c << ": " << i->first << " (" << i->second.getCoordCount() << ")." 
            << " Antinodes: " << i->second.getAntinodeCount() << "/" << totalAntinodes << "." << std::endl;
    }
}

unsigned long deDupeAntinodes(std::map<char, Antennas> f, std::set<Coord> & antinodes, bool verbose = false){
    int count = 0;
    if(verbose)
        std::cout << "   Antinodes:" << std::endl;

    for(std::map<char, Antennas>::iterator it = f.begin(); it != f.end(); it++){
        for(std::deque<Coord>::iterator c_it = it->second.getAntinodes().begin();
            c_it != it->second.getAntinodes().end(); c_it++){
                if(verbose)
                    std::cout << "   " << ++count << " (" << c_it->x << ", " << c_it->y << ")" << std::endl;
                Coord c = *c_it;
                antinodes.insert(*c_it);
            }
    }

    return antinodes.size();
}

void printAntinodes(std::set<Coord> & antinodes){
    int count = 0;
    std::cout << "   Antinodes:" << std::endl;

    for(std::set<Coord>::iterator it = antinodes.begin(); it != antinodes.end(); it++){
        std::cout << "   " << ++count << " (" << it->x << ", " << it->y << ")" << std::endl;
    }
}

int main(int argc, char** argv){
    char* inputFile;
    int maxX = 0;
    int totalAntinodes = 0;
    std::map<char, Antennas> frequencies;
    std::set<Coord> antinodes;
    
    if(argc > 1){
        inputFile = argv[1];
    } else {
        inputFile = "input.txt";
    }

    //storage for map
    std::vector<std::vector<char> > antennaMap;
    std::vector<std::vector<char> > cleanMap;
        
    std::cout << cm.beginLog() << "AoC 2024 - Day 08" << std::endl;
    std::cout << cm.beginLog() << "Opening file: " << inputFile << "." << std::endl;
    std::ifstream infile(inputFile);

    std::cout << cm.beginLog() << "Reading file." << std::endl;
    std::string s;
 
     while (std::getline(infile, s)){
        std::vector<char> t (s.begin(), s.end());
        if(s.length() > maxX)
            maxX = (int) s.length();
        antennaMap.push_back(t);
    }
    std::cout << cm.beginLog() << "Read " << antennaMap.size() << " lines from file." << std::endl;
    std::cout << cm.beginLog() << "Map Size: " << maxX << "X" << antennaMap.size() << "." << std::endl;
    std::cout << cm.beginLog() << "Initializing map data." << std::endl;

    for(int y = 0; y < antennaMap.size(); y++){
        for(int x = 0; x < antennaMap[y].size(); x++){
            char f = antennaMap[y][x];
            if(f != '.'){
                if(frequencies.count(f)){
                    frequencies[f].pushAntenna(x, y);
                } else {
                    frequencies[f] = Antennas(f, x, y, maxX, (int) antennaMap.size());
                }
            }
        }
    }

    std::cout << cm.beginLog() << "Initializing map data: COMPLETE." << std::endl;

    // for(std::map<char, Antennas>::iterator i = frequencies.begin(); i != frequencies.end(); i++){
    //     totalAntinodes += (int) i->second.getAntinodeCount();
    // //    i->second.debug();
    // }

    // printAntennaCounts(frequencies);
    
    // deDupeAntinodes(frequencies, antinodes);
    // printAntinodes(antinodes);

    //frequencies.begin()->second.debug();

    std::cout << cm.beginLog() << "TOTAL ANTINODES ON MAP: " << deDupeAntinodes(frequencies, antinodes) << "." << std::endl;

    return 0;
}
