// AppsSetup.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "AppsSetup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������
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
		// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO:  ���Ĵ�������Է���������Ҫ
			_tprintf(_T("����:  MFC ��ʼ��ʧ��\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO:  �ڴ˴�ΪӦ�ó������Ϊ��д���롣

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
		// TODO:  ���Ĵ�������Է���������Ҫ
		_tprintf(_T("����:  GetModuleHandle ʧ��\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
