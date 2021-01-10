#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <process.h>
#include <tchar.h>

int Number1 = 0;
int Number2 = 0;
UINT __stdcall StaffA(LPVOID);
UINT __stdcall StaffB(LPVOID);

int _tmain(int argc, char* argv[]) {
	UINT Id;
	HANDLE hd[2];
	srand(GetTickCount());
	hd[0] = (HANDLE)_beginthreadex(NULL, 0, StaffA, NULL, 0, &Id);
	hd[0] = (HANDLE)_beginthreadex(NULL, 0, StaffB, NULL, 0, &Id);
	WaitForMultipleObjects(2, hd, TRUE, INFINITE);
	CloseHandle(hd[0]);
	CloseHandle(hd[1]);
	system("pause");
	return 0;
}

UINT __stdcall StaffA(LPVOID) {
	while (Number1 < 100) {
		printf("Begin of A\n");
		Number1++;
		Number2++;
		printf("A add number.\n");
		printf("1A = %d\n", Number1);
		Sleep(rand() % 2);
		printf("2A = %d\n", Number2);
		printf("End of A\n");
		Sleep(rand() % 2);
	}
	return 0;
}

UINT __stdcall StaffB(LPVOID) {
	while (Number1 < 100) {
		printf("Begin of B\n");
		Number1++;
		Number2++;
		printf("B add number.\n");
		printf("1B = %d\n", Number1);
		Sleep(rand() % 2);
		printf("2B = %d\n", Number2);
		printf("End of B\n");
		Sleep(rand() % 2);
	}
	return 0;
}
