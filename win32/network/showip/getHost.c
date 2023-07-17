#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include <winsock2.h>
#include <stdio.h>
#include <string.h>
#include <ws2tcpip.h>

#define ID_EDITCHILD 20001

const char g_szClassName[] = "getHostWindowClass";

void get_msg_text
(
   DWORD    dw_error, /* in   - Error code                                    */
   char  **pnc_msg    /* out  - Error message                                 */
);

void setcolor(int textcol, int backcol)
{
    if ((textcol % 16) == (backcol % 16))textcol++;
    textcol %= 16; backcol %= 16;
    unsigned short wAttributes = ((unsigned)backcol << 4) | (unsigned)textcol;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, wAttributes);
}

void writeToConsole(int color, LPCTSTR msg) {
    
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    setcolor(color, 0);
    if (!WriteFile(
			hStdout,               // output handle 
			msg,           // prompt string 
			strlen(msg), // string length 
			NULL,             // bytes written 
			NULL))
    {
        DWORD dw_error = GetLastError();
        char                *nc_error;
        get_msg_text(dw_error,
                    &nc_error);
    }
}

void get_msg_text
(
   DWORD    dw_error, /* in   - Error code                                    */
   char  **pnc_msg    /* out  - Error message                                 */
)
{
    DWORD dw_flags;
    dw_flags = FORMAT_MESSAGE_ALLOCATE_BUFFER
            | FORMAT_MESSAGE_FROM_SYSTEM
            | FORMAT_MESSAGE_IGNORE_INSERTS;
    FormatMessage(dw_flags,NULL,dw_error,LANG_SYSTEM_DEFAULT,(LPTSTR)pnc_msg,0,
                 NULL);
}

void showSelfIps(char* result) {
    struct addrinfo     *ps_address;
    void                *pv_address;
    char                *nc_error;
    DWORD                dw_error;
    WSADATA             s_wsaData;
    struct addrinfo       s_hints;
    char                 ac_ipstr[INET6_ADDRSTRLEN];
    struct sockaddr_in  *ps_ipv4;
    struct sockaddr_in6 *ps_ipv6;
    char                *pc_ipver;
    struct addrinfo     *ps_res;
    int                 i_status;
    if ((i_status = WSAStartup(MAKEWORD(2,2), &s_wsaData)) != 0) {
        dw_error = (DWORD)i_status;
        get_msg_text(dw_error,
                    &nc_error);
        // fprintf(stderr,"WSAStartup failed with code %d.\n",i_status);
        // fprintf(stderr,"%s\n",nc_error);
        LocalFree(nc_error);
    }

    if (LOBYTE(s_wsaData.wVersion) < 2 ||
       HIBYTE(s_wsaData.wVersion) < 2)
    {
        // fprintf(stderr,"Version 2.2 of Winsock is not available.\n");
        WSACleanup();
    }

    memset(&s_hints,0,sizeof(s_hints));
    s_hints.ai_family   = AF_UNSPEC;
    s_hints.ai_socktype = SOCK_STREAM;
    s_hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

    i_status = getaddrinfo(NULL,"3490",&s_hints,&ps_res);

    if (i_status != 0)
    {
        dw_error = (DWORD)WSAGetLastError();
        get_msg_text(dw_error,
                    &nc_error);
        // fprintf(stderr,"getaddrinfo failed with code %ld.\n",dw_error);
        // fprintf(stderr,"%s\n",nc_error);
        writeToConsole(14, nc_error);
        LocalFree(nc_error);
        WSACleanup();
    }

    for (ps_address = ps_res ;
        ps_address != NULL ;
        ps_address = ps_address->ai_next)
    {
        if (ps_address->ai_family == AF_INET) // IPv4
        {
            ps_ipv4 = (struct sockaddr_in *)ps_address->ai_addr;
            pv_address = &(ps_ipv4->sin_addr);
            pc_ipver = "IPv4";
        }
        else // IPv6
        {
            ps_ipv6 = (struct sockaddr_in6 *)ps_address->ai_addr;
            pv_address = &(ps_ipv6->sin6_addr);
            pc_ipver = "IPv6";
        }
        inet_ntop(ps_address->ai_family,pv_address,ac_ipstr,sizeof(ac_ipstr));

        // printf("  %s: %s\n",pc_ipver,ac_ipstr);
        // writeToConsole(14, ac_ipstr);
    }
    WSACleanup();
    freeaddrinfo(ps_res);

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
	wc.hbrBackground 		= (HBRUSH) (COLOR_WINDOW+1);
	wc.lpszMenuName 		= NULL;
	wc.lpszClassName 		= g_szClassName;
	wc.hIconSm 				= LoadIcon(NULL, IDI_APPLICATION);
	
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

    AllocConsole();
	
	hWnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"Get Host",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 320, 240,
		NULL, NULL, hInstance, NULL);
	if (hWnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
    
    writeToConsole(14, "success");

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
        static HWND hwndEdit;
        case WM_CREATE:
        {
            writeToConsole(15, "on create");

            hwndEdit = CreateWindowEx(
                0,
                "EDIT",
                NULL,
                WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
                20, 20, 270, 180,
                hWnd,
                (HMENU) ID_EDITCHILD,
                (HINSTANCE) GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                NULL
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