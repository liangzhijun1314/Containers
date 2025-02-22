// 参考 https://www.cnblogs.com/Baesky/archive/2012/08/12/windows_pipe_anonymous_pipe.html
// 该例子是一个单工的匿名管道
#include "UnNamePipe.h"
#include <iostream>
#include <Windows.h>

using namespace std;

HANDLE g_hReadPipe;
HANDLE g_hWritePipe;
HANDLE g_cReadPipe;
HANDLE g_cWritePipe;

int main()
{
	LPTSTR errbuff;
	char strBuff[256] = { 0 };

	char temp[] = "q";
	char* QUITCHAR = temp;
	CUnNamedPipe myPipe;
	SECURITY_ATTRIBUTES saAttr;
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE;
	saAttr.lpSecurityDescriptor = NULL;
	STARTUPINFO siStartInfo;
	PROCESS_INFORMATION piProcInfo;
	DWORD nWriteTo;
	TCHAR szAppName[] = TEXT("childConse.exe");
	if (!myPipe.CreatePipe(g_hReadPipe, g_hWritePipe, saAttr, 0))
	{
		DWORD d = GetLastError();
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_IGNORE_INSERTS |
			FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			d,
			LANG_NEUTRAL,
			(LPTSTR)& errbuff,
			0,
			NULL);
		std::cout << "can not create pipe 1!" << std::endl;
		return 1;
	}

	if (!SetHandleInformation(g_hReadPipe, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT))
	{
		std::cout << "set handle property error!" << std::endl;
	}
	/*if(!SetHandleInformation(g_hWritePipe, HANDLE_FLAG_INHERIT, 0))
	{
		cout<<"set handle property error!"<<endl;
	}*/
	ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
	siStartInfo.cb = sizeof(STARTUPINFO);
	siStartInfo.hStdInput = g_hReadPipe;
	siStartInfo.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

	if (!CreateProcess(NULL, szAppName, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &siStartInfo, &piProcInfo))
	{
		DWORD d = GetLastError();
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_IGNORE_INSERTS |
			FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			d,
			LANG_NEUTRAL,
			(LPTSTR)& errbuff,
			0,
			NULL);

		std::cout << "can't create process:" << szAppName << std::endl;
		std::cout << errbuff;
		return 0;
	}
	std::cout << "press q to quit, others to show!" << std::endl;
	while (cin >> strBuff)
	{
		while (strBuff[0] != 0)
		{
			if (!WriteFile(g_hWritePipe, strBuff, sizeof strBuff, &nWriteTo, NULL))
			{
				cout << "write file error!" << endl;
				break;
			}
			if (strcmp(strBuff, QUITCHAR) == 0)
			{
				return 0;;
			}
			ZeroMemory(strBuff, sizeof(strBuff));
		}

	}
	CloseHandle(piProcInfo.hProcess);
	CloseHandle(piProcInfo.hThread);

	myPipe.ClosePipe(g_hReadPipe);
	myPipe.ClosePipe(g_hWritePipe);

	return 0;
}