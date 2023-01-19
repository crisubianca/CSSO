#pragma comment(lib, "advapi32.lib")
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <aclapi.h>
#include <tchar.h>
#include <iostream>
#include <sddl.h>
#include <lmcons.h>
using namespace std;

int main() {
	cout << "////start P2////" << endl;
	DWORD usernameLength = UNLEN;
	LPSTR username = (LPSTR)malloc(usernameLength);
	GetUserName(username, &usernameLength);

	SID* owner = (SID*)new BYTE[SECURITY_MAX_SID_SIZE];
	DWORD owner_size = SECURITY_MAX_SID_SIZE, size = 1024;

	LPSTR DomainName = new TCHAR[1024];
	SID_NAME_USE peUse;
	if (!LookupAccountName(NULL, username, owner, &owner_size, DomainName, &size, &peUse)) {
		cout << "err la LookupAccountName :" << GetLastError() << endl;
		return -1;
	}

	LPSTR ownerSid = (LPSTR)new BYTE[SECURITY_MAX_SID_SIZE];
	ConvertSidToStringSidA(owner, &ownerSid);
	cout << ownerSid;

	HANDLE hFile = CreateFile("C:\\Facultate\\CSSO\\Laboratoare\\Week5\\RESTRICTED_WRITE\\P2.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		if (GetLastError() != 183) {
			cout << "err la CreateFile :" << GetLastError() << endl;
			return -1;
		}
	}

	if (!WriteFile(hFile, ownerSid, strlen(ownerSid), NULL, NULL)) {
		cout << "err la WriteFile :" << GetLastError() << endl;
		return -1;
	}

	HANDLE hLogs = CreateFile("C:\\Facultate\\CSSO\\Laboratoare\\Week5\\LOGS\\P2.log", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hLogs == INVALID_HANDLE_VALUE) {
		if (GetLastError() != 183) {
			cout << "err la CreateFile :" << GetLastError() << endl;
			return -1;
		}
	}

	LPCSTR buff = "A reusit crearea fisierului! \n";
	if (!WriteFile(hLogs, buff, strlen(buff), NULL, NULL)) {
		cout << "err la WriteFile" << GetLastError() << endl;
		return -1;
	}

	LPSTR lastSeven = (LPSTR)new BYTE[10];
	cout << endl << strlen(ownerSid);
	int count = 0;
	for (int i = strlen(ownerSid) - 7; i < strlen(ownerSid) + 1; i++)
		lastSeven[count++] = ownerSid[i];
	for (int i = 2; i < strlen(lastSeven) - 1; i++)
		lastSeven[i] = lastSeven[i + 1];
	lastSeven[strlen(lastSeven) - 1] = '\0';
	cout << endl << lastSeven << endl;

	DWORD lastSevenDword = 0;
	count = 0;
	for (int i = 0; i < strlen(lastSeven); i++)
		lastSevenDword = lastSevenDword * 10 + lastSeven[i] - '0';

	cout << endl << lastSevenDword << endl;

	DWORD finall = lastSevenDword;
	HKEY hKey;
	if (RegCreateKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\CSSO\\Tema5\\P2", 0, 0, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL)) {
		cout << "err la RegCreateKeyEx :" << GetLastError() << endl;

		LPCSTR buff = "Nu a reusit crearea de subkey! \n";

		if (!WriteFile(hLogs, buff, strlen(buff), NULL, NULL)) {
			cout << "err la WriteFile :" << GetLastError() << endl;
			return -1;
		}

		return -1;
	}
	else {

		LPCSTR buff = "A reusit crearea de subkey! \n";

		if (!WriteFile(hLogs, buff, strlen(buff), NULL, NULL)) {
			cout << "err la WriteFile :" << GetLastError() << endl;
			return -1;
		}
	}

	const BYTE* pfinall = (BYTE*)&finall;

	if (RegSetValueEx(hKey, "ultimele 6 cifre :", 0, REG_DWORD, pfinall, sizeof(lastSevenDword)) != ERROR_SUCCESS && GetLastError() != 183) {
		cout << "err la RegSetValueEx :" << GetLastError() << endl;

		LPCSTR buff = "Nu a reusit crearea valorii! \n";

		if (!WriteFile(hLogs, buff, strlen(buff), NULL, NULL)) {
			cout << "err la WriteFile :" << GetLastError() << endl;
			return -1;
		}

		return -1;
	}
	else {

		LPCSTR buff = "A reusit crearea de valorii! \n";

		if (!WriteFile(hLogs, buff, strlen(buff), NULL, NULL)) {
			cout << "err la WriteFile :" << GetLastError() << endl;
			return -1;
		}
	}

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	if (!CreateProcess("D:\\Desktop\\fii\\anul III\\Semestrul I\\CSSO\\Teme\\tema5\\p3\\x64\\Debug\\p3.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
		/*cout << "am ajuns aici\n";*/

		LPCSTR buff = "Nu a reusit pornirea lui P3! \n";

		if (!WriteFile(hLogs, buff, strlen(buff), NULL, NULL)) {
			cout << "err la WriteFile :" << GetLastError() << endl;
			return -1;
		}

		return -1;
	}
	else {
		LPCSTR buff = "A reusit pornirea lui P3! \n";

		if (!WriteFile(hLogs, buff, strlen(buff), NULL, NULL)) {
			cout << "err la WriteFile :" << GetLastError() << endl;
			return -1;
		}
	}

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	RegCloseKey(hKey);
	delete[SECURITY_MAX_SID_SIZE] owner;
	delete[1024] DomainName;

	cout << "////finish P2///" << endl;

	return 0;
}