#pragma once

#include <Windows.h>

#include <tlhelp32.h>
#include <iostream>
#include <direct.h>

using namespace std;

namespace color
{
	inline std::ostream& white(std::ostream &s)
	{
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		return s;
	}

	inline std::ostream& blue(std::ostream &s)
	{
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		return s;
	}

	inline std::ostream& red(std::ostream &s)
	{
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_INTENSITY);
		return s;
	}

	inline std::ostream& green(std::ostream &s)
	{
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		return s;
	}
}

namespace process
{
	DWORD process(char* ProcessName)
	{
		HANDLE hPID = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
		PROCESSENTRY32 ProcEntry;
		ProcEntry.dwSize = sizeof(ProcEntry);
		do
			if (!strcmp(ProcEntry.szExeFile, ProcessName))
			{
				DWORD dwPID = ProcEntry.th32ProcessID;
				CloseHandle(hPID);
				return dwPID;
			}
		while (Process32Next(hPID, &ProcEntry));
	}

	bool inject(DWORD pid, char* dll)
	{
		char myDLL[MAX_PATH];
		GetFullPathName(dll, MAX_PATH, myDLL, 0);

		HANDLE hProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, pid);

		LPVOID allocatedMem = VirtualAllocEx(hProcess, NULL, sizeof(myDLL), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
		WriteProcessMemory(hProcess, allocatedMem, myDLL, sizeof(myDLL), NULL);

		CreateRemoteThread(hProcess, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibrary, allocatedMem, 0, 0);

		CloseHandle(hProcess);
		
		return true;
	}
}

