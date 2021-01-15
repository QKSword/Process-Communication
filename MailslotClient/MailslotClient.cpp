#include"Mailslot.h"

int main()
{
	DWORD dwWrite = 0;
	HANDLE hHandle = NULL;

	char* WriteBuffer = (char*)malloc(MailslotBufferSize);
	memset(WriteBuffer,
		0,
		MailslotBufferSize);

	hHandle = CreateFile(MailslotName,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (hHandle == INVALID_HANDLE_VALUE)
	{
		printf_s("CreateFile Failed£º0x%x", GetLastError());
		goto Free;
	}
	
	while (true)
	{
		printf_s("Send Buffer:");
		scanf_s("%s", WriteBuffer, 0x50);
		WriteFile(hHandle,
			WriteBuffer,
			0x50,
			&dwWrite,
			NULL);
	}

Free:
	if (hHandle != NULL)
	{
		CloseHandle(hHandle);
	}
}