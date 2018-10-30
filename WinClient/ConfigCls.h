#pragma once
#include <Shlobj.h>
#include <UIlib.h>
#pragma comment(lib, "DuiLib_ud.lib")
using namespace DuiLib;

class ConfigCls
{
public:
	ConfigCls(TCHAR *configName = nullptr, TCHAR *folderName = nullptr);
	~ConfigCls();
	TCHAR getPath();
	TCHAR getName();
	bool setSelectState(const TCHAR *bkName, const CPaintManagerUI &_paintManager);
	bool readSelectState(const TCHAR *bkName, const CPaintManagerUI &_paintManager);
private:
	TCHAR _defaultFolderName[100];
	TCHAR _defaultConfigName[100];
	TCHAR _defaultConfigPath[MAX_PATH+1];
};