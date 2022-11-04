#define _CRT_SECURE_NO_WARNINGS //撤销sdl检查

#include <windows.h>
#include <stdio.h> 
#include <stdlib.h> 
#include "res.h"

char switch_d = FALSE;              //控制浮点数的开关
char switch_f = FALSE;              //控制首次输入的开关
char switch_x = FALSE;              //控制连续运算
char switch_y = FALSE;              //控制浮点和整数的混合运算

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);//声明回调函数


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
    static TCHAR szAppName[] = TEXT("MyWindows");
    HWND hwnd;
    MSG msg;
    WNDCLASS wndclass;

    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = NULL;
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName;

    if (!RegisterClass(&wndclass))
    {
        MessageBox(NULL, TEXT("这个程序需要在windows nt下运行"), szAppName, MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindow(szAppName,
        TEXT("MiniCalc"),
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL);

    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

#define NUM (sizeof(button) / sizeof button[0])

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    RECT rect;
    static int cxChar, cyChar;              //计算字符宽高，方便计算每个按钮的位置和大小
    int i = 0;
    int j = 0;                              //初始化每个按钮使用到的循环临时数
    int judeg = 0;                          //判断用户输入的按钮

    char num[2] = { 0 };                    //临时存放客户输入的数字
    static char num_a[10] = { 0 };          //输出到屏幕上的内容第一个值
    static char num_b[10] = { 0 };          //输出到屏幕上的内容第二个值

    static double num_f = 0.0;              //存放第一个数
    static double num_e = 0.0;              //存放第二个数
    static double num_r = 0.0;              //存放结果

    switch (message)
    {
    case WM_CREATE:
        cxChar = LOWORD(GetDialogBaseUnits());
        cyChar = HIWORD(GetDialogBaseUnits());
        //重置窗口大小
        GetWindowRect(hwnd, &rect);
        MoveWindow(hwnd, rect.left, rect.top, 27 * cxChar, 20 * cyChar, TRUE);
        //将按钮输出到屏幕上
        for (j = 0; j < 5; j++)
        {
            for (i = 0; i < 4; i++) {

                CreateWindow(TEXT("button"),
                    button[i + j * 4].szText,
                    WS_CHILD | WS_VISIBLE | button[i + j * 4].iStyle,
                    cxChar * i * 6 + 10, 80 + j * 40,
                    40, 30,
                    hwnd, (HMENU)(i + j * 4),
                    ((LPCREATESTRUCT)lParam)->hInstance, NULL);
            }
        }
        return 0;
        //响应按钮
    case WM_COMMAND:
        hdc = GetDC(hwnd);
        judeg = LOWORD(wParam);
        //当点击按钮时输入数字或小数点，第一个数
        if (switch_f == FALSE && (judeg == BUT0 || judeg == BUT1 || judeg == BUT2 || judeg == BUT3 || judeg == BUT4
            || judeg == BUT5 || judeg == BUT6 || judeg == BUT7 || judeg == BUT8 || judeg == BUT9 || judeg == BUTDEC))
        {
            GetDlgItemTextA(hwnd, wParam, num, sizeof(num));
            strcat(num_a, num);
            TextOutA(hdc, 3 * cxChar, cyChar, num_a, strlen(num_a));
            num_f = atoi(num_a);
        }
        //当点击运算符时，将输入的字符转换为数值，将数放进计算区
        if (judeg == BUTADD || judeg == BUTMINUS || judeg == BUTMUL || judeg == BUTEXCPT)
        {
            if (switch_f == FALSE)
            {
                switch_f = TRUE;
            }
            switch_f += 1;
        }
        //第二个数,只有当第一个数的开关关闭时才能输入第二个数
        if (switch_f >= TRUE && (judeg == BUT0 || judeg == BUT1 || judeg == BUT2 || judeg == BUT3 || judeg == BUT4
            || judeg == BUT5 || judeg == BUT6 || judeg == BUT7 || judeg == BUT8 || judeg == BUT9 || judeg == BUTDEC))
        {
            GetDlgItemTextA(hwnd, wParam, num, sizeof(num));
            strcat(num_b, num);
            TextOutA(hdc, 3 * cxChar,2 * cyChar, num_b, strlen(num_b));
            num_e = atoi(num_b);
        }
        //点击等号
        if (judeg == BUTEQUAL)
        {
            switch_f == FALSE;
        }

        ReleaseDC(hwnd, hdc);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}
//四则运算
void* calculate()
{
    
}

