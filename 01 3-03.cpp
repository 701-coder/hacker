#include <windows.h> //1-4 don't change
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
static TCHAR szWindowClass[] = _T("DesktopApp");
static TCHAR szTitle[] = _T("Windows Desktop Guided Tour Applicaiton"); //視窗標題
HINSTANCE hInst; //don't change
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); //don't change
int CALLBACK WinMain( //程式的切入點 9-14 don't change
	_In_ HINSTANCE hInstance, //一個Handle
	_In_ HINSTANCE hPrevInstance, //32位元以上的電腦通常傳入NULL
	_In_ LPSTR lpCmdLine, //命令列參數
	_In_ int nCmdShow //設定Windows的顯示狀態
)
{
	WNDCLASSEX wcex; //16-28 主視窗的性質 usually don't change
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	if (!RegisterClassEx(&wcex)) //29-36 視窗設計不成功會跳出MessageBox don't change
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);
		return 1;
	}
	hInst = hInstance;
	HWND hWnd = CreateWindow( //38-48 call CreateWindow i.e.創立一個視窗 don't change
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 100,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (!hWnd) //49-57 視窗設計不成功會跳出MessageBox don't change
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);

		return 1;
	}
	ShowWindow(hWnd, nCmdShow); //設定視窗顯示狀態 don't change
	UpdateWindow(hWnd); //更新視窗 don't change
	MSG msg; //60-66 don't change
	while (GetMessage(&msg, NULL, 0, 0)) //將消息存入msg
	{
		TranslateMessage(&msg); //將虛擬鍵值訊息轉換為字元訊息
		DispatchMessage(&msg); //將消息傳給視窗
	}
	return (int)msg.wParam;
} //前面的1-67行不重要，68行以後才是重點
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}
