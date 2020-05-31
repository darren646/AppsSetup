#include "stdafx.h"
#include "ClassAppsSetup.h"


ClassAppsSetup::ClassAppsSetup()
{
	TCHAR tchcurrentpath[PathLenth];
	ZeroMemory(tchcurrentpath, PathLenth);
	GetCurrentPath(tchcurrentpath);
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
	while (read.ReadString(line))
	{
		if (line.IsEmpty())
		{
			continue;
		}
		m_veInstallCommonds.push_back(m_cstrCurrentPath + _T("\\") + line);
		_tprintf(line);
		_tprintf(_T("\n"));
	}



	return TRUE;

}


BOOL ClassAppsSetup::InstallApps()
{
	for (vector<CString>::iterator it = m_veInstallCommonds.begin(); it != m_veInstallCommonds.end(); it++)
	{

		// 临时变量  
		CString sCommandLine;

		DWORD dwExitCode;
		PROCESS_INFORMATION pi;
		ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

		STARTUPINFO si = { sizeof(si) };



		sCommandLine = *it;
		BOOL ret = CreateProcess(NULL, sCommandLine.GetBuffer(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
		if (ret) {
			// 关闭子进程的主线程句柄
			CloseHandle(pi.hThread);
			// 等待子进程的退出 
			_tprintf(_T("The programe of %s is installing\n"), (*it).GetBuffer());
			fflush(stdout);
			WaitForSingleObject(pi.hProcess, INFINITE);
			// 获取子进程的退出码   
			GetExitCodeProcess(pi.hProcess, &dwExitCode);
			_tprintf(_T("The exitcode of %s is %d\n"), sCommandLine,dwExitCode);
			fflush(stdout);
			if (dwExitCode != 0)
			{	
				_tprintf(_T("The programe installation failedd\n"));
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
			_tprintf(_T("%s installation is failed!\nThe errorcode is %d\n"), sCommandLine, dwerrorcode);
			fflush(stdout);
			return FALSE;
			
			
		}

	}
	//CAtlRegExp
	_tprintf(_T("McAfee installation is finished!\n"));
	return TRUE;
}