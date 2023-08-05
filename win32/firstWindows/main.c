#include <Windows.h>

#define IDM_OPT1 301
#define IDM_OPT2 302

HMENU hRoot;
const char g_szClassName[] = "myWindowClass";

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// it's not wise to create dialog dynamically while it's technically possible
// dynamically add menu
void CreateMyMenu();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lcCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hWnd;
	MSG msg;
	CreateMyMenu();
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
		CW_USEDEFAULT, CW_USEDEFAULT, 240, 120,
		NULL, 
		hRoot, 
		hInstance, NULL);
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
	switch(msg)
	{
		case WM_COMMAND:
		{
			
			if (LOWORD(wParam) == IDM_OPT1) {
				MessageBox(NULL, "Air Plane", "Debug", MB_ICONEXCLAMATION | MB_OK);
			}
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

void CreateMyMenu() {
	hRoot = CreateMenu();
	if (!hRoot) return ;
	HMENU pop1 = CreatePopupMenu();
	AppendMenu(hRoot, MF_POPUP, (UINT_PTR) pop1, "Operation");
	AppendMenu(pop1, MF_STRING, IDM_OPT1, "Air Plane");
	// second InsertMenuItem
	MENUITEMINFO mif;
	mif.cbSize = sizeof(MENUITEMINFO);
	mif.cch = 100;
	mif.dwItemData = NULL;
	mif.dwTypeData = "About";
	mif.fMask = MIIM_ID | MIIM_STRING | MIIM_STATE;
	mif.fState = MFS_ENABLED;
	mif.wID = IDM_OPT2;
	InsertMenuItem(pop1, IDM_OPT2, FALSE, &mif);	
}