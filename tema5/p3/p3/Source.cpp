#pragma comment(lib, "advapi32.lib")
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <aclapi.h>
#include <tchar.h>
#include <sddl.h>
#include <iostream>
#include <lmcons.h>
using namespace std;

int main() {
	cout << "////start P3////" << endl;

	SID* everyone = (SID*)new BYTE[SECURITY_MAX_SID_SIZE];
	DWORD everyone_size = SECURITY_MAX_SID_SIZE;
	if (!CreateWellKnownSid(WELL_KNOWN_SID_TYPE::WinWorldSid, NULL, everyone, &everyone_size)) {
		cout << "err la CreateWellKnownSid :" << GetLastError() << endl;
		return -1;
	}

	LPSTR everyoneSID = (LPSTR)new BYTE[SECURITY_MAX_SID_SIZE];
	ConvertSidToStringSidA(everyone, &everyoneSID);

	SID* admins = (SID*)new BYTE[SECURITY_MAX_SID_SIZE];
	DWORD admins_size = SECURITY_MAX_SID_SIZE;
	if (!CreateWellKnownSid(WELL_KNOWN_SID_TYPE::WinLocalAccountAndAdministratorSid, NULL, admins, &admins_size)) {
		cout << "err la CreateWellKnownSid :" << GetLastError() << endl;
		return -1;
	}

	LPSTR adminsSid = (LPSTR)new BYTE[SECURITY_MAX_SID_SIZE];
	ConvertSidToStringSidA(admins, &adminsSid);


	cout << "everyone sid P3:" << endl;
	cout << strlen(everyoneSID) << endl;
	cout << everyoneSID << endl;
	cout << "admin sid P3:" << endl;
	cout << strlen(adminsSid) << endl;
	cout << adminsSid << endl;

	HANDLE hPtrei = CreateFile("C:\\Facultate\\CSSO\\Laboratoare\\Week5\\RESTRICTED_WRITE\\P3.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hPtrei == INVALID_HANDLE_VALUE) {
		if (GetLastError() != 183) {
			cout << "err la CreateFile :" << GetLastError() << endl;
			return -1;
		}
	}

	if (!WriteFile(hPtrei, adminsSid, strlen(adminsSid), NULL, NULL)) {
		cout << "err la WriteFile :" << GetLastError() << endl;
		return -1;
	}

	LPCSTR n = "     \n";
	if (!WriteFile(hPtrei, n, strlen(n), NULL, NULL)) {
		cout << "err la WriteFile :" << GetLastError() << endl;
		return -1;
	}

	if (!WriteFile(hPtrei, everyoneSID, strlen(everyoneSID), NULL, NULL)) {
		cout << "err la WriteFile :" << GetLastError() << endl;
		return -1;
	}

	HANDLE hLogs = CreateFile("C:\\Facultate\\CSSO\\Laboratoare\\Week5\\LOGS\\P3.log", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hLogs == INVALID_HANDLE_VALUE) {
		if (GetLastError() != 183) {
			cout << "err la CreateFile :" << GetLastError() << endl;
			return -1;
		}
	}

	LPCSTR buff = "A reusit crearea fisierului! \n";

	if (!WriteFile(hLogs, buff, strlen(buff), NULL, NULL)) {
		cout << "err la WriteFile :" << GetLastError() << endl;
		return -1;
	}

	LPSTR lastSevenAdmins = (LPSTR)new BYTE[10];
	cout << endl << strlen(adminsSid);

	int count = 0;
	for (int i = 0; i < strlen(adminsSid); i++)
		if (adminsSid[i] >= '0' && adminsSid[i] <= '9' && count <= 6)
			lastSevenAdmins[count++] = adminsSid[i];
	lastSevenAdmins[count] = '\0';

	cout << endl << lastSevenAdmins << endl;

	DWORD lastSevenAdminsDword = 0;

	count = 0;
	for (int i = 0; i < strlen(lastSevenAdmins); i++) {
		lastSevenAdminsDword = lastSevenAdminsDword * 10 + lastSevenAdmins[i] - '\0';
	}

	cout << endl << lastSevenAdminsDword << endl;

	DWORD finallAdmins = lastSevenAdminsDword;
	HKEY hKey;

	if (RegCreateKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\CSSO\\Tema5\\P3", 0, 0, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL)) {
		
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

	const BYTE* pfinallAdmins = (BYTE*)&finallAdmins;

	if (RegSetValueEx(hKey, "ultimele 6 cifre admins:", 0, REG_DWORD, pfinallAdmins, sizeof(lastSevenAdminsDword)) != ERROR_SUCCESS && GetLastError() != 183) {
		cout << "err la RegSetValueEx :" << GetLastError() << endl;

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

	LPSTR lastSevenEveryone = (LPSTR)new BYTE[10];
	cout << endl << strlen(everyoneSID);

	int counter = 0;
	for (int i = 0; i < strlen(everyoneSID); i++)
		if (everyoneSID[i] >= '0' && everyoneSID[i] <= '9' && counter <= 6)
			lastSevenEveryone[counter++] = everyoneSID[i];
	lastSevenEveryone[counter] = '\0';

	cout << endl << lastSevenEveryone << endl;

	DWORD lastSevenEveryoneDword = 0;

	count = 0;
	for (int i = 0; i < strlen(lastSevenEveryone); i++) {
		lastSevenEveryoneDword = lastSevenEveryoneDword * 10 + lastSevenEveryone[i] - '\0';
	}

	cout << endl << lastSevenEveryoneDword << endl;

	DWORD finallEveryone = lastSevenEveryoneDword;

	const BYTE* pfinallEveryone = (BYTE*)&finallEveryone;

	if (RegSetValueEx(hKey, "ultimele 6 cifre everyone :", 0, REG_DWORD, pfinallEveryone, sizeof(lastSevenEveryoneDword)) != ERROR_SUCCESS && GetLastError() != 183) {
		cout << "err la RegSetValueEx :" << GetLastError() << endl;

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

	RegCloseKey(hKey);
	delete[SECURITY_MAX_SID_SIZE] admins;
	delete[SECURITY_MAX_SID_SIZE] everyone;

	cout << "////finished P3////" << endl;

	return 0;
}