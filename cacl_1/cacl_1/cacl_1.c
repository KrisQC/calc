#define _CRT_SECURE_NO_WARNINGS //����sdl���

#include <windows.h>
#include <stdio.h> 
#include <stdlib.h> 
#include "res.h"

char switch_d = FALSE;              //���Ƹ������Ŀ���
char switch_f = FALSE;              //�����״�����Ŀ���
char switch_x = FALSE;              //������������
char switch_y = FALSE;              //���Ƹ���������Ļ������

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);//�����ص�����


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
        MessageBox(NULL, TEXT("���������Ҫ��windows nt������"), szAppName, MB_ICONERROR);
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
    static int cxChar, cyChar;              //�����ַ���ߣ��������ÿ����ť��λ�úʹ�С
    int i = 0;
    int j = 0;                              //��ʼ��ÿ����ťʹ�õ���ѭ����ʱ��
    int judeg = 0;                          //�ж��û�����İ�ť

    char num[2] = { 0 };                    //��ʱ��ſͻ����������
    static char num_a[10] = { 0 };          //�������Ļ�ϵ����ݵ�һ��ֵ
    static char num_b[10] = { 0 };          //�������Ļ�ϵ����ݵڶ���ֵ

    static double num_f = 0.0;              //��ŵ�һ����
    static double num_e = 0.0;              //��ŵڶ�����
    static double num_r = 0.0;              //��Ž��

    switch (message)
    {
    case WM_CREATE:
        cxChar = LOWORD(GetDialogBaseUnits());
        cyChar = HIWORD(GetDialogBaseUnits());
        //���ô��ڴ�С
        GetWindowRect(hwnd, &rect);
        MoveWindow(hwnd, rect.left, rect.top, 27 * cxChar, 20 * cyChar, TRUE);
        //����ť�������Ļ��
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
        //��Ӧ��ť
    case WM_COMMAND:
        hdc = GetDC(hwnd);
        judeg = LOWORD(wParam);
        //�������ťʱ�������ֻ�С���㣬��һ����
        if (switch_f == FALSE && (judeg == BUT0 || judeg == BUT1 || judeg == BUT2 || judeg == BUT3 || judeg == BUT4
            || judeg == BUT5 || judeg == BUT6 || judeg == BUT7 || judeg == BUT8 || judeg == BUT9 || judeg == BUTDEC))
        {
            GetDlgItemTextA(hwnd, wParam, num, sizeof(num));
            strcat(num_a, num);
            TextOutA(hdc, 3 * cxChar, cyChar, num_a, strlen(num_a));
            num_f = atoi(num_a);
        }
        //����������ʱ����������ַ�ת��Ϊ��ֵ�������Ž�������
        if (judeg == BUTADD || judeg == BUTMINUS || judeg == BUTMUL || judeg == BUTEXCPT)
        {
            if (switch_f == FALSE)
            {
                switch_f = TRUE;
            }
            switch_f += 1;
        }
        //�ڶ�����,ֻ�е���һ�����Ŀ��عر�ʱ��������ڶ�����
        if (switch_f >= TRUE && (judeg == BUT0 || judeg == BUT1 || judeg == BUT2 || judeg == BUT3 || judeg == BUT4
            || judeg == BUT5 || judeg == BUT6 || judeg == BUT7 || judeg == BUT8 || judeg == BUT9 || judeg == BUTDEC))
        {
            GetDlgItemTextA(hwnd, wParam, num, sizeof(num));
            strcat(num_b, num);
            TextOutA(hdc, 3 * cxChar,2 * cyChar, num_b, strlen(num_b));
            num_e = atoi(num_b);
        }
        //����Ⱥ�
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
//��������
void* calculate()
{
    
}

