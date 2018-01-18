#ifndef _UITEXTEDIT_H
#define _UITEXTEDIT_H
#include "View.h"
namespace swd
{
	namespace ui
	{
		class TextEdit : public View
		{
		public:
			TextEdit();
			void SetFrame(int _x, int _y, int _width, int _height);
			void SetHWND(HWND _hwnd);
			virtual HRESULT Initialize();
			virtual void SetRect();
			virtual HRESULT OnRender();
			virtual ~TextEdit();
			static LRESULT CALLBACK WndProc(
				HWND hWnd,
				UINT message,
				WPARAM wParam,
				LPARAM lParam
				);

		protected:
			virtual HRESULT CreateDeviceIndependentResources();
			virtual void DiscardDeviceResources();

		protected:
			IDWriteFactory *m_pDWriteFactory;
			IDWriteTextFormat *m_pTextFormat;
		public:
			int width;
			int height;
			int x;
			int y;
			const std::wstring content;
		};
	}
}

#endif