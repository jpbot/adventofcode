#include "chronoMessage.h"
#include <time.h>
#include <cstdio>

#define MAXFMTMESSAGE 512

double ChronoMessage::updateTime(void){
    long sec, nsec;
    clock_gettime(CLOCK_REALTIME, &last);
    sec = last.tv_sec - start.tv_sec;
    nsec = last.tv_nsec - start.tv_nsec;
    
    if(nsec < 0){
        sec--;
        nsec+= 1000000000;
    }
    
    time = (double) sec + (double) nsec / 1e9;
    return time;
}

ChronoMessage::ChronoMessage(){
    clock_gettime(CLOCK_REALTIME, &start);
    m = 0;
    buf = new char[MAXFMTMESSAGE];
}

timespec_t ChronoMessage::getStart(){ return start; }
timespec_t ChronoMessage::getLast(){ return last; }
int ChronoMessage::ChronoMessage::getMessageCount() { return m; }

char* ChronoMessage::beginLog(){
    double time;
    m++;
    time = updateTime();
    snprintf(buf, MAXFMTMESSAGE, "%05d [%.3f] ", m, time);
    return buf;
}



