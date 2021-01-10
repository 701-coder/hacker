#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <process.h>

#define MAX_DOCUMENT 100
#define TOTAL_STAFF 2

volatile LONG Document_Number = 0;
INT Document_Counter[MAX_DOCUMENT];
HANDLE P1_Done, P2_Ready, P2_GetDoc;

UINT __stdcall P1(PVOID lp) {
	while (Document_Number < MAX_DOCUMENT) {
		printf("Process document %2d by staff 1\n", Document_Number);
		Sleep(rand() % 2); //process document
		printf("Finish1 document %2d by staff 1\n", Document_Number);
		Document_Counter[Document_Number]++;
		SetEvent(P1_Done);
		WaitForSingleObject(P2_Ready, INFINITE);
		WaitForSingleObject(P2_GetDoc, INFINITE);
		Document_Number++;
	}
	return 0;
}

UINT __stdcall P2(PVOID lp) {
	SetEvent(P2_Ready);
	while (Document_Number < MAX_DOCUMENT) {
		WaitForSingleObject(P1_Done, INFINITE);
		INT i = Document_Number;
		printf("Process document %2d by staff 2\n", i);
		SetEvent(P2_GetDoc);
		Sleep(rand() % 2); //process document
		printf("Finish2 document %2d by staff 2\n", i);
		Document_Counter[i]++;
		SetEvent(P2_Ready);
	}
	return 0;
}

INT main(INT argc, PCHAR argv[]) {
	HANDLE Staff_Handles[TOTAL_STAFF];
	ZeroMemory(Document_Counter, sizeof(Document_Counter));
	P1_Done = CreateEvent(NULL, FALSE, FALSE, NULL);
	P2_Ready = CreateEvent(NULL, FALSE, FALSE, NULL);
	P2_GetDoc = CreateEvent(NULL, FALSE, FALSE, NULL);
	Staff_Handles[0] = (HANDLE)_beginthreadex(NULL, 0, P1, NULL, 0, NULL);
	Staff_Handles[1] = (HANDLE)_beginthreadex(NULL, 0, P2, NULL, 0, NULL);
	WaitForMultipleObjects(TOTAL_STAFF, Staff_Handles, TRUE, INFINITE);
	CloseHandle(P1_Done);
	CloseHandle(P2_Ready);
	CloseHandle(P2_GetDoc);
	for (int i = 0; i < MAX_DOCUMENT; ++i)printf("Document %2d processed by %d staffs\n", i, Document_Counter[i]);
	system("pause");
	return 0;
}
