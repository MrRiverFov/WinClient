#pragma once
#include <UIlib.h>
#pragma comment(lib, "DuiLib_ud.lib")
using namespace DuiLib;
#include "CheckboxMenu.h"
#include "mestype.h"

class CDuiFrame : public WindowImplBase
{
public:
	virtual LPCTSTR GetWindowClassName() const	{ return TEXT("WinClient"); }
	virtual CDuiString GetSkinFile()			{ return TEXT("duilib.xml"); }
	virtual CDuiString GetSkinFolder()			{ return TEXT(""); }
	virtual void Notify(TNotifyUI &msg);
	virtual void InitWindow();
	virtual LRESULT HandleWindow();
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	CDuiFrame() { }
protected:
};
