#ifndef _UIMESSAGEBOX_H
#define _UIMESSAGEBOX_H
#include "Stdafx.h"
namespace swd
{
	namespace ui
	{
		class UIMessageBox
		{
		protected:
			HWND hwnd;
			LPCWSTR content;
		public:
			UIMessageBox()
				:hwnd(NULL),
				content(L"OK")
			{
			}
			UIMessageBox(LPCWSTR _content)
				:hwnd(NULL),
				content(_content)
			{
			}
			UIMessageBox(HWND _hwnd , LPCWSTR _content)
				:hwnd(_hwnd),
				content(_content)
			{
			}
			void ShowWarn()
			{
				::MessageBox(NULL, content, L"Warning",MB_OKCANCEL);
			}
			void Show()
			{
				::MessageBox(NULL, content, L"Dialog", MB_OKCANCEL);
			}
		};
	}
}

#endif