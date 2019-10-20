#ifndef STDAFX_H
#define STDAFX_H

#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>	// waitpid()
#include <string.h>
#include <iostream>

#define APP_NAME "fork_multi_process"
#define CHANNEL_NUMBER_ALL 4



void init_glog(const char* logpath, const char* appname);

#endif //STDAFX_H