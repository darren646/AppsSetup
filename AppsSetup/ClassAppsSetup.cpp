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
		//CString tmp1=line.Mid(2, 1);  //�ڶ����ַ�Ϊ:\���ʾ����·��(��������) "c:\windows\system32\cmd.exe"
		//CString tmp2 = line.Mid(1, 1);  //��һ���ַ�Ϊ:\���ʾ����·�������������ţ� c:\windows\system32\cmd.exe
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

//˳��ִ�а�װ�������������װʧ�ܣ������ִ����һ����װ������˳�
BOOL ClassAppsSetup::InstallApps()
{
	for (vector<CString>::iterator it = m_veInstallCommonds.begin(); it != m_veInstallCommonds.end(); it++)
	{

		// ��ʱ����  
		CString sCommandLine;

		DWORD dwExitCode;
		PROCESS_INFORMATION pi;
		ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

		//STARTUPINFO si = { sizeof(si) };

		STARTUPINFO si; //���ؽ��̴���
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
			// �ر��ӽ��̵����߳̾��
			CloseHandle(pi.hThread);
			// �ȴ��ӽ��̵��˳� 
			_tprintf(_T("%s The programe of %s is installing\n"), GetCurrentTimeString().GetBuffer(),(*it).GetBuffer());
			fflush(stdout);
			WaitForSingleObject(pi.hProcess, INFINITE);
			// ��ȡ�ӽ��̵��˳���   
			GetExitCodeProcess(pi.hProcess, &dwExitCode);
			_tprintf(_T("%s The exitcode of %s is %d\n"), GetCurrentTimeString().GetBuffer(), sCommandLine.GetBuffer(), dwExitCode);
			fflush(stdout);
			if (dwExitCode != 0)
			{	
				_tprintf(_T("%s The programe installation failed!\n"), GetCurrentTimeString().GetBuffer());
				fflush(stdout);
				return FALSE;
			}
			
			// �ر��ӽ��̾�� 
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