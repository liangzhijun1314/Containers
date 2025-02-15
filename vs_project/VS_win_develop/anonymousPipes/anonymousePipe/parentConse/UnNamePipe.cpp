#include "UnNamePipe.h"

CUnNamedPipe::CUnNamedPipe()
{
}

CUnNamedPipe::~CUnNamedPipe()
{
}


bool CUnNamedPipe::CreatePipe(HANDLE& hReadPipe, HANDLE& hWritePipe, SECURITY_ATTRIBUTES& lpPipeAttributes, DWORD nBuffSize)
{
	return ::CreatePipe(&hReadPipe, &hWritePipe, &lpPipeAttributes, nBuffSize);
}

bool CUnNamedPipe::ClosePipe(HANDLE hPipe)
{
	return CloseHandle(hPipe);
}