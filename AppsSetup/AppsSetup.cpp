// AppsSetup.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "AppsSetup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象
CString cstrCurrentPath;
ClassAppsSetup appssetup;

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// 初始化 MFC 并在失败时显示错误
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO:  更改错误代码以符合您的需要
			_tprintf(_T("错误:  MFC 初始化失败\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO:  在此处为应用程序的行为编写代码。

			CString cstrtime = GetCurrentTimeString();
			

			TCHAR tchcurrentpath[PathLenth];
			ZeroMemory(tchcurrentpath, PathLenth);
			GetcurrentPath(tchcurrentpath);
			cstrCurrentPath = tchcurrentpath;

			
			USES_CONVERSION;
			std::string  strcurrentpath=T2A(tchcurrentpath);
			std::string strlogfullname = strcurrentpath + "\\AppsSetup.log";
			FILE *stream;
		
		/*	err = freopen_s(&stream, strlogfullname.c_str(), "w+", stdout);
			if (err != 0)
			{
				fprintf(stderr, "error redirecting stdout\n");
			}*/

			stream = freopen(strlogfullname.c_str(), "w+", stdout);  //file share

			if (stream==NULL)
			{
				fprintf(stderr, "error redirecting stdout\n");
			}
			
			_tprintf(cstrtime.GetBuffer());
			printf_s(" Please wait for products installation commands:\n");
			appssetup.OnStart();
			fflush(stdout);


		





		}
	}
	else
	{
		// TODO:  更改错误代码以符合您的需要
		_tprintf(_T("错误:  GetModuleHandle 失败\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
