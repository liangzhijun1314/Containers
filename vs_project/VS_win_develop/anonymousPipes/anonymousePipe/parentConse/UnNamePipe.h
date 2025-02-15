#pragma once
#include "IPipe.h"

class CUnNamedPipe :public IPipe
{
public:
	CUnNamedPipe(void);
	~CUnNamedPipe(void);

	bool CreatePipe(HANDLE& hReadPipe, HANDLE& hWritePipe, SECURITY_ATTRIBUTES& lpPipeAttributes, DWORD nBuffSize);
	bool ClosePipe(HANDLE hPipe);
};
