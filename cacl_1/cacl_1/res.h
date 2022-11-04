#pragma once
//按钮
#define BUTBACK     0       //<-
#define BUTCE       1
#define BUTC        2
#define BUTEXCPT    3       //÷
#define BUT7        4
#define BUT8        5
#define BUT9        6
#define BUTMUL      7       //*
#define BUT4        8
#define BUT5        9
#define BUT6        10
#define BUTMINUS    11      //-
#define BUT1        12
#define BUT2        13
#define BUT3        14
#define BUTADD      15      //+
#define BUT0        16
#define BUTDEC      17      //.
#define BUTNEG      18      //负号
#define BUTEQUAL    19      //=
//开关
#define TRUE 1
#define FALSE 0

struct button_class
{
    int iStyle;
    TCHAR* szText;

};
struct button_class button[20] = {
    BS_PUSHBUTTON,TEXT("<-"),
    BS_PUSHBUTTON,TEXT("CE"),
    BS_PUSHBUTTON,TEXT("C"),
    BS_PUSHBUTTON,TEXT("/"),
    BS_PUSHBUTTON,TEXT("7"),
    BS_PUSHBUTTON,TEXT("8"),
    BS_PUSHBUTTON,TEXT("9"),
    BS_PUSHBUTTON,TEXT("*"),
    BS_PUSHBUTTON,TEXT("4"),
    BS_PUSHBUTTON,TEXT("5"),
    BS_PUSHBUTTON,TEXT("6"),
    BS_PUSHBUTTON,TEXT("-"),
    BS_PUSHBUTTON,TEXT("1"),
    BS_PUSHBUTTON,TEXT("2"),
    BS_PUSHBUTTON,TEXT("3"),
    BS_PUSHBUTTON,TEXT("+"),
    BS_PUSHBUTTON,TEXT("0"),
    BS_PUSHBUTTON,TEXT("."),
    BS_PUSHBUTTON,TEXT("+/-"),
    BS_PUSHBUTTON,TEXT("="),
};