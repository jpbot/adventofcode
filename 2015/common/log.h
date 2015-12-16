// Logging
#ifndef LOG_H
#define LOG_H

#define ERRDEBUG 0
#define ERRINFO 1
#define ERRWARN 2
#define ERRERROR 3
#define ERRFATAL 4

int loggerf(int level, char *fmt, ...);

#endif
