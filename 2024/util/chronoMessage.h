#include <time.h>

class ChronoMessage {
private:
    timespec_t start, last;
    double time;
    int m;
    char *buf;

    double updateTime(void);

public:
    ChronoMessage();

    timespec_t getStart();
    timespec_t getLast();
    int getMessageCount();

    char* beginLog();
};
