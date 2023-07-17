#include <windows.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>
#include <process.h>
#include <stdio.h>
#include <stdbool.h>
#include "zen_timer.h"

const char g_szClassName[] = "myWindowsClass";

const int width = 640;
const int height = 480;

static uintptr_t thread_test;

typedef uint32_t u32;

typedef struct {
    int x;
    int y;
} point;

typedef struct {
	int width;
	int height;
	u32 *pixels;
} Frame;

typedef struct {
	bool *quit;
	HWND *hwnd;
	Frame *frame;
} render_data_t;


Frame frame = {0};

static BITMAPINFO  frame_bitmap_info;
static HBITMAP frame_bitmap = 0;
static HDC frame_device_context = 0;
static bool quit = false;
static HWND window_handle;

// Global Windows/Drawing variables
HBITMAP hbmp;

static render_data_t render_data = {
	.quit = &quit,
	.hwnd = &window_handle,
	.frame = &frame,
};

void test_thread(void *data) {
	render_data_t *pdata = (render_data_t*) data;
	float phase = 0.0f;
	float theta = phase;
	while (!*pdata->quit) {
		UpdateWindow(*pdata->hwnd);
		memset(pdata->frame->pixels, 0xffffff, pdata->frame->width*pdata->frame->height*4);
		// memset(pdata->frame->pixels, 0x0, pdata->frame->width*pdata->frame->height*4);
		
		short x, y;
		x = (short)(140.0*cos(theta*3.14/180.0)+280.0);
		y = (short)(-140.0*sin(theta*3.14/180.0)+240.0);
		point start = {.x= 280.0, .y =240.0};
		point end = {.x= x, .y = y};
		drawLine(pdata->frame, &start, &end, 0x000000);
		theta += 10;
		if (theta > 360.0) theta = theta - 360.0;
		Sleep(90l);
		// Update window
		InvalidateRect(*pdata->hwnd, NULL, FALSE);
	}
}

void test_frame();

void clear_frame();

