#include "parse.h"


char* currentDataTime() {
	time_t now = time(0);
	struct tm tstruct;
	char buf[20];
	localtime_s(&tstruct, &now);
	strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
	return buf;
}


void get_pid()
{
	while (true)
	{
		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		PROCESSENTRY32 ProcessEntry32;
		BOOL bProcessFound;
		ProcessEntry32.dwSize = sizeof(PROCESSENTRY32);

		char buf[20];
		strncpy_s(buf, sizeof(buf), currentDataTime(), 20);
		if (hSnapshot)
		{
			bProcessFound = Process32First(hSnapshot, &ProcessEntry32);
			while (bProcessFound)
			{
				cout << endl;
				printf("%s [PID : %d] [Parent PID : %d] %ws]", buf, ProcessEntry32.th32ProcessID, ProcessEntry32.th32ParentProcessID, ProcessEntry32.szExeFile);
				bProcessFound = Process32Next(hSnapshot, &ProcessEntry32);
			}
		}
		Sleep(1000);
	}
}