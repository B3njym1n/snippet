#include <Windows.h>
#include <commctrl.h>

const char g_szClassName[] = "Progress Bar Demo";

DWORD WINAPI PBThreadProc(LPVOID lpParameter) {
    HWND hwndPB = (HWND) lpParameter;
    PBRANGE range;

    SendMessage(hwndPB, PBM_SETRANGE,
        (WPARAM) 0, (LPARAM) (MAKELPARAM(0, 100)));
    
    SendMessage(hwndPB, PBM_GETRANGE,
        (WPARAM) TRUE,
        (LPARAM) &range);
    
    while (TRUE)
    {
        SendMessage(hwndPB, PBM_DELTAPOS, (WPARAM) (range.iHigh - range.iLow) / 20, (LPARAM) 0);
        if (SendMessage(hwndPB, PBM_GETPOS, (WPARAM) 0, (LPARAM) 0) == range.iHigh)
        {
            SendMessage(hwndPB, PBM_SETPOS, (WPARAM) range.iLow, (LPARAM) 0);
        }
        Sleep(1000);
    }
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lcCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hWnd;
	MSG msg;
	
	// Step 1: Registering the Window class
	wc.cbSize 				= sizeof(WNDCLASSEX);
	wc.style 				= 0;
	wc.lpfnWndProc 			= WndProc;
	wc.cbClsExtra 			= 0;
	wc.cbWndExtra 			= 0;
	wc.hInstance 			= hInstance;
	wc.hIcon 				= LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor 				= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground 		= (HBRUSH) GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName 		= NULL;
	wc.lpszClassName 		= g_szClassName;
	wc.hIconSm 				= LoadIcon(NULL, IDI_APPLICATION);
	
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	
	hWnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"The title of my window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 480, 360,
		NULL, NULL, hInstance, NULL);
	if (hWnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	// message loop
	while(GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HWND hwndPB;
	switch(msg)
	{
        case WM_CREATE:
        {
            InitCommonControls();
            hwndPB = CreateWindowEx(
                0,
                PROGRESS_CLASS,
                NULL,
                WS_CHILD | WS_VISIBLE,
                0,0,0,0,
                hWnd,
                (HMENU) 0,
                ((LPCREATESTRUCT)lParam)->hInstance,
                NULL
            );
            CreateThread(
                NULL,
                0,
                (LPTHREAD_START_ROUTINE) PBThreadProc,
                hwndPB,
                0,
                0
            );
        }
            break;
        case WM_SIZE:
        {
            RECT rc;
            GetClientRect(hWnd, &rc);
            MoveWindow(
                hwndPB,
                rc.left,
                (rc.bottom - rc.top) / 4,
                rc.right - rc.left,
                (rc.bottom - rc.top) / 10,
                TRUE
            );
        }
        break;
		case WM_CLOSE:
			DestroyWindow(hWnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}