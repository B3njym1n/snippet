#include <windows.h>

const char g_szClassName[] = "myWindowsClass";
const int ID_TIMER = 1;

void OnPaint(HDC hdc);
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.style		 = 0;
	wc.lpfnWndProc	 = WndProc;
	wc.cbClsExtra	 = 0;
	wc.cbWndExtra	 = 0;
	wc.hInstance	 = hInstance;
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION);

	if(!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"An Animation Program",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 320, 240,
		NULL, NULL, hInstance, NULL);

	if(hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while(GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static POINT aptFigure [10] = { 10,70, 50,70, 50,10, 90,10, 90,50,
                                     30,50, 30,90, 70,90, 70,30, 10,30 };
    static int   cxClient, cyClient ;
    HDC          hdc ;
    int          i ;
    PAINTSTRUCT  ps ;
    POINT        apt[10] ;

    switch(msg)
    {
        case WM_CREATE:
        break;
        case WM_SIZE:
            cxClient = LOWORD(lParam);
            cyClient = HIWORD(lParam);
        break;
        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);
            // OnPaint(hdc);
            SelectObject (hdc, GetStockObject (GRAY_BRUSH)) ;

            for (i = 0 ; i < 10 ; i++)
            {
                apt[i].x = cxClient * aptFigure[i].x / 200 ;
                apt[i].y = cyClient * aptFigure[i].y / 100 ;
            }

            SetPolyFillMode (hdc, ALTERNATE) ;
            Polygon (hdc, apt, 10) ;

            for (i = 0 ; i < 10 ; i++)
            {
                apt[i].x += cxClient / 2 ;
            }

            SetPolyFillMode (hdc, WINDING) ;
            Polygon (hdc, apt, 10) ;
            EndPaint(hwnd, &ps);
        break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void OnPaint(HDC hdc)
{
    
}