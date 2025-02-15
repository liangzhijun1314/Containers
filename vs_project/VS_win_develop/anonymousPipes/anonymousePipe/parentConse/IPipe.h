#pragma once
#include <Windows.h>
class IPipe
{
public:
	virtual bool CreatePipe(HANDLE& hReadPipe, HANDLE& hWritePipe, SECURITY_ATTRIBUTES& lpPipeAttributes, DWORD nBuffSize) = 0;
	virtual bool ClosePipe(HANDLE hPipe) = 0;
};