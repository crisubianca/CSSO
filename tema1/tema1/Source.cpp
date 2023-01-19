#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

int main()
{
    //L1
    bool result1 = CreateDirectoryA("C:\\Facultate", NULL);
    bool result2 = CreateDirectoryA("C:\\Facultate\\CSSO", NULL);
    bool result3 = CreateDirectoryA("C:\\Facultate\\CSSO\\Laboratoare", NULL);
    bool result4 = CreateDirectoryA("C:\\Facultate\\CSSO\\Laboratoare\\Week1", NULL);
    bool result5 = CreateDirectoryA("C:\\Facultate\\CSSO\\Laboratoare\\Week1\\Extensii", NULL);
    bool result6 = CreateDirectoryA("C:\\Facultate\\CSSO\\Laboratoare\\Week1\\Rezultate", NULL);
    if ( !result1 || !result2 || !result3 || !result4 || !result5 || !result6 )
    {
        DWORD errCode = GetLastError();
        if (errCode != ERROR_ALREADY_EXISTS)
        {
            printf("Eroare la CreateDirectoryA: % d\n", GetLastError());
            return 1;
        }
    }
    printf("Primul ex. s-a rezolvat cu succes! - L1\n");

    //L1/L2
    DWORD lpcSubKeys1 = 0, lpcMaxSubKeyLen1 = 0;
    FILETIME lpftLastWriteTime1;
    //HKLM.txt
    HANDLE h1;
    h1 = CreateFile(L"C:\\Facultate\\CSSO\\Laboratoare\\Week1\\Rezultate\\HKLM.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (h1 == INVALID_HANDLE_VALUE)
    {
        printf("Eroare la CreateFile: %d\n", GetLastError());
        return 1;
    }
    /*printf("am ajuns aici");*/
    if (RegQueryInfoKey(HKEY_LOCAL_MACHINE, NULL, NULL, NULL, &lpcSubKeys1, &lpcMaxSubKeyLen1, NULL, NULL, NULL, NULL, NULL, &lpftLastWriteTime1) != ERROR_SUCCESS)
    {
        RegCloseKey(HKEY_LOCAL_MACHINE);
        return 1;
    }
    /*printf("am ajuns aici");*/
    char subKeys1[100];
    char result[250] = "";
    sprintf_s(subKeys1, "%d", lpcSubKeys1);
    char maxSubKeyLen1[30];
    sprintf_s(maxSubKeyLen1, "%d", lpcMaxSubKeyLen1);
    SYSTEMTIME time1;
    char lastWriteTime1[100];
    /*printf("am ajuns aici");*/
    if (FileTimeToSystemTime(&lpftLastWriteTime1, &time1) == 0)
    {
        printf("Eroate la FileTimeToSystemTime\n");
        return 1;
    }
    else { sprintf_s(lastWriteTime1, "%02d/%02d/%02d %02d:%02d:%02d\n", time1.wYear, time1.wMonth, time1.wDay, time1.wHour, time1.wMinute, time1.wSecond); }
    strcat_s(result, sizeof(result), subKeys1);
    strcat_s(result, sizeof(result), "\n");
    strcat_s(result, sizeof(result), maxSubKeyLen1);
    strcat_s(result, sizeof(result), "\n");
    strcat_s(result, sizeof(result), lastWriteTime1);
    /*printf("am ajuns aici");*/
    if (WriteFile(h1, result, strlen(result), NULL, NULL) == 0)
    {
        printf("Eroare la WriteFile: %d\n", GetLastError());
        return 1;
    }

    CloseHandle(h1);

    //HKCC.txt
    DWORD lpcSubKeys2 = 0, lpcMaxSubKeyLen2 = 0;
    FILETIME lpftLastWriteTime2;
    HANDLE h2;
    h2 = CreateFile(L"C:\\Facultate\\CSSO\\Laboratoare\\Week1\\Rezultate\\HKCC.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (h2 == INVALID_HANDLE_VALUE)
    {
        printf("Eroare la CreateFile: %d\n", GetLastError());
        return 1;
    }
    /*printf("am ajuns aici");*/
    if (RegQueryInfoKey(HKEY_CURRENT_CONFIG, NULL, NULL, NULL, &lpcSubKeys2, &lpcMaxSubKeyLen2, NULL, NULL, NULL, NULL, NULL, &lpftLastWriteTime2) != ERROR_SUCCESS)
    {
        RegCloseKey(HKEY_CURRENT_CONFIG);
        return 1;
    }
    /*printf("am ajuns aici");*/
    char subKeys2[100];
    char res[250] = "";
    sprintf_s(subKeys2, "%d", lpcSubKeys2);
    char maxSubKeyLen2[30];
    sprintf_s(maxSubKeyLen2, "%d", lpcMaxSubKeyLen2);
    SYSTEMTIME time2;
    char lastWriteTime2[100];
    /*printf("am ajuns aici");*/
    if (FileTimeToSystemTime(&lpftLastWriteTime2, &time2) == 0)
    {
        printf("Eroate la FileTimeToSystemTime\n");
        return 1;
    }
    else { sprintf_s(lastWriteTime2, "%02d/%02d/%02d %02d:%02d:%02d\n", time2.wYear, time2.wMonth, time2.wDay, time2.wHour, time2.wMinute, time2.wSecond); }
    strcat_s(res, sizeof(res), subKeys2);
    strcat_s(res, sizeof(res), "\n");
    strcat_s(res, sizeof(res), maxSubKeyLen2);
    strcat_s(res, sizeof(res), "\n");
    strcat_s(res, sizeof(res), lastWriteTime2);
    /*printf("am ajuns aici");*/
    if (WriteFile(h2, res, strlen(res), NULL, NULL) == 0)
    {
        printf("Eroare la WriteFile: %d\n", GetLastError());
        return 1;
    }

    CloseHandle(h2);


    //HKCU.txt
    DWORD lpcSubKeys3 = 0, lpcMaxSubKeyLen3 = 0;
    FILETIME lpftLastWriteTime3;
    HANDLE h3;
    h3 = CreateFile(L"C:\\Facultate\\CSSO\\Laboratoare\\Week1\\Rezultate\\HKCU.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (h3 == INVALID_HANDLE_VALUE)
    {
        printf("Eroare la CreateFile: %d\n", GetLastError());
        return 1;
    }
    /*printf("am ajuns aici");*/
    if (RegQueryInfoKey(HKEY_CURRENT_USER, NULL, NULL, NULL, &lpcSubKeys3, &lpcMaxSubKeyLen3, NULL, NULL, NULL, NULL, NULL, &lpftLastWriteTime3) != ERROR_SUCCESS)
    {
        RegCloseKey(HKEY_CURRENT_USER);
        return 1;
    }
    /*printf("am ajuns aici");*/
    char subKeys3[100];
    char rezultat[250] = "";
    sprintf_s(subKeys3, "%d", lpcSubKeys3);
    char maxSubKeyLen3[30];
    sprintf_s(maxSubKeyLen3, "%d", lpcMaxSubKeyLen3);
    SYSTEMTIME time3;
    char lastWriteTime3[100];
    /*printf("am ajuns aici");*/
    if (FileTimeToSystemTime(&lpftLastWriteTime3, &time3) == 0)
    {
        printf("Eroate la FileTimeToSystemTime\n");
        return 1;
    }
    else { sprintf_s(lastWriteTime3, "%02d/%02d/%02d %02d:%02d:%02d\n", time3.wYear, time3.wMonth, time3.wDay, time3.wHour, time3.wMinute, time3.wSecond); }
    strcat_s(rezultat, sizeof(rezultat), subKeys3);
    strcat_s(rezultat, sizeof(rezultat), "\n");
    strcat_s(rezultat, sizeof(rezultat), maxSubKeyLen3);
    strcat_s(rezultat, sizeof(rezultat), "\n");
    strcat_s(rezultat, sizeof(rezultat), lastWriteTime3);
    /*printf("am ajuns aici");*/
    if (WriteFile(h3, res, strlen(res), NULL, NULL) == 0)
    {
        printf("Eroare la WriteFile: %d\n", GetLastError());
        return 1;
    }

    CloseHandle(h3);
    printf("Al doilea ex. s-a rezolvat cu succes! - L1/L2\n");


	printf("Am ajuns la finalul programului!\n");
}