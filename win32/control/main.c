#include <Windows.h>
#include <Windowsx.h>
#include <strsafe.h>
#include <conio.h>

#define IDM_BTN1 10001
#define IDM_BTN2 10002
#define ID_EDITCHILD 20001

static int width = 360;
static int height = 240;

const char g_szClassName[] = "myWindowClass";

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lcCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND m_hwnd;
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
	wc.hbrBackground 		= (HBRUSH) (COLOR_WINDOW+1);
	wc.lpszMenuName 		= NULL;
	wc.lpszClassName 		= g_szClassName;
	wc.hIconSm 				= LoadIcon(NULL, IDI_APPLICATION);
	
    if (!AllocConsole())
    {
        LPVOID lpMsgBuf;
        LPVOID lpDisplayBuf;
        DWORD dw = GetLastError(); 
        FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );
        // Display the error message and exit the process

        lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
            (lstrlen((LPCTSTR)lpMsgBuf) + 40) * sizeof(TCHAR)); 
        StringCchPrintf((LPTSTR)lpDisplayBuf, 
            LocalSize(lpDisplayBuf) / sizeof(TCHAR),
            TEXT("AllocConsole() failed with error %d: %s"), dw, lpMsgBuf); 
        MessageBox(NULL, lpDisplayBuf, "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
    } 
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	
	m_hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"The title of my window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, width, height,
		NULL, NULL, hInstance, NULL);
	if (m_hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

    HWND hwndButton = CreateWindow( 
    "BUTTON",  // Predefined class; Unicode assumed 
    "OK",      // Button text 
    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
    10,         // x position 
    10,         // y position 
    50,        // Button width
    20,        // Button height
    m_hwnd,     // Parent window
    (HMENU) IDM_BTN1,       // No menu.
    (HINSTANCE)GetWindowLongPtr(m_hwnd, GWLP_HINSTANCE), 
    NULL);      // Pointer not needed.

    HWND hwndButton2 = CreateWindow( 
    "BUTTON",  // Predefined class; Unicode assumed 
    "OK",      // Button text 
    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
    80,         // x position 
    10,         // y position 
    50,        // Button width
    20,        // Button height
    m_hwnd,     // Parent window
    (HMENU) IDM_BTN2,       // No menu.
    (HINSTANCE)GetWindowLongPtr(m_hwnd, GWLP_HINSTANCE), 
    NULL);      // Pointer not needed.
	
	ShowWindow(m_hwnd, nCmdShow);
	UpdateWindow(m_hwnd);
	
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
    static HWND hwndEdit;
    char lpczS[] = "ljaglasngoasputasoisdongas";
    
	switch(msg)
	{
        case WM_CREATE:
        hwndEdit = CreateWindowEx(
            0,
            "EDIT",
            NULL,
            WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
            10, 30, 310, 150,
            hWnd,
            (HMENU) ID_EDITCHILD,
            (HINSTANCE) GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL
        );
        
        SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM) lpczS);
        break;
        case WM_SIZE:
        width = LOWORD(lParam);
        height = HIWORD(lParam);
        break;
        case WM_COMMAND:
            switch(LOWORD(wParam)) {
                case IDM_BTN1:
                char buf[1024];
                Edit_GetText(hwndEdit, buf, 1024);
                MessageBox(NULL, buf , "BTN1 message", MB_ICONEXCLAMATION | MB_OK);
                break;
                case IDM_BTN2:
                MessageBox(NULL, "Button Clicked" , "BTN2 message", MB_ICONEXCLAMATION | MB_OK);
                break;
            }
        break;
        /* case WM_PAINT:
        break; */
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