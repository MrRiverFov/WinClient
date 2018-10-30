#include "CDuiMenu.h"
#include "CheckboxMenu.h"

CheckBoxMenu::CheckBoxMenu(LPCTSTR pszXMLPath, HWND hWnd, const TCHAR *appName, const TCHAR *fileName, 
	const TCHAR *appPath) :m_strXMLPath(pszXMLPath), m_hwd(hWnd)
{
	memset(m_appPath, '\0', sizeof(m_appPath));
	memset(m_fileName, '\0', sizeof(m_fileName));
	memset(m_appName, '\0', sizeof(m_appName));

	lstrcpy(m_appPath, appPath);
	lstrcpy(m_appName, appName);
	lstrcpy(m_fileName, fileName);
}

LRESULT CheckBoxMenu::OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
	Close();
	bHandled = FALSE;

	return 0;
}

void CheckBoxMenu::Init(HWND hWndParent, POINT ptPos)
{
	Create(hWndParent, TEXT("MenuWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	::ClientToScreen(hWndParent, &ptPos);
	::SetWindowPos(*this, NULL, ptPos.x, ptPos.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
}

LRESULT CheckBoxMenu::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT res = 0;
	BOOL bHandled = TRUE;
	static bool addState = false;

	switch (uMsg)
	{
	case WM_KILLFOCUS:
		res = OnKillFocus(uMsg, wParam, lParam, bHandled);
		break;
	default:
		bHandled = FALSE;
		break;
	}

	if (bHandled || m_PaintManager.MessageHandler(uMsg, wParam, lParam, res))
	{
		return res;
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
}

void OutputDebugPrintfW(const wchar_t * strOutputString, ...)
{
	wchar_t strBuffer[4096] = { 0 };
	va_list vlArgs;
	va_start(vlArgs, strOutputString);
	_vsnwprintf_s(strBuffer, sizeof(strBuffer) - 1, strOutputString, vlArgs);
	//vsprintf(strBuffer,strOutputString,vlArgs);
	va_end(vlArgs);
	OutputDebugStringW(strBuffer);
}

int i = 0;
void CheckBoxMenu::Notify(TNotifyUI &msg)
{
	if (msg.sType == TEXT("selectchanged"))
	{
		if (msg.pSender->GetName() == TEXT("_chkAutoRun"))
		{
			//	--���ÿ����Զ�����
			setSelectedState(m_appName, msg.pSender->GetName());
		}
		if (msg.pSender->GetName() == TEXT("_chkAutoLogin"))
		{
			//	--���ô�����Զ���½
			setSelectedState(m_appName, msg.pSender->GetName());
		}

		/* �˳������ڰ�ť��Ҫ�ύ�������ڴ��� */
		if (msg.pSender->GetName() == TEXT("_chkExit"))
		{
			::PostMessage(m_hwd, MSG_TOPMENU_EXIT, msg.wParam, msg.lParam);
		}
		if (msg.pSender->GetName() == TEXT("_chkAbout"))
		{
			::PostMessage(m_hwd, MSG_TOPMENU_ABOUT, msg.wParam, msg.lParam);
		}
		PostMessage(WM_KILLFOCUS, msg.wParam, msg.lParam);
	}
}

/* appdata�ļ��Ƿ���ڣ����������ȡ·������ */
void CheckBoxMenu::checkSelectedState(const TCHAR *appName, const TCHAR *keyName)
{

	/* ��ȡAPPDATA�ļ���·�� */
	SHGetSpecialFolderPath(GetDesktopWindow(), m_appPath, CSIDL_LOCAL_APPDATA, FALSE);
	/* ��ӳ����ļ������� */
	lstrcat(m_appPath, TEXT("\\���̳�ֵϵͳ"));
	/* �����ļ��У��Ѵ��ڷ���ERROR_ALREADY_EXISTS ������ֱ�Ӵ��� */
	CreateDirectory(m_appPath, NULL);

	/* ����Ŀ¼ */
	lstrcat(m_appPath, TEXT("\\"));
	lstrcat(m_appPath, m_fileName);

	CCheckBoxUI *pCheck = static_cast<CCheckBoxUI*>(m_PaintManager.FindControl(keyName));
	int i = 0;

	/* �����˵���ʾ֮ǰ���������Ƿ�ѡ�� */
	switch (GetPrivateProfileIntW(appName, keyName, -1, m_appPath))
	{
	case -1:
		WritePrivateProfileStringW(appName, keyName, TEXT("0"), m_appPath);
		pCheck->SetBkImage(TEXT("file='Image/unchecked.png'"));
		break;
	case 0:
		pCheck->SetBkImage(TEXT("file='Image/unchecked.png'"));
		break;
	case 1:
		pCheck->SetBkImage(TEXT("file='Image/checked.png'"));
		break;
	default:
		break;
	}
}

void CheckBoxMenu::InitWindow()
{
	checkSelectedState(TEXT("TOPMENU"), TEXT("_chkAutoRun"));
	checkSelectedState(TEXT("TOPMENU"), TEXT("_chkAutoLogin"));
}

bool CheckBoxMenu::setSelectedState(const TCHAR *appName, const TCHAR *keyName)
{
	CCheckBoxUI *pCheck = static_cast<CCheckBoxUI*>(m_PaintManager.FindControl(keyName));
	/* ����ļ������ڣ�����Ĭ������/������ */
	switch (GetPrivateProfileIntW(appName, keyName, -1, m_appPath))
	{
	case -1:
		WritePrivateProfileStringW(appName, keyName, TEXT("0"), m_appPath);
		pCheck->SetBkImage(TEXT("file='Image/unchecked.png'"));
		break;
	case 1:
		WritePrivateProfileStringW(appName, keyName, TEXT("0"), m_appPath);
		pCheck->SetBkImage(TEXT("file='Image/unchecked.png'"));
		break;
	case 0:
		WritePrivateProfileStringW(appName, keyName, TEXT("1"), m_appPath);
		pCheck->SetBkImage(TEXT("file='Image/checked.png'"));
		break;
	default:
		break;
	}

	return true;
}