void drawLine(Frame* frame, point* start, point* end, u32 color);

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, 
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, 
	int nCmdShow)
{
	WNDCLASSEX wc;
	// HWND hwnd;
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

	frame_bitmap_info.bmiHeader.biSize = sizeof(frame_bitmap_info.bmiHeader);
	frame_bitmap_info.bmiHeader.biPlanes = 1;
	frame_bitmap_info.bmiHeader.biBitCount = 32;
	frame_bitmap_info.bmiHeader.biCompression = BI_RGB;
	frame_device_context = CreateCompatibleDC(NULL);

	window_handle = CreateWindowEx(
		WS_EX_APPWINDOW,
		g_szClassName,
		"An Animation Program",
		WS_MINIMIZEBOX | WS_SYSMENU | WS_POPUP | WS_CAPTION,
		CW_USEDEFAULT, CW_USEDEFAULT, width, height,
		NULL, NULL, hInstance, NULL);

	if(window_handle == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(window_handle, nCmdShow);
	UpdateWindow(window_handle);

	/* using CRT thread instead of  */
	// hTickThread = CreateThread(NULL, NULL, &dumbThreadProc, NULL, NULL, NULL);

	if ((thread_test = _beginthread(test_thread, 0, (void*)&render_data)) == -1) {
		MessageBox(NULL, "beginthread Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	while(GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
   
    PAINTSTRUCT  ps ;
    HDC          hdc ;

    switch(msg)
    {
        case WM_CREATE:
        break;
        case WM_SIZE:
			frame_bitmap_info.bmiHeader.biWidth = LOWORD(lParam);
			frame_bitmap_info.bmiHeader.biHeight = HIWORD(lParam);

			if (frame_bitmap) DeleteObject(frame_bitmap);
			frame_bitmap = CreateDIBSection(NULL, &frame_bitmap_info, DIB_RGB_COLORS, 
				(void*) &frame.pixels, 0, 0);
			SelectObject(frame_device_context, frame_bitmap);

			frame.width = LOWORD(lParam);
			frame.height = HIWORD(lParam);
        break;
        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);
			// clear_frame();
			// test_frame();

			static HDC buffered_device_context;
			// FillRect(hdc, &ps.rcPaint, (HBRUSH)GetStockObject(GRAY_BRUSH));
			BitBlt(hdc, ps.rcPaint.left, ps.rcPaint.top,
				ps.rcPaint.right - ps.rcPaint.left, 
				ps.rcPaint.bottom - ps.rcPaint.top, 
				frame_device_context, 
				ps.rcPaint.left, 
				ps.rcPaint.top, 
				SRCCOPY);
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

void clear_frame() {
	for (int y = 0; y < frame.height; ++y) {
		for (int x = 0; x < frame.width; ++x) {
			frame.pixels[y * frame.width + x] = 0xffffff;
		}
	}
}

void test_frame() {
	int center_x = frame.width / 2;
	int center_y = frame.height / 2;
	point start; start.x = 27;start.y = 59;
	point end; end.x = 379; end.y = 219;
	// drawLine(&frame, &start, &end, 0x00ff80);
	drawLine(&frame, &start, &end, 0x000000);
}

void drawLine(Frame* frame, point* start, point* end, u32 color)
{
	assert(start->x >= 0 && start-> x < frame->width);
	assert(start->y >= 0 && start-> y < frame->height);
	assert(end->x >= 0 && end-> x < frame->width);
	assert(end->y >= 0 && end-> y < frame->height);

	// grey scale level 256
	// intensityBits denotes bits used to represent color 8
	unsigned short IntensityShift, ErrorAdj, ErrorAcc;
	unsigned short ErrorAccTemp, Weighting, WeightingComplementMask;
	short DeltaX, DeltaY, Temp, XDir;

	int x0 = start->x, x1 = end->x, y0 = start->y, y1 = end->y;
	/* make sure line runs from top to bottom */
	if (y0 > y1) {
		Temp = y0; y0 = y1; y1 = Temp;
		Temp = x0; x0 = x1; x1 = Temp;
	}
	/* Draw the initial pixel, which is always exactly intersected by
      the line and so needs no weighting */
	frame->pixels[y0 * frame->width + x0] = color;

	if ((DeltaX = x1 - x0) >= 0)
	{
		XDir = 1;
	} else {
		XDir = -1;
		DeltaX = -DeltaX;
	}
	/* Special-case horizontal, vertical, and diagonal lines, which
      require no weighting because they go right through the center of
      every pixel */

	if ((DeltaY = y1 -y0) == 0)
	{
		while (DeltaX-- != 0)
		{
			x0 += XDir;
			frame->pixels[y0 * frame->width + x0] = color;
		}
		return ;
	}
	if (DeltaX == 0) {
		do {
			y0++;
			frame->pixels[y0 * frame->width + x0] = color;
		} while (--DeltaY != 0);
		return ;
	}
	if (DeltaX == DeltaY) {
		do {
			x0 += XDir;
			y0++;
			frame->pixels[y0 * frame->width + x0] = color;
		} while(--DeltaY != 0);
		return ;
	}

	/* Line is not horizontal, diagonal, or vertical */
	ErrorAcc = 0;
	/* # of bits by which to shift ErrorAcc to get intensity level */
	IntensityShift = 16 - 8;
	/* Mask used to flip all bits in an intensity weighting, producing the
      result (1 - intensity weighting) */
	WeightingComplementMask = 256 - 1;

	if (DeltaY > DeltaX) {
		/* Y-major line; calculate 16-bit fixed-point fractional part of a
         pixel that X advances each time Y advances 1 pixel, truncating the
         result so that we won't overrun the endpoint along the X axis */
		ErrorAdj = ((unsigned long) DeltaX << 16) / (unsigned long) DeltaY;
		/* Draw all pixels other than the first and last */
		while(--DeltaY) {
			ErrorAccTemp = ErrorAcc;
			ErrorAcc += ErrorAdj;
			if (ErrorAcc <= ErrorAccTemp) {
				/* The error accumulator turned over, so advance the X coord */
				x0 += XDir;
			}
			y0++; /* Y-major, so always advance Y */
			/* The IntensityBits most significant bits of ErrorAcc give us the
            intensity weighting for this pixel, and the complement of the
            weighting for the paired pixel */
			Weighting = ErrorAcc >> IntensityShift;
			frame->pixels[y0 * frame->width + x0] = color + Weighting;
			frame->pixels[y0 * frame->width + x0 + XDir] = color + (Weighting ^ WeightingComplementMask);
		}
		/* Draw the final pixel, which is 
         always exactly intersected by the line
         and so needs no weighting */
		frame->pixels[y1 * frame->width + x1] = color;
		return ;
	}
	/* It's an X-major line; calculate 16-bit fixed-point fractional part of a
      pixel that Y advances each time X advances 1 pixel, truncating the
      result to avoid overrunning the endpoint along the X axis */
	ErrorAdj = ((unsigned long) DeltaY << 16) /(unsigned long) DeltaX;
	while (--DeltaX)
	{
		ErrorAccTemp = ErrorAcc;
		ErrorAcc += ErrorAdj;
		if (ErrorAcc <= ErrorAccTemp) {
			y0++;
		}
		x0 += XDir;
		Weighting = ErrorAcc >> IntensityShift;
		frame->pixels[y0 * frame->width + x0] = color + Weighting;
		frame->pixels[y0 * frame->width + x0] = color + (Weighting ^ WeightingComplementMask);
	}
	frame->pixels[y1 * frame->width + x1] = color;	
}