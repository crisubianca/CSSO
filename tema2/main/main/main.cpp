#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <string>

using namespace std;

#define BUFFER_SIZE 256
TCHAR sz_name[] = TEXT("cssow2basicsync");

void memoryMapping() {
	HANDLE mapHandle;
	LPCTSTR buf;

	mapHandle = CreateFileMapping(
		INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		0,
		BUFFER_SIZE,
		sz_name
	);

	if (mapHandle == NULL) {
		cout << "CreateFileMapping error: " << GetLastError() << endl;
	}

	buf = (LPTSTR)MapViewOfFile(mapHandle,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		BUFFER_SIZE);

	if (buf == NULL) {
		cout << "MapViewOfFile error: " << GetLastError() << endl;
	}


	/*UnmapViewOfFile(mapHandle);
	CloseHandle(mapHandle);*/
}

void readFromMemoryMap() {
	TCHAR sz_name[] = TEXT("cssow2basicsync");

	HANDLE mapHandle;
	LPCTSTR buf;

	mapHandle = OpenFileMapping(
		FILE_MAP_ALL_ACCESS,
		FALSE,
		sz_name);

	if (mapHandle == NULL) {
		cout << "OpenFileMapping error: " << GetLastError();
	}

	buf = (LPTSTR)MapViewOfFile(
		mapHandle,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		BUFFER_SIZE);

	if (buf == NULL) {
		cout << "MapViewOfFile error: " << GetLastError();
	}

	cout << "Read from memory mapping: " << '\n' << (char*)buf << '\n';

	UnmapViewOfFile(buf);
	CloseHandle(mapHandle);
}

void startP(string path) {
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	LPTSTR long_string = new TCHAR[path.size() + 1];
	strcpy(long_string, path.c_str());
	if (!CreateProcess(long_string,
		NULL,
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si,
		&pi)) {
		cout << "CreateProcess failed! Error: " << GetLastError() << endl;
	}
	WaitForSingleObject(pi.hProcess, INFINITE);
	if (path == "D:\\Desktop\\fii\\anul III\\Semestrul I\\CSSO\\Teme\\tema2\\P1\\x64\\Debug\\P1.exe")
		readFromMemoryMap();
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

int _tmain()
{
	memoryMapping();
	startP("D:\\Desktop\\fii\\anul III\\Semestrul I\\CSSO\\Teme\\tema2\\P1\\x64\\Debug\\P1.exe");
	startP("D:\\Desktop\\fii\\anul III\\Semestrul I\\CSSO\\Teme\\tema2\\P1\\x64\\Debug\\P2.exe");
	return 0;
}