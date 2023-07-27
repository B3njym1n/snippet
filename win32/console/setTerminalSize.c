#include <Windows.h>
#include <stdio.h>

HANDLE hStdout, hStdin;
CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

int main(void)
{

    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD cRead;
    if (hStdin == INVALID_HANDLE_VALUE ||
        hStdout == INVALID_HANDLE_VALUE)
    {
        MessageBox(NULL, TEXT("GetStdHandle"), TEXT("Console Error"),
            MB_OK);
        return 1;
    }

    if (! GetConsoleScreenBufferInfo(hStdout, &csbiInfo))
    {
        MessageBox(NULL, TEXT("GetConsoleScreenBufferInfo"),
            TEXT("Console Error"), MB_OK);
        return 1;
    }

    COORD newDwSize = csbiInfo.dwSize;
    newDwSize.X = 240;
    newDwSize.Y = 60;
    SetConsoleScreenBufferSize(hStdout, newDwSize); // set screen buffer size

    SMALL_RECT rect;
    rect.Top = 0;
    rect.Left = 0;
    rect.Right = 240; // 239 no error
    rect.Bottom = 60; // 59 no error
    if (!SetConsoleWindowInfo(
        hStdout,
        TRUE,
        &rect
    )) {
        DWORD dwError = GetLastError();
        fprintf(stdout, "%u\n", dwError);
        LPTSTR   pmsg = NULL;
        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                        0, 
                        dwError,
                        LANG_SYSTEM_DEFAULT,
                        &pmsg, 
                        0, 
                        NULL);
        fprintf(stdout, pmsg);
    }

    if (GetConsoleScreenBufferInfo(hStdout, &csbiInfo)) fprintf(stdout, "terminal size %d x %d\n", csbiInfo.srWindow.Right, csbiInfo.srWindow.Bottom);
    
    CHAR chBuffer[256];
    while (1)
    {
        if (! ReadFile(
            hStdin,    // input handle
            chBuffer,  // buffer to read into
            255,       // size of buffer
            &cRead,    // actual bytes read
            NULL) )    // not overlapped
        break;
        if (chBuffer[0] == 'q') break;
    }
}