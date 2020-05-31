
// stdafx.cpp : source file that includes just the standard includes
// OutInSEPReg.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information



#include "common.h"




using namespace std;

BOOL GetcurrentPath(TCHAR tchFileName[])  //Get current path without last '\\'
{
	//TCHAR tchFileName[1024];
	GetModuleFileName(NULL, tchFileName, 1024);
	int ipathLen=_tcslen(tchFileName);
	for (int i = ipathLen-1; i >=0; i--)
	{
		if (tchFileName[i]=='\\')
		{
			tchFileName[i] = NULL;
			return TRUE;

		}

	}
	return FALSE;

}

BOOL Is64bitSystem()
{
	SYSTEM_INFO si;
	GetNativeSystemInfo(&si);
	if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 ||
		si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64)
		return TRUE;
	else
		return FALSE;
}

BOOL Is32bitSystem()
{
	return !Is64bitSystem();
}

CString GetCurrentTimeString()
{
	
	CTime nowtime = CTime::GetCurrentTime(); //��ȡϵͳ����
	CString currenttime = nowtime.Format("%Y-%m-%d %H:%M-%S");
	return currenttime;
}

//srand((unsigned)time(NULL));   ��ʼ��ʱ��Ҫ���ã�ʱ�����ӡ�����ѭ������֮ǰ���ҽ�����һ�Ρ�
int GetIntRand(double MIN, double MAX)
{
	int max;
	max = RAND_MAX;//rand()��������������ֵ
	int randnum = (int)(rand()*(MAX - MIN) / max + MIN);
	return randnum;
}
