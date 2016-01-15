#include "functions.h"
#include <stdio.h>

bool isBackgroundProc(char* buf, int nbf) {
	if ( buf[strlen(buf)-1] == '&' ) {
		buf[strlen(buf)-1] = 0;
		return true;
	} else {
		return false;
	}
}

void backgroundHandler(int signum) {
	pid_t pid;
	int i;
	switch(signum) {
		case SIGCHLD:
			while ( (pid = waitpid(-1, NULL, WNOHANG)) > 0) {
				if(isInTheList(backgroundPidsList,sizePidsList,pid)) {
					printf("A background process has terminated: %ld\n\n", (long)pid);
				}
			continue;
			}
			break;
		case SIGHUP:
			for(i = 0; i < sizePidsList; i++){
				if(backgroundPidsList[i] != 0)
				kill(backgroundPidsList[i], SIGHUP);
			}
			exit(0);
			break;
	}	
}


void foregroundHandler(int signum) {
	if(foregroundPid == -1) 
		return;

	switch(signum) {
		case SIGINT:
			kill(foregroundPid, SIGINT);
			break;
		case SIGQUIT:
			kill(foregroundPid, SIGQUIT);
			break;
	}

}

void addPidToList(pid_t* pidList, int size, pid_t pid) {
	backgroundPidsList = realloc(pidList, (size+1)*sizeof(pid));
	backgroundPidsList[sizePidsList++] = pid;
}

bool isInTheList(pid_t* pidList,int size, pid_t pid) {
	int i;
	for(i =0 ; i < size; i++) {
		if(pid == pidList[i]) {
			pidList[i] = 0;
			//pidList = realloc(pidList, (size-1)*sizeof(pid));
			//size--;
			return true;
		}
	}	
	return false;	
}
