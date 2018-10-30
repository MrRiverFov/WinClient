#include "CDuiMenu.h"

LRESULT CDuiMenu::OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
	Close();
	bHandled = FALSE;

	return 0;
}

void CDuiMenu::Init(HWND hWndParent, POINT ptPos)
{
	Create(hWndParent, TEXT("MenuWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	::ClientToScreen(hWndParent, &ptPos);
	::SetWindowPos(*this, NULL, ptPos.x, ptPos.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
}

LRESULT CDuiMenu::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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


void CDuiMenu::Notify(TNotifyUI & msg)
{
	/* 菜单实现需要将list改成checkbox */

	/* 菜单会收到两次itemclick消息 duilib BUG */
	/* 用sieve变量先过滤一次 */

	if (msg.sType == TEXT("itemclick"))
	{
		if (sieve == 1)
		{
			sieve = 0;
			return;
		}
		if (sieve == 0)	sieve = 1;

		/* 响应顶层菜单 */
		if (msg.pSender->GetName() == TEXT("lemt_AutoRun"))
		{
			configCls.setSelectState(TEXT("bk_AutoRun"), m_PaintManager);
			PostMessage(WM_KILLFOCUS, msg.wParam, msg.lParam);
		}
		if (msg.pSender->GetName() == TEXT("lemt_AutoLogin"))
		{
			configCls.setSelectState(TEXT("bk_AutoLogin"), m_PaintManager);
			PostMessage(WM_KILLFOCUS, msg.wParam, msg.lParam);
		}
		if (msg.pSender->GetName() == TEXT("lemt_About"))
		{
			//configCls.setSelectState(TEXT("bk_About"), m_PaintManager);
			configCls.setSelectState(TEXT("bk_About"), m_PaintManager);
			PostMessage(WM_KILLFOCUS, msg.wParam, msg.lParam);
		}
		if (msg.pSender->GetName() == TEXT("lemt_Exit"))
		{
			/* 焦点消失会导致类delete this,弹窗会出问题 */
			MessageBox(NULL, TEXT("确定退出吗？"), NULL, MB_OKCANCEL);
			//exit.
		}
	}
}


void CDuiMenu::InitWindow()
{
	sieve = 1;
	configCls.readSelectState(TEXT("bk_AutoRun"), m_PaintManager);
	configCls.readSelectState(TEXT("bk_AutoLogin"), m_PaintManager);
	configCls.readSelectState(TEXT("bk_About"), m_PaintManager);
}