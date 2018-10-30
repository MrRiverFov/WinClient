#include "ConfigCls.h"



ConfigCls::ConfigCls( TCHAR *configName, TCHAR *folderName  )
{
	if (!configName && !folderName)
	{
		memset(_defaultFolderName, '\0', sizeof(_defaultFolderName));
		memset(_defaultConfigName, '\0', sizeof(_defaultConfigName));
		lstrcpy(_defaultConfigName, TEXT("\\config.ini"));
		lstrcpy(_defaultFolderName, TEXT("\\WinClient"));
	}
	/*
	else if(!configName)
	{
		_defaultConfigName = new TCHAR[lstrlen(configName)];
		_defaultFolderName = new TCHAR[lstrlen(TEXT("\\WinClient"))];
		memset(_defaultFolderName, '\0', sizeof(_defaultFolderName));
		memset(_defaultConfigName, '\0', sizeof(_defaultConfigName));
	}
	else
	{
		_defaultConfigName = new TCHAR[lstrlen(configName)];
		_defaultFolderName = new TCHAR[lstrlen(folderName)];
		memset(_defaultFolderName, '\0', sizeof(_defaultFolderName));
		memset(_defaultConfigName, '\0', sizeof(_defaultConfigName));
	}*/

	memset(_defaultConfigPath, '\0', sizeof(_defaultConfigPath));

	/* 获取APPDATA文件夹路径 */
	SHGetSpecialFolderPath(GetDesktopWindow(), _defaultConfigPath, CSIDL_LOCAL_APPDATA, FALSE);
	/* 添加程序文件夹名字 */
	lstrcat(_defaultConfigPath, _defaultFolderName);
	/* 创建文件夹，已存在返回ERROR_ALREADY_EXISTS 不存在直接创建 */
	CreateDirectory(_defaultConfigPath, NULL);

	/* 完整目录 */
	lstrcat(_defaultConfigPath, _defaultConfigName);

	/* 创建/检查配置文件 */
	if (GetPrivateProfileIntW(TEXT("menuList"), TEXT("bk_AutoRun"), -1, _defaultConfigPath) == -1)
		WritePrivateProfileStringW(TEXT("menuList"), TEXT("bk_AutoRun"), TEXT("0"), _defaultConfigPath);
	if(GetPrivateProfileIntW(TEXT("menuList"), TEXT("bk_AutoLogin"), -1, _defaultConfigPath) == -1)
		WritePrivateProfileStringW(TEXT("menuList"), TEXT("bk_AutoLogin"), TEXT("0"), _defaultConfigPath);
	if (GetPrivateProfileIntW(TEXT("menuList"), TEXT("bk_About"), -1, _defaultConfigPath) == -1)
		WritePrivateProfileStringW(TEXT("menuList"), TEXT("bk_About"), TEXT("0"), _defaultConfigPath);
}

ConfigCls::~ConfigCls()
{
}

bool ConfigCls::setSelectState(const TCHAR *bkName, const CPaintManagerUI &_paintManager)
{
	int i = 0;
	CButtonUI *pBtn = static_cast<CButtonUI*>(_paintManager.FindControl(bkName));

	switch (GetPrivateProfileIntW(TEXT("menuList"), bkName, -1, _defaultConfigPath))
	{
	case -1:
		WritePrivateProfileStringW(TEXT("menuList"), bkName, TEXT("1"), _defaultConfigPath);
		pBtn->SetBkImage(TEXT("file='Image/checked.png'"));
		break;
	case 1:
		i=WritePrivateProfileStringW(TEXT("menuList"), bkName, TEXT("0"), _defaultConfigPath);
		pBtn->SetBkImage(TEXT("file='Image/unchecked.png'"));
		break;
	case 0:
		WritePrivateProfileStringW(TEXT("menuList"), bkName, TEXT("1"), _defaultConfigPath);
		pBtn->SetBkImage(TEXT("file='Image/checked.png'"));
		break;
	default:
		break;
	}

	//OutputDebugPrintfW(TEXT("%s:%d\n"), bkName, i);

	return true;
}

bool ConfigCls::readSelectState(const TCHAR *bkName, const CPaintManagerUI &_paintManager)
{
	if (GetPrivateProfileIntW(TEXT("menuList"), bkName, -1, _defaultConfigPath) == -1)
		WritePrivateProfileStringW(TEXT("menuList"), bkName, TEXT("0"), _defaultConfigPath);

	CButtonUI *pBtn = static_cast<CButtonUI*>(_paintManager.FindControl(bkName));
	
	int i = GetPrivateProfileIntW(TEXT("menuList"), bkName, -1, _defaultConfigPath);
	switch (i)
	{
	case -1:
		WritePrivateProfileStringW(TEXT("menuList"), bkName, TEXT("1"), _defaultConfigPath);
		pBtn->SetBkImage(TEXT("file='Image/checked.png'"));
		break;
	case 1:
		pBtn->SetBkImage(TEXT("file='Image/checked.png'"));
		break;
	case 0:
		pBtn->SetBkImage(TEXT("file='Image/unchecked.png'"));
		break;
	default:
		break;
	}

	return true;
}

TCHAR ConfigCls::getPath()
{
	return TCHAR();
}

TCHAR ConfigCls::getName()
{
	return TCHAR();
}
