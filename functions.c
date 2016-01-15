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
				if(isInTheList(sizePidsList,pid)) {
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

void addPidToList(int size, pid_t pid) {
	backgroundPidsList = realloc(backgroundPidsList, (size+1)*sizeof(pid));
	backgroundPidsList[sizePidsList++] = pid;
}

bool isInTheList(int size, pid_t pid) {
	int i;
	for(i =0 ; i < size; i++) {
		if(pid == backgroundPidsList[i]) {
			backgroundPidsList[i] = backgroundPidsList[size-1];
			backgroundPidsList = realloc(backgroundPidsList, (size-1)*sizeof(pid));
			size--;
			return true;
		}
	}	
	return false;	
}
