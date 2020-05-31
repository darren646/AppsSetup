#pragma once
#include<vector>
using namespace std;

class ClassAppsSetup
{
public:
	ClassAppsSetup();
	~ClassAppsSetup();

private:
	CString m_cstrCurrentPath;
	vector<CString> m_veInstallCommonds;
	


	//function
private:
	BOOL GetInstallationCommonds();
	BOOL InstallApps();



public:
	BOOL OnStart();
};

