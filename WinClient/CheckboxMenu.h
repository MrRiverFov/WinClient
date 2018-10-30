#pragma once
#include <Shlobj.h>
#include <UIlib.h>
#pragma comment(lib, "DuiLib_ud.lib")
using namespace DuiLib;

#include "mestype.h"
#include <Shlobj.h>

class CheckBoxMenu : public WindowImplBase
{
public:
	explicit CheckBoxMenu(LPCTSTR pszXMLPath, HWND hWnd, const TCHAR *appName = TEXT("TOPMENU"), const TCHAR *fileName = TEXT("config.ini"),
		const TCHAR *appPath = TEXT("���̳�ֵϵͳ"));
	virtual LPCTSTR GetWindowClassName() const { return TEXT("CDuiMenu"); }
	virtual CDuiString GetSkinFile() { return m_strXMLPath; }
	virtual CDuiString GetSkinFolder() { return TEXT(""); }
	virtual void OnFinalMessage(HWND hWnd) { delete this; }
	virtual LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
	void Init(HWND hWndParent, POINT ptPos);
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual void Notify(TNotifyUI &msg);
	virtual void InitWindow(); 
	void checkSelectedState(const TCHAR *appName, const TCHAR *keyName);				/* ����appdataĿ¼�µ��ļ�����ӻ�ȡ������� */
	bool setSelectedState(const TCHAR *keyName, const TCHAR *appname = nullptr);		/* ����д������ */
protected:
	virtual ~CheckBoxMenu() {}
	CDuiString m_strXMLPath;

	TCHAR m_appPath[MAX_PATH+1];
	TCHAR m_appName[50];
	TCHAR m_fileName[50];

	HWND m_hwd;
};
