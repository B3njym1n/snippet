#include <Windows.h>
#include <stdio.h>
#include <math.h>
#include "vec2.h"
#include "vec3.h"
#include "function.h"

HANDLE hStdout, hStdin;
CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

void LastErrorMsg() {
    DWORD    dw_error = GetLastError();
    char*   pmsg;
    
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                       0, 
                       dw_error,
                       LANG_SYSTEM_DEFAULT,
                       (LPTSTR) &pmsg, 
                       0, 
                       NULL);
    fprintf(stderr, pmsg);
    exit(1);
}

void SetWindow(int width, int height) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT  Rect = {
        0,
        0,
        width - 1,
        height - 1
    };
    COORD coord = {
        width,
        height
    };
    SetConsoleScreenBufferSize(hStdout, coord);
    SetConsoleWindowInfo(hStdout, TRUE, &Rect);
}

const char gradient[] = " .:!/r(l1Z4H9W8$@";
const int gradiantSize = 16;

int main(void)
{

    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdin == INVALID_HANDLE_VALUE ||
        hStdout == INVALID_HANDLE_VALUE)
    {
        LastErrorMsg();
    }

    if (! GetConsoleScreenBufferInfo(hStdout, &csbiInfo))
    {
        LastErrorMsg();
    }
    int width = 120;
	int height = 30;
    SetWindow(width, height);
    float aspect = (float) width / height;
    float pixelAspect = 11.0f/ 24.0f;
    char screen[ width* height + 1];
    screen[width * height] = '\0';
    
    /* Vec3 light = {-0.5, 0.5, -1.0};
    light = norm(light); */
    for (int t = 0; t < 10000; t++) {
        Vec3 light = {sin(t*0.001), cos(t * 0.001), -1.0};
        light = norm(light);
        for (int i = 0; i < width; ++i)
        {
            for (int j = 0; j < height; ++j)
            {
                Vec2 ij = {i, j};
                Vec2 wh = {width, height};
                Vec2 uv = subByValue(mulByValue(divByVec2(ij, wh), 2.0f), 1.0f);

                uv.x *= aspect * pixelAspect; // scale to y axis length
                int color = 0;
                char pixel = ' ';
                Vec3 ro = {-2, 0, 0}; // camera position
                Vec3 rd = {1, uv.x, uv.y}; // direction of beam
                rd = norm(rd);
                Vec2 intersection = sphere(ro, rd, 1);
                
                if (intersection.x > 0) { // lambda or length of rd vector
                    Vec3 itPoint = addByVec3(ro, mulByScale(rd, intersection.x));
                    Vec3 n = norm(itPoint);
                    float diff = dot(n, light);
                    color = (int) (diff * 10);
                    // color = 10;
                }
                color = clamp(color, 0, gradiantSize);
                pixel = gradient[color];
                screen[i + j * width] = pixel;
            }
        }
        DWORD cWritten;
        WriteFile(
            hStdout,    // input handle
            screen,
            lstrlen(screen),       // size of buffer
            &cWritten,    // actual bytes read
            NULL
        );
    }
    getchar();
}