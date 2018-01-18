#include "UITextEdit.h"

namespace swd
{
	namespace ui
	{
		TextEdit::TextEdit()
		{

		}
		void TextEdit::SetFrame(int _x, int _y, int _width, int _height)
		{

		}
		void TextEdit::SetHWND(HWND _hwnd)
		{

		}
		void TextEdit::SetRect()
		{
			GetClientRect(m_hwnd, &(this->rect));
		}

		HRESULT TextEdit::Initialize()
		{
			HRESULT hr;

			hr = CreateDeviceIndependentResources();

			if (SUCCEEDED(hr))
			{
				WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
				wcex.style = CS_HREDRAW | CS_VREDRAW;
				wcex.lpfnWndProc = TextEdit::WndProc;
				wcex.cbClsExtra = 0;
				wcex.cbWndExtra = sizeof(LONG_PTR);
				wcex.hInstance = HINST_THISCOMPONENT;
				wcex.hbrBackground = (HBRUSH)COLOR_WINDOW;
				wcex.lpszMenuName = NULL;
				wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
				wcex.lpszClassName = L"D2DTextEdit";

				RegisterClassEx(&wcex);

				FLOAT dpiX, dpiY;

				m_pDirect2dFactory->GetDesktopDpi(&dpiX, &dpiY);

				m_hwnd = CreateWindow(
					L"D2DTextEdit",
					L"UITextEdit",
					WS_CHILD | WS_BORDER | WS_CLIPSIBLINGS | WS_VISIBLE,
					this->x,
					this->y,
					static_cast<UINT>(ceil(this->width * dpiX / 96.f)),
					static_cast<UINT>(ceil(this->height * dpiY / 96.f)),
					this->m_parentHWND,
					NULL,
					HINST_THISCOMPONENT,
					this
					);
				hr = m_hwnd ? S_OK : E_FAIL;
				if (SUCCEEDED(hr))
				{
					ShowWindow(m_hwnd, SW_SHOWNORMAL);
					UpdateWindow(m_hwnd);
				}
			}
			return hr;
		}

		HRESULT TextEdit::OnRender()
		{
			//如何自绘可编辑区
			//答案：无需绘制.只需绘制边框和内部背景，光标。
			//只需利用消息机制显示字符即可。
			return 0;
		}
		TextEdit::~TextEdit()
		{
			SafeRelease(&m_pDirect2dFactory);
			SafeRelease(&m_pRenderTarget);
			SafeRelease(&m_pLightSlateGrayBrush);
			SafeRelease(&m_pCornflowerBlueBrush);
			SafeRelease(&m_pDWriteFactory);
			SafeRelease(&m_pTextFormat);
		}
		LRESULT CALLBACK TextEdit::WndProc(
			HWND hWnd,
			UINT message,
			WPARAM wParam,
			LPARAM lParam
			)
		{
			return 0;
		}
		HRESULT TextEdit::CreateDeviceIndependentResources()
		{
			return View::CreateDeviceIndependentResources();
		}
		void TextEdit::DiscardDeviceResources()
		{
			SafeRelease(&m_pDirect2dFactory);
			SafeRelease(&m_pRenderTarget);
			SafeRelease(&m_pLightSlateGrayBrush);
			SafeRelease(&m_pCornflowerBlueBrush);
			SafeRelease(&m_pDWriteFactory);
			SafeRelease(&m_pTextFormat);
		}

		

		/*LRESULT CALLBACK TextEdit::WndProc(
			HWND hWnd,
			UINT message,
			WPARAM wParam,
			LPARAM lParam
			)
		{
			return 0;
		}*/
	}
}