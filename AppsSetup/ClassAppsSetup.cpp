#include "stdafx.h"
#include "ClassAppsSetup.h"




ClassAppsSetup::ClassAppsSetup()
{
	TCHAR tchcurrentpath[PathLenth];
	ZeroMemory(tchcurrentpath, PathLenth);
	::GetcurrentPath(tchcurrentpath);
	m_cstrCurrentPath = tchcurrentpath;
}


ClassAppsSetup::~ClassAppsSetup()
{

}


BOOL ClassAppsSetup::OnStart()
{
	GetInstallationCommonds();
	InstallApps();

	return TRUE;
}
BOOL ClassAppsSetup::GetInstallationCommonds()
{
	CStdioFile read;
	if (!read.Open(m_cstrCurrentPath + _T("\\installcommand.txt"), CFile::modeRead))
	{
		printf_s("Open   file   error!\n");
		return FALSE;
	}
	CString line;
	_tprintf(_T("The following installations is:"));
	_tprintf(_T("\n"));
	while (read.ReadString(line))
	{
		if (line.IsEmpty())
		{
			continue;
		}
		//CString tmp1=line.Mid(2, 1);  //第二个字符为:\则表示绝对路径(存在引号) "c:\windows\system32\cmd.exe"
		//CString tmp2 = line.Mid(1, 1);  //第一个字符为:\则表示绝对路径（不存在引号） c:\windows\system32\cmd.exe
		//if (tmp1.CompareNoCase(_T(":")) == 0 || tmp2.CompareNoCase(_T(":")) == 0)
		//{
		//	m_veInstallCommonds.push_back(line);
		//}
		//else
		//{
		//	m_veInstallCommonds.push_back(m_cstrCurrentPath + _T("\\") + line);
		//}
		m_veInstallCommonds.push_back(line);
		_tprintf(line);
		_tprintf(_T("\n"));
		fflush(stdout);
	}



	return TRUE;

}

//顺序执行安装程序，如果遇到安装失败，则继续执行下一个安装命令，不退出
BOOL ClassAppsSetup::InstallApps()
{
	for (vector<CString>::iterator it = m_veInstallCommonds.begin(); it != m_veInstallCommonds.end(); it++)
	{

		// 临时变量  
		CString sCommandLine;

		DWORD dwExitCode;
		PROCESS_INFORMATION pi;
		ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

		//STARTUPINFO si = { sizeof(si) };

		STARTUPINFO si; //隐藏进程窗口
		si.cb = sizeof(STARTUPINFO);
		si.lpReserved = NULL;
		si.lpDesktop = NULL;
		si.lpTitle = NULL;
		si.dwFlags = STARTF_USESHOWWINDOW;
#ifdef _WINDOOWS_SHOW

		si.wShowWindow = SW_SHOW;
#else
		si.wShowWindow = SW_HIDE;
#endif


		si.cbReserved2 = NULL;
		si.lpReserved2 = NULL;

		sCommandLine = *it;

		BOOL ret = CreateProcess(NULL, sCommandLine.GetBuffer(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
		if (ret) {
			// 关闭子进程的主线程句柄
			CloseHandle(pi.hThread);
			// 等待子进程的退出 
			_tprintf(_T("%s The programe of %s is installing\n"), GetCurrentTimeString().GetBuffer(),(*it).GetBuffer());
			fflush(stdout);
			WaitForSingleObject(pi.hProcess, INFINITE);
			// 获取子进程的退出码   
			GetExitCodeProcess(pi.hProcess, &dwExitCode);
			_tprintf(_T("%s The exitcode of %s is %d\n"), GetCurrentTimeString().GetBuffer(), sCommandLine.GetBuffer(), dwExitCode);
			fflush(stdout);
			if (dwExitCode != 0)
			{	
				_tprintf(_T("%s The programe installation failed!\n"), GetCurrentTimeString().GetBuffer());
				fflush(stdout);
				return FALSE;
			}
			
			// 关闭子进程句柄 
			CloseHandle(pi.hProcess);
			Sleep(1000 * 60);
		}
		else
		{
			DWORD dwerrorcode=::GetLastError();
			_tprintf(_T("%s %s installation is failed!\nThe errorcode is %d\n"), GetCurrentTimeString().GetBuffer(), sCommandLine.GetBuffer(), dwerrorcode);
			fflush(stdout);
			return FALSE;
			
			
		}

	}
	//CAtlRegExp
	_tprintf(_T("\n%s installation is finished!\n"), GetCurrentTimeString().GetBuffer());
	return TRUE;
}