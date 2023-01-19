#pragma comment(lib, "advapi32.lib")
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <aclapi.h>
#include <tchar.h>
#include <iostream>
#include <lmcons.h>
using namespace std;

int main() {
	cout << "////start P1////" << endl;
	SECURITY_DESCRIPTOR sd;
	if (!InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION)) {
		cout << "err la InitializeSecurityDescriptor :" << GetLastError() << endl;
		return -1;
	}

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

	SID* everyone = (SID*)new BYTE[SECURITY_MAX_SID_SIZE];
	DWORD everyone_size = SECURITY_MAX_SID_SIZE;
	if(!CreateWellKnownSid(WELL_KNOWN_SID_TYPE::WinWorldSid, NULL, everyone, &everyone_size)) {
		cout << "err la CreateWellKnownSid :" << GetLastError() << endl;
		return -1;
	}

	if (!SetSecurityDescriptorOwner(&sd, owner, FALSE)) {
		cout << "err la SetSecurityDescriptorOwner" << GetLastError() << endl;
		return -1;
	}

	EXPLICIT_ACCESS ea[2];
	PACL pACL = NULL;
	ZeroMemory(&ea, 2 * sizeof(EXPLICIT_ACCESS));
	ea[0].grfAccessPermissions = FILE_GENERIC_READ | FILE_GENERIC_WRITE;
	ea[0].grfAccessMode = SET_ACCESS;
	ea[0].grfInheritance = SUB_CONTAINERS_AND_OBJECTS_INHERIT;
	ea[0].Trustee.TrusteeForm = TRUSTEE_IS_SID;
	ea[0].Trustee.TrusteeType = TRUSTEE_IS_GROUP;
	ea[0].Trustee.ptstrName = (LPTSTR)owner;

	ea[1].grfAccessPermissions = FILE_GENERIC_READ;
	ea[1].grfAccessMode = SET_ACCESS;
	ea[1].grfInheritance = SUB_CONTAINERS_AND_OBJECTS_INHERIT;
	ea[1].Trustee.TrusteeForm = TRUSTEE_IS_SID;
	ea[1].Trustee.TrusteeType = TRUSTEE_IS_GROUP;
	ea[1].Trustee.ptstrName = (LPTSTR)everyone;

	if (SetEntriesInAcl(2, ea, NULL, &pACL) != ERROR_SUCCESS) {
		cout << "err la SetEntriesInAcl :" << GetLastError() << endl;
		return -1;
	}

	if (!SetSecurityDescriptorDacl(&sd, TRUE, pACL, FALSE)) {
		cout << "SetSecurityDescriptorDacl :" << GetLastError() << endl;
		return -1;
	}

	_SECURITY_ATTRIBUTES security_attributes;
	security_attributes.nLength = sizeof(SECURITY_ATTRIBUTES);
	security_attributes.lpSecurityDescriptor = &sd;
	security_attributes.bInheritHandle = TRUE;

	if (CreateDirectoryA("C:\\Facultate\\CSSO\\Laboratoare\\Week5", &security_attributes) == 0 && GetLastError() != 183) {
		cout << "err la CreateFirectoryA :" << GetLastError() << endl;
		return 1;
	}

	if (CreateDirectoryA("C:\\Facultate\\CSSO\\Laboratoare\\Week5\\RESTRICTED_WRITE", &security_attributes) == 0 && GetLastError() != 183) {
		cout << "err la CreateFirectoryA :" << GetLastError() << endl;
		return 1;
	}

	if (CreateDirectoryA("C:\\Facultate\\CSSO\\Laboratoare\\Week5\\LOGS", &security_attributes) == 0 && GetLastError() != 183) {
		cout << "err la CreateFirectoryA :" << GetLastError() << endl;
		return 1;
	}

	HKEY hKey;
	if (RegCreateKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\CSSO\\Tema5", 0, 0, REG_OPTION_NON_VOLATILE, KEY_WRITE, &security_attributes, &hKey, NULL)) {
		cout << "err la RegCreateKeyEx :" << GetLastError() << endl;
		return -1;
	}

	delete[SECURITY_MAX_SID_SIZE] owner;
	delete[1024] DomainName;

	cout << "////finish P1////" << endl;
	return 0;
}

