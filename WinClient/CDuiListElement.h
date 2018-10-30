#pragma once
#include <Shlobj.h>
#include <UIlib.h>
#pragma comment(lib, "DuiLib_ud.lib")
using namespace DuiLib;

class CDuiListElement : public CListContainerElementUI
{
public:
	explicit CDuiListElement();
	virtual ~CDuiListElement();
};

