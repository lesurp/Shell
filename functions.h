#include <stdbool.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

extern pid_t* backgroundPidsList;
extern int sizePidsList;
extern pid_t foregroundPid;

bool isBackgroundProc(char* buf, int nbf);
void backgroundHandler(int status);
void foregroundHandler(int status);
void addPidToList(pid_t*,int, pid_t);
bool isInTheList(pid_t*,int, pid_t);

