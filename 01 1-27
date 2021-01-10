#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <process.h>

#define MAX_DOCUMENT 100
#define TOTAL_STAFF 10

volatile LONGLONG Document_Number = 0;
INT Document_Counter[MAX_DOCUMENT];

UINT __stdcall Staff(PVOID lp) {
	INT Staff_Number = *(INT*)lp;
	while (Document_Number < MAX_DOCUMENT) {
		INT i = InterlockedIncrement64(&Document_Number) - 1;
		printf("Process document %2d by staff %d\n", i, Staff_Number);
		Document_Counter[i]++;
	}
	return 0;
}

int main(int argc, TCHAR *argv[]) {
	HANDLE Staff_Handles[TOTAL_STAFF];
	INT Staff_Numbers[TOTAL_STAFF];
	ZeroMemory(Document_Counter, sizeof(Document_Counter));
	for (int i = 0; i < TOTAL_STAFF; ++i) {
		Staff_Numbers[i] = i;
		Staff_Handles[i] = (HANDLE)_beginthreadex(NULL, 0, Staff, &Staff_Numbers[i], CREATE_SUSPENDED, NULL);
	}
	printf("Staffs are ready\n");
	for (int i = 0; i < TOTAL_STAFF; ++i)ResumeThread(Staff_Handles[i]);
	WaitForMultipleObjects(TOTAL_STAFF, Staff_Handles, TRUE, INFINITE);
	for (int i = 0; i < TOTAL_STAFF; ++i)CloseHandle(Staff_Handles[i]);
	for (int i = 0; i < MAX_DOCUMENT; ++i)printf("Document %2d processed by %d staffs\n", i, Document_Counter[i]);
	system("pause");
	return 0;
}
