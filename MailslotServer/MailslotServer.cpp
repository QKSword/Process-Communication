#include"Mailslot.h"

int main()
{
	HANDLE hHandle = NULL;
	DWORD dwRead = 0;

	char* ReadBuffer = (char*)malloc(MailslotBufferSize);
	memset(ReadBuffer, 
		0, 
		MailslotBufferSize);

	hHandle = CreateMailslot(MailslotName,
		0,
		MAILSLOT_WAIT_FOREVER,
		NULL);
	if (hHandle == INVALID_HANDLE_VALUE)
	{
		printf_s("CreateMailslot Failed£º0x%x", GetLastError());
		goto Free;
	}

	while (true)
	{
		ReadFile(hHandle,
			ReadBuffer,
			0x50,
			&dwRead,
			NULL);
		printf_s("Receive:%s\n", ReadBuffer);
	}

Free:
	if (hHandle != NULL)
	{
		CloseHandle(hHandle);
	}
}