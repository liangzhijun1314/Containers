#include <Windows.h>
#include <iostream>

using namespace std;
int main()
{
	HANDLE hStdin, hStdout;
	char buff[256] = { 0 };
	char temp[] = "q";
	char* QUIT = temp;
	DWORD dwRead;
	DWORD dwWrite;
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE || hStdout == INVALID_HANDLE_VALUE)
	{
		return 1;
	}
	std::cout << "client is working!" << std::endl;
	while (1)
	{
		std::cout << "client is working  in while!" << std::endl;
		if (ReadFile(hStdin, buff, 256, &dwRead, NULL) && buff[0] != 0)
		{
			std::cout << "buffer : " << buff << std::endl;
			if (strcmp(buff, QUIT) == 0)
				return 0;
			else
			{
				cout << buff << endl;
				//WriteFile(hStdout, buff, 256, &dwWrite, NULL); there is someting interesting if you use this instead of before one.
				ZeroMemory(buff, sizeof buff);
			}

		}

		Sleep(500);
	}
	cout << "client will shutdown in 3 sec!" << endl;
	Sleep(3000);
	return 0;
}