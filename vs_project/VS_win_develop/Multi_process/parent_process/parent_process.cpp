﻿// Multi_process.cpp : 定义控制台应用程序的入口点。
// 参考：https://blog.csdn.net/bzhxuexi/article/details/23950701
// 参考：https://blog.csdn.net/think_A_lot/article/details/100980104
//		 https://www.cnblogs.com/MakeView660/p/7755374.html
//

#include "stdafx.h"
#define CHANNEL_NUMBER 4

int main()
{
	char cWindowsDirectory[MAX_PATH];

	//获取当前进程伪句柄
	HANDLE hProcess = NULL;
	hProcess = GetCurrentProcess();
	std::cout << "Current virtual handle = " << hProcess << std::endl;

	DuplicateHandle(GetCurrentProcess(), GetCurrentProcess(),
		GetCurrentProcess(), &hProcess,
		0,
		FALSE,
		DUPLICATE_SAME_ACCESS);

	std::cout << "Current real handle = " << hProcess << std::endl;

	DWORD dwProcessID = 0;
	dwProcessID = GetCurrentProcessId();
	std::cout << "parent pid = " << dwProcessID << std::endl;

	//LPTSTR 与 wchar_t* 等价(Unicode环境下)
	LPTSTR cWinDir = new TCHAR[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, cWinDir);

	//// 获取待执行的exe路径
	//char buff[1000];
	//// 当前路径
	//_getcwd(buff, 1000);
	//std::string dir = buff;
	//// 路径组装
	//std::string exePath = dir + std::string("\\ctv-4k-monitor.exe");
	//std::cout << "exePath = " << exePath << std::endl;

	//LPTSTR sConLin = _tcsdup(TEXT("F:\\share\\lzj\\source\\SignalCapServer-multiprocess\\x64\\Debug\\ctv-4k-monitor.exe"));
	

	std::vector<PROCESS_INFORMATION> piList;
	int board_num = 0;
	int channel_num = 0;
	int port = 8001;
	for (int i = 0; i < CHANNEL_NUMBER; i++)
	{
		DWORD dwExitCode;//用于保存子程进的返回值;

		LPTSTR sConLin = _tcsdup(TEXT(""));
		
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&si, sizeof(si));
		ZeroMemory(&pi, sizeof(pi));

		switch (i)
		{
		case 0:
			board_num = 0;
			channel_num = 0;
			port = 8001;
			sConLin = _tcsdup(TEXT("F:\\share\\lzj\\source\\SignalCapServer-multiprocess\\x64\\Debug\\ctv-4k-monitor.exe 0 0 8001"));
			break;
		case 1:
			board_num = 0;
			channel_num = 1;
			port = 8002;
			sConLin = _tcsdup(TEXT("F:\\share\\lzj\\source\\SignalCapServer-multiprocess\\x64\\Debug\\ctv-4k-monitor.exe 0 1 8002"));
			break;
		case 2:
			board_num = 1;
			channel_num = 0;
			port = 8003;
			sConLin = _tcsdup(TEXT("F:\\share\\lzj\\source\\SignalCapServer-multiprocess\\x64\\Debug\\ctv-4k-monitor.exe 1 0 8003"));
			break;
		case 3:
			board_num = 1;
			channel_num = 1;
			port = 8004;
			sConLin = _tcsdup(TEXT("F:\\share\\lzj\\source\\SignalCapServer-multiprocess\\x64\\Debug\\ctv-4k-monitor.exe 1 1 8004"));
			break;
		default:
			break;
		}
		TCHAR temp[2048];

		//创建一个新进程
		if (!CreateProcess(
			NULL,	//	指向一个NULL结尾的、用来指定可执行模块的宽字节字符串
			sConLin,//	命令行字符串
			NULL,	//	指向一个SECURITY_ATTRIBUTES结构体，这个结构体决定是否返回的句柄可以被子进程继承。
			NULL,	//	如果lpProcessAttributes参数为空（NULL），那么句柄不能被继承。<同上>
			false,	//	指示新进程是否从调用进程处继承了句柄。
			CREATE_SUSPENDED,	//	指定附加的、用来控制优先类和进程的创建的标
					//	CREATE_NEW_CONSOLE	新控制台打开子进程
					//	CREATE_SUSPENDED	子进程创建后挂起，直到调用ResumeThread函数
			NULL,	//	指向一个新进程的环境块。如果此参数为空，新进程使用调用进程的环境
			NULL,	//	指定子进程的工作路径
			&si,	//	决定新进程的主窗体如何显示的STARTUPINFO结构体
			&pi		//	接收新进程的识别信息的PROCESS_INFORMATION结构体
		))
		{
			std::cerr << "failed to create process" << std::endl;	
		}
		else
		{
			std::cout << "create process success" << std::endl;

			DWORD childPID = 0;
			childPID = GetCurrentProcessId();
			std::cout << "child pid = " << childPID << std::endl;

			//The child process terminated;  
			//get its exit code.  
			GetExitCodeProcess(pi.hProcess,&dwExitCode);        
			std::cout << "process return code:" << dwExitCode << std::endl;

			////Close the thread handle as soon as  
			////it is no longer needed!  
			//CloseHandle(pi.hThread);

			////Suspend our execution until  
			////the child has terminated.  
			//WaitForSingleObject(pi.hProcess, INFINITE);

			

			////Close the process handle as soon as  
			////it is no longer needed.  
			//CloseHandle(pi.hProcess);


			piList.push_back(pi);
			std::cout << "start process end ." << std::endl;

			//下面两行关闭句柄，解除本进程和新进程的关系，不然有可能不小心调用TerminateProcess函数关掉子进程
			//		CloseHandle(pi.hProcess);
			//		CloseHandle(pi.hThread);
		}
	}

	Sleep(1000);
	// 同步启动子进程
	for (PROCESS_INFORMATION pinfo : piList) {
		ResumeThread(pinfo.hThread);
	}

	////终止子进程
	//TerminateProcess(pi.hProcess, 300);
	//终止本进程，状态码
	ExitProcess(1001);

	return 0;
}


/*

#include <locale.h>
#include <Windows.h>

int main()
{
	PROCESS_INFORMATION ProInfo;

	STARTUPINFO StartInfo;
	ZeroMemory(&StartInfo, sizeof(StartInfo));

	LPTSTR szPrameter = TEXT("C:\\Users\\DELL\\Desktop\\YuvPlayer\\RawViewer.exe");
	TCHAR szCmdLine[2048] = { 0 };
	CopyMemory(szCmdLine, szPrameter, 2 * _tcslen(szPrameter));

	ZeroMemory(&ProInfo, sizeof(ProInfo));

	if (!CreateProcess(NULL,
		szCmdLine,
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&StartInfo,
		&ProInfo)
		)
	{
		_tprintf(TEXT("CreateProcess failed : %d\n"), GetLastError());
		return(-1);
	}

	WaitForSingleObject(ProInfo.hProcess, INFINITE);

	CloseHandle(ProInfo.hProcess);
	CloseHandle(ProInfo.hThread);

	return 0;
}

*/