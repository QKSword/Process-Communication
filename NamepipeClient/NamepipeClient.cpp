#include"Namepipe.h"

int main()
{
	HANDLE hHandleNamepipe = NULL;
	DWORD dwWrite = 0;

	char* WriteBuffer = (char*)malloc(PipeBufferSize);
	memset(WriteBuffer, 0, PipeBufferSize);

	if (WaitNamedPipe(NamePipe, NMPWAIT_WAIT_FOREVER) == FALSE)
	{
		printf_s("WaitNamepipe failed£º0x%x\n", GetLastError());
		goto Free;
	}

	hHandleNamepipe = CreateFile(NamePipe,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (hHandleNamepipe == INVALID_HANDLE_VALUE)
	{
		printf_s("Open NamePipe Failed£º0x%x\n", GetLastError());
		goto Free;
	}

	memset(WriteBuffer, 0x55, 0x50);
	WriteFile(hHandleNamepipe, WriteBuffer, 0x50, &dwWrite, NULL);
	
Free:

	if (hHandleNamepipe > NULL)
	{
		CloseHandle(hHandleNamepipe);
	}

	return 0;
}