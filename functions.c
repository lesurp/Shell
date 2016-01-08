#include "functions.h"
#include <stdio.h>

bool isBackgroundProc(char* buf, int nbf) {
	if ( buf[strlen(buf)-2] == '&' ) {
		buf[strlen(buf)-2] = 0;
		return true;
	} else {
		return false;
	}
}
