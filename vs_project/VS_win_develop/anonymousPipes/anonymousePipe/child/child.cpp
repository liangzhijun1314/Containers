#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>

#define BUFSIZE 4096

int main(void)
{
	CHAR chBuf[BUFSIZE];
	DWORD dwRead, dwWritten;
	HANDLE hStdin, hStdout;
	BOOL bSuccess;

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (
		(hStdout == INVALID_HANDLE_VALUE) ||
		(hStdin == INVALID_HANDLE_VALUE)
		)
		ExitProcess(1);

	// Send something to this process's stdout using printf.
	printf("\n ** This is a message from the child process. ** \n");

	// This simple algorithm uses the existence of the pipes to control execution.
	// It relies on the pipe buffers to ensure that no data is lost.
	// Larger applications would use more advanced process control.

	for (;;)
	{
		std::cout << "-------------------child-------- read and write---------" << std::endl;
		// Read from standard input and stop on error or no data.
		bSuccess = ReadFile(hStdin, chBuf, BUFSIZE, &dwRead, NULL);

		if (!bSuccess || dwRead == 0)
		{
			std::cout << "child read over or error" << std::endl;
			break;
		}
		else
			std::cout << "child read pipe ok , read data : " << chBuf  << "; dwRead = " << dwRead << std::endl;

		// Write to standard output and stop on error.
		bSuccess = WriteFile(hStdout, chBuf, dwRead, &dwWritten, NULL);

		if (!bSuccess)
		{
			std::cout << "child WriteFile error" << std::endl;
			break;
		}
		else
			std::cout << "child write pipe ok , write data : "<< chBuf << std::endl;
	}
	return 0;
}