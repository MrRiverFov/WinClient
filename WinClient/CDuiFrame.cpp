#include "CDuiFrame.h"


void CDuiFrame::Notify(TNotifyUI &msg)
{
	if (msg.sType == TEXT("click"))
	{
		if (msg.pSender->GetName() == TEXT("menuClose"))		PostQuitMessage(0);
		if (msg.pSender->GetName() == TEXT("menuSetting"))
		{
			/* 120是菜单的宽度 */
			POINT pt = { msg.ptMouse.x-120, msg.ptMouse.y };
			CheckBoxMenu *pMenu = new CheckBoxMenu(TEXT("checkBoxMenu.xml"), m_hWnd);

			
			pMenu->Init(*this, pt);
			pMenu->ShowWindow(true);
/*			CDialogBuilder builder;
			CControlUI *pRoot = builder.Create(TEXT("checkBoxMenu.xml"), (UINT)0, NULL, &m_PaintManager);

			m_PaintManager.AttachDialog(pRoot);*/
		}
		if (msg.pSender->GetName() == TEXT("_chkAutoRun"))
		{
			MessageBox(NULL, TEXT("111"), NULL, MB_OK);
		}
	}
	if (msg.sType == TEXT("selectchanged"))
	{
		CDuiString strName = msg.pSender->GetName();
		CTabLayoutUI *pControl = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(TEXT("TabLayoutMain")));

		if (msg.pSender->GetName() == TEXT("MyGame"))
		{
			pControl->SelectItem(1);

			
			CListUI *pList = static_cast<CListUI*>(m_PaintManager.FindControl(TEXT("_stgameList")));
			CDialogBuilder builder;
			
			pList->SetItemHLineColor(RGB(20,20,20));
			CHorizontalLayoutUI *pElement = static_cast<CHorizontalLayoutUI*>(builder.Create(TEXT("RunlistHeadElement.xml"), (UINT)0, NULL, &m_PaintManager));
			pList->Add(pElement);
			//pElement = static_cast<CListContainerElementUI*>(builder.Create(TEXT("RunlistElement.xml"), (UINT)0, NULL, &m_PaintManager));
			//pList->Add(pElement);
			CDialogBuilder builder2;
			CHorizontalLayoutUI *pCC = static_cast<CHorizontalLayoutUI*>(builder.Create(TEXT("RunlistElement.xml"), (UINT)0, NULL, &m_PaintManager));
			pList->Add(pCC);

			/* 修改list element. 解决手动添加list */
		}
		else if (msg.pSender->GetName() == TEXT("MyAccount"))
	
		{
			pControl->SelectItem(0);
		}
	}
}

void CDuiFrame::InitWindow()
{
}

LRESULT CDuiFrame::HandleWindow()
{
	return LRESULT();
}

LRESULT CDuiFrame::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	switch (uMsg)
	{
	case MSG_TOPMENU_EXIT:
		if (MessageBox(NULL, TEXT("12314"), TEXT("TIPS"), MB_YESNO | MB_ICONINFORMATION) == IDYES)
			PostQuitMessage(0);
		break;
		/* 只将topmenu的exit与about传到mainframe. 在menu弹窗会导致程序崩溃 */
	case MSG_TOPMENU_ABOUT:
		MessageBox(NULL, TEXT("create by amuyun-network.\n contants us:xxxx-xxxxxxx"), TEXT("About"), MB_OK | MB_ICONINFORMATION);
		break;
	default:
		break;
	}

	bHandled = false;
	return 0;
}