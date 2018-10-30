#pragma once
#include "ConfigCls.h"
#include <UIlib.h>
#pragma comment(lib, "DuiLib_ud.lib")
using namespace DuiLib;

class CDuiMenu :
	public WindowImplBase
{
public:
	explicit CDuiMenu(LPCTSTR pszXMLPath) :m_strXMLPath(pszXMLPath) {}
	virtual LPCTSTR GetWindowClassName() const { return TEXT("CDuiMenu"); }
	virtual CDuiString GetSkinFile() { return m_strXMLPath; }
	virtual CDuiString GetSkinFolder() { return TEXT(""); }
	virtual void OnFinalMessage(HWND hWnd) { delete this; }
	virtual LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
	void Init(HWND hWndParent, POINT ptPos);
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual void Notify(TNotifyUI &msg);
	virtual void InitWindow();
protected:
	virtual ~CDuiMenu() {}
	CDuiString m_strXMLPath;
private:
	ConfigCls configCls;
	int sieve;
};
