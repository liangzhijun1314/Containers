/*
*	此示例主要目的时练习同时创建多个子进程
*	参考链接 ： https://blog.csdn.net/aspireone/article/details/7372213
*				https://blog.csdn.net/poject/article/details/85456329
*/
#include "stdafx.h"
#include "ctv-jsonprocess.h"

void readConfig()
{
	std::string jdata = JsonProcess::readfile("./config/config.json");
	std::cout << "jdata = " << jdata  << "; pid = " << getpid() << std::endl;
	JsonProcess::parseConfig(jdata);
}
int main()
{
	//正确的使用Linux中的用fork()由一个父进程创建同时多个子进程
	std::cout << "The correct way to create multiple processes in linux." << std::endl;
	printf("before fork(), pid = %d\n", getpid());
	init_glog("./log/", APP_NAME);
	readConfig();

	pid_t pid_status = 0;// 
	int chan_idx = 0;	 // 板卡通道索引
	char cmd[16] = { 0, };

	for (chan_idx = 0; chan_idx < CHANNEL_NUMBER_ALL; chan_idx++)
	{
		pid_status = fork();

		if (0 == pid_status || -1 == pid_status)
			break;
		//每次循环时，如果发现是子进程就直接从创建子进程的循环中跳出来，
		//不让你进入循环，这样就保证了每次只有父进程来做循环创建子进程的工作
	}

	if (-1 == pid_status)
	{
		//error
		printf("error, pid = %d, pid_idx_board = %d\n", getpid(), chan_idx);
		wait(NULL);
	}
	else if (0 == pid_status) //每个子进程都会执行的代码
	{
		printf("ok do something, pid = %d, pid_status = %d, pid_idx_board = %d\n", getpid(), pid_status, chan_idx);
		
		// ok do something
	}
	else
	{
		printf("parent process, pid = %d\n", getpid());
		//parent process
	}

	//父进程中回收资源
	if (pid_status > 0)
	{
		//childpid is child process pid in the parent process
		printf("FIRST PROCESS:parent create process finished! waiting for children pid=%d childpid=%d \n", getpid(), pid_status);
		sprintf(cmd, "ps -ef | grep %d", getpid());
		system(cmd);
		printf("\n\n %s \n\n", cmd);
		wait(NULL);
		printf("FIRST PROCESS: all exit & wait over pid=%d \n", getpid());
	}
	else
	{
		printf("  <--pid=%d  ppid=%d childpid=%d idx=%d will exit \n", getpid(), getppid(), pid_status, chan_idx);
	}


	return 0;
}

//int main()
//{
//	//特点：同时创建多个子进程，每个子进程可以执行不同的任务，程序 可读性较好，便于分析，易扩展为多个子进程
//    printf("hello from fork_multi_process!\n");
//	printf("before fork(), pid = %d\n", getpid());
//
//	pid_t p1 = fork();
//	if (p1 == 0)
//	{
//		printf("in child 1, pid = %d\n", getpid());
//		return 0;
//	}
//
//	pid_t p2 = fork();
//	if (p2 == 0)
//	{
//		printf("in child 2, pid = %d\n", getpid());
//		return 0;
//		printf("hello world \n");
//	}
//
//	int st1, st2;
//	waitpid(p1, &st1, 0);  //waitpid() 暂时停止目前进程的执行，直到有信号来到或子进程结束。
//	waitpid(p2, &st2, 0);
//
//	printf("in parent, child 1 pid =%d\n", p1);
//	printf("in parent, child 2 pid =%d\n", p2);
//
//	printf("in parent, pid =%d\n", getpid());
//
//	printf("in parent, child 1 exited with %d\n", st1);
//	printf("in parent, child 2 exited with %d\n", st2);
//    return 0;
//}