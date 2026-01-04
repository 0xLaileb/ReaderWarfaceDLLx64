#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <DbgHelp.h>
#include <Mmsystem.h>
#include <ShellAPI.h>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <iosfwd>
#include <TlHelp32.h>
#include <fcntl.h>
#include <Io.h>
#include <locale.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <Winsock2.h>
#include <winioctl.h>
#include <type_traits>
#include <thread>
#include <conio.h>
#include <atlstr.h>
#include <random>

using namespace std;

bool start_game = false;
#define _QWORD DWORD64
#define WINDOW_WARFACE FindWindow(NULL, (LPCSTR("Warface")))
string global = "";
char buffer[4024];

//#include "cHook_VMT.h"
//VMT_Hook_Tools* hkInterFace = new VMT_Hook_Tools;

#include "MinHook.h"
#include ".//mGameEngine.h"
#include "List_Classes.h"