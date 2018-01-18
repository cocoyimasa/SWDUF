#ifndef _DemoApp_H
#define _DemoApp_H
#include "Stdafx.h"
#include "View.h"
namespace swd
{
	namespace ui
	{
		class Button;
	}
}
using namespace swd;
using namespace swd::ui;

class DemoApp :public View
{
public:
	DemoApp();
	~DemoApp();
	virtual HRESULT OnRender();
	swd::ui::Button* button;
};
#endif