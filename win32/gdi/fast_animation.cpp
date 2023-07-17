#include <Windows.h>
#include <iostream>
#include <cmath>
#include <strsafe.h>

void ErrorExit(LPTSTR lpszFunction)
{
	// Retrieve the system error message for the last-error code

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
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	// Display the error message and exit the process

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
	StringCchPrintf((LPTSTR)lpDisplayBuf,
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("%s failed with error %d: %s"),
		lpszFunction, dw, lpMsgBuf);
	MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
	ExitProcess(dw);
}

struct pixel {
	union {
		struct {
			unsigned char b, g, r, a;
		};
		int val;
	};

	pixel() {
		val = 0;
	}
};

// Windows client size
const int width = 375;
const int height = 375;

const int fps = 50;

// Global Windows/Drawing variables
HBITMAP hbmp;
HANDLE hTickThread;
HWND hwnd;
HDC hdcMem;

// Pointer to pixels
pixel* ppixel;

void onFrame(pixel* ppixel)
{
	pixel* p;
	static float frameoffset = 0;
	float px;
	float py;
	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			p = &ppixel[y * width + x];
			px = float(x) / float(width);
			py = float(y) / float(height);

			p->r = (unsigned char)(((cos(px + frameoffset * 10) / sin(py + frameoffset)) * cos(frameoffset * 3) * 10) * 127 + 127);
			p->g = ~p->r;
			p->b = 255;
		}
	}

	frameoffset += 0.005f;
}

DWORD WINAPI tickThreadProc(HANDLE handle)
{
	Sleep(50);
	ShowWindow(hwnd, SW_SHOW);

	HDC hdc = GetDC(hwnd);

	hdcMem = CreateCompatibleDC(hdc);
	HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hbmp);

	// milliseconds to wait each time
	int delay = 1000 / fps;
	for (;;)
	{
		onFrame(ppixel);

		BitBlt(hdc, 0, 0, width, height, hdcMem, 0, 0, SRCCOPY);

		Sleep(delay);
	}

	SelectObject(hdcMem, hbmOld);
	DeleteDC(hdc);
}

void MakeSurface(HWND hwnd)
{
	BITMAPINFO bmi;
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biWidth = width;
	bmi.bmiHeader.biHeight = -height; // order pixels from top to bottom
	bmi.bmiHeader.biPlanes = 1;

	
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = 0;
	bmi.bmiHeader.biXPelsPerMeter = 0;
	bmi.bmiHeader.biYPelsPerMeter = 0;
	bmi.bmiHeader.biClrUsed = 0;
	bmi.bmiHeader.biClrImportant = 0;
	bmi.bmiColors[0].rgbBlue = 0;
	bmi.bmiColors[0].rgbGreen = 0;
	bmi.bmiColors[0].rgbRed = 0;
	bmi.bmiColors[0].rgbReserved = 0;

	HDC hdc = GetDC(hwnd);

	hbmp = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (void**)&ppixel, NULL, 0);
	DeleteDC(hdc);

	hTickThread = CreateThread(NULL, NULL, &tickThreadProc, NULL, NULL, NULL);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		case WM_CREATE:
		{
			MakeSurface(hwnd);
		}
		break;
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			// Draw pixels to window when window needs repainting
			BitBlt(hdc, 0, 0, width, height, hdcMem, 0, 0, SRCCOPY);

			EndPaint(hwnd, &ps);
		}
		break;
		case WM_CLOSE:
		{
			DestroyWindow(hwnd);
		}
		break;
		case WM_DESTROY:
		{
			TerminateThread(hTickThread, 0);
			PostQuitMessage(0);
		}
		break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd
)
{
	WNDCLASSEX wc;
	MSG msg;

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hbrBackground = CreateSolidBrush(0);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = "animation_class";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;;
	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Failed to register window class.", "Error", MB_OK);
		return 0;
	}

	// Make window
	hwnd = CreateWindowEx(
		WS_EX_APPWINDOW,
		"animation_class",
		"Animation",
		WS_MINIMIZEBOX | WS_SYSMENU | WS_POPUP | WS_CAPTION,
		CW_USEDEFAULT, CW_USEDEFAULT, width, height,
		NULL, NULL, hInstance, NULL);

	if (!hwnd)
		ErrorExit((LPTSTR)TEXT("CreateWindowEX"));

	RECT rcClient, rcWindow;
	POINT ptDiff;

	// Get window and client sizes
	GetClientRect(hwnd, &rcClient);
	GetWindowRect(hwnd, &rcWindow);

	// Find offset between window size and client size
	ptDiff.x = (rcWindow.right - rcWindow.left) - rcClient.right;
	ptDiff.y = (rcWindow.bottom - rcWindow.top) - rcClient.bottom;

	// Resize client
	MoveWindow(hwnd, rcWindow.left, rcWindow.top, width + ptDiff.x, height + ptDiff.y, false);

	UpdateWindow(hwnd);

	while (GetMessage(&msg, 0, 0, NULL) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;

}