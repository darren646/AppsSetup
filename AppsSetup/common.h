

#pragma once
#include "stdafx.h"
#include < string.h >
#include <tchar.h>



#define PathLenth 1024




extern "C" BOOL GetcurrentPath(TCHAR []);
extern "C" BOOL Is64bitSystem();
extern "C" BOOL Is32bitSystem();
extern   CString GetCurrentTimeString();
extern "C" int GetIntRand(double MIN, double MAX);





