#ifndef _UIBUTTON_H
#define _UIBUTTON_H
#include "View.h"
namespace swd{
	namespace ui{
		class Button : public View
		{
		public:
			enum UIButtonStyle {
				UIButtonStyleNormal = 0,
				UIButtonStyleHighlight,
				UIButtonStyleDisabled
			};
			Button(UIButtonStyle _style = UIButtonStyleNormal);
			Button(const std::wstring& _title, UIButtonStyle _style = UIButtonStyleNormal);
			void SetFrame(int _x, int _y, int _width, int _height);
			void SetHWND(HWND _hwnd);
			virtual HRESULT Initialize();
			virtual void SetRect();
			virtual HRESULT OnRender();
			virtual ~Button();
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
			const std::wstring title;
			UIButtonStyle style;
		};
	}
}
#endif