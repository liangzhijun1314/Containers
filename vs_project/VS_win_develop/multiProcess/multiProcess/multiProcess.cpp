﻿// multiProcess.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <windows.h>
#include <tchar.h>
#include <iostream>

int main()
{
    std::cout << "Hello World!\n";

	int chan_num = 4;
	int uiChildProcNum = 0;
	int uiForkErrorFlag = 0;
	int rv = 0;
	int i = 0;
	STARTUPINFO si[chan_num] = { nullptr };
	PROCESS_INFORMATION pi[chan_num] = { nullptr };
	char strCmdLine[480];
	char * pucDevName[chan_num] = { nullptr };
	char * puiDevType[chan_num] = { nullptr };
	HANDLE lpHandles[chan_num] = { nullptr };
	char * strDevType;

	for (i = 0; i < chan_num; i++)
	{
		memset(&si[i],0, sizeof(si[i]));
		si[i].cb = sizeof(si[i]);
		memset(&pi[i], 0, sizeof(pi[i]));
		memset(strCmdLine, 0, sizeof(strCmdLine));
		strcpy(strCmdLine, "ctv-4k-monitor.exe");
		strcat(strCmdLine, "");
		strcat(strCmdLine, pucDevName[i]);
		memset(strDevType, 0, sizeof(strDevType));
		sprintf(strDevType, "%d", puiDevType[i]);
		strcat(strCmdLine, " ");
		strcat(strCmdLine, strDevType);

		if (!CreateProcess(NULL,
			strCmdLine,
			NULL,
			NULL,
			FALSE,
			0,
			NULL,
			NULL,
			&si[i],
			&pi[i])
			)
		{
			// create child process failed

			uiChildProcNum++;
			lpHandles[i] = pi[i].hProcess;
		}
	}

	END;
	if ((uiForkErrorFlag == 1) && (uiChildProcNum > 0))
	{
		//终止其余子进程
		for (i = 0; i < uiChildProcNum; i++)
		{
			TerminateProcess(pi[i].hProcess, 127);
			Sleep(60);
			CloseHandle(pi[i].hThread);
			CloseHandle(pi[i].hProcess);
		}
	}
	else if (uiChildProcNum > 0)
	{
		rv = WaitForMultipleObjects(uiChildProcNum, lpHandles, FALSE, INFINITE);
		if ((rv >= WAIT_OBJECT_0) && (rv <= WAIT_OBJECT_0 + uiChildProcNum - 1))
		{
			CloseHandle(pi[rv].hThread);

			CloseHandle(pi[rv].hProcess);
		}  //终止其余子进程
		for (i = 0; i < uiChildProcNum; i++)
		{
			if (i != rv)
			{
				TerminateProcess(pi[i].hProcess, 127);

				Sleep(60);

				CloseHandle(pi[i].hThread);

				CloseHandle(pi[i].hProcess);
			}
		}
	}
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
