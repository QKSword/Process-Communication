#include"Namepipe.h"

int main()
{
	DWORD dwRead = 0;
	HANDLE hHandleNamepipe = NULL;
	HANDLE hEvent = NULL;

	char* ReadBuffer = (char*)malloc(PipeBufferSize);
	memset(ReadBuffer, 
		0, 
		PipeBufferSize);

	OVERLAPPED Lapped = { 0 };

	hHandleNamepipe = CreateNamedPipe(NamePipe,
		PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
		PIPE_TYPE_BYTE | PIPE_READMODE_BYTE,
		PIPE_UNLIMITED_INSTANCES,
		PipeBufferSize,
		PipeBufferSize,
		0,
		NULL);
	if (hHandleNamepipe == INVALID_HANDLE_VALUE)
	{
		printf_s("CreateNamePipe Failed：0x%x\n", GetLastError());
		goto Free;
	}

	hEvent = CreateEvent(NULL,
		TRUE,
		FALSE,
		NULL);
	if (hEvent == NULL)
	{
		printf_s("CreateEvent Failed：0x%x\n", GetLastError());
		goto Free;
	}

	Lapped.hEvent = hEvent;

	if (ConnectNamedPipe(hHandleNamepipe, 
		&Lapped) == FALSE)		//异步通信这里返回FALSE，GetLastError获取到的值为ERROR_IO_PENDING
	{
		while (true)
		{
			if (WaitForSingleObject(Lapped.hEvent, 
				INFINITE) == WAIT_FAILED)
			{
				goto Free;
			}

			ReadFile(hHandleNamepipe, 
				ReadBuffer,
				0x50,
				&dwRead, 
				NULL);
			printf_s("Receive:%s\n", ReadBuffer);
		}
	}

Free:
	if (hEvent > NULL)
	{
		CloseHandle(hEvent);
	}
	if (hHandleNamepipe > NULL)
	{
		CloseHandle(hHandleNamepipe);
	}

	return 0;
}