#include "UIButton.h"
namespace swd
{
	namespace ui
	{
		Button::Button(Button::UIButtonStyle _style)
			:style(_style)
		{
		}
		Button::Button(const std::wstring& _title, 
					   Button::UIButtonStyle _style)
					   : title(_title), style(_style)
		{

		}
		void Button::SetFrame(int _x, int _y, int _width, int _height)
		{
			this->x = _x;
			this->y = _y;
			this->width = _width;
			this->height = _height;
		}
		void Button::SetHWND(HWND _hwnd)
		{
			this->m_hwnd = _hwnd;
			
		}
		HRESULT Button::CreateDeviceIndependentResources()
		{
			static const WCHAR msc_fontName[] = L"Verdana";
			static const FLOAT msc_fontSize = 12;
			View::CreateDeviceIndependentResources();
			HRESULT hr = S_OK;
			m_pDWriteFactory = GetWinDWriteFactory();

			// Create a DirectWrite text format object.
			hr = m_pDWriteFactory->CreateTextFormat(
				msc_fontName,
				NULL,
				DWRITE_FONT_WEIGHT_NORMAL,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_NORMAL,
				msc_fontSize,
				L"", //locale
				&m_pTextFormat
				);
			if (SUCCEEDED(hr))
			{
				// Center the text horizontally and vertically.
				m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
				m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
			}
			return hr;
		}
		HRESULT Button::Initialize()
		{
			HRESULT hr;

			hr = CreateDeviceIndependentResources();

			if (SUCCEEDED(hr))
			{
				WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
				wcex.style = CS_HREDRAW | CS_VREDRAW;
				wcex.lpfnWndProc = Button::WndProc;
				wcex.cbClsExtra = 0;
				wcex.cbWndExtra = sizeof(LONG_PTR);
				wcex.hInstance = HINST_THISCOMPONENT;
				wcex.hbrBackground = (HBRUSH)COLOR_WINDOW;
				wcex.lpszMenuName = NULL;
				wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
				wcex.lpszClassName = L"D2DButton";

				RegisterClassEx(&wcex);

				FLOAT dpiX, dpiY;

				m_pDirect2dFactory->GetDesktopDpi(&dpiX, &dpiY);

				m_hwnd = CreateWindow(
					L"D2DButton",
					L"UIButton",
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
				//GetClientRect(m_hwnd, &this->rect);
			}

			return hr;
		}
		void Button::SetRect()
		{
			GetClientRect(m_hwnd, &(this->rect));
			//this->rect = { 0, 0, width, height };
		}
		HRESULT Button::OnRender()
		{
			m_pRenderTarget = GetContext();
			//m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

			ID2D1SolidColorBrush *pSilverBrush;
			HRESULT hr = m_pRenderTarget->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::Silver),
				&pSilverBrush
				);
			if (SUCCEEDED(hr))
			{
				//renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
				D2D1_RECT_F rect = D2D1::RectF(0, 0, width, height);
				D2D1_SIZE_F renderTargetSize = m_pRenderTarget->GetSize();
				//D2D1_RECT_F rect = D2D1::RectF(20, 20, 100, 60);
				//D2D1_RECT_F rectBorder = D2D1::RectF(x - 1, y - 1, x + width + 1, y + height + 1);
				m_pRenderTarget->FillRectangle(&rect, pSilverBrush);
				//m_pRenderTarget->DrawRectangle(&rectBorder, pSilverBrush);
				ID2D1SolidColorBrush *pBlackBrush;
				HRESULT hr = m_pRenderTarget->CreateSolidColorBrush(
					D2D1::ColorF(D2D1::ColorF::Black),
					&pBlackBrush
					);
				if (SUCCEEDED(hr))
				{
					m_pRenderTarget->DrawTextW(
						(const WCHAR*)title.c_str(), 
						(UINT32)title.length(), 
						m_pTextFormat, 
						D2D1::RectF(0, 0, renderTargetSize.width, renderTargetSize.height), pBlackBrush);
				}
				if (hr == D2DERR_RECREATE_TARGET)
				{
					hr = S_OK;
					DiscardDeviceResources();
				}
				SafeRelease(&pSilverBrush);
				SafeRelease(&pBlackBrush);
			}
			ReleaseContext();

			return hr;
		}
		void Button::DiscardDeviceResources()
		{
			SafeRelease(&m_pDirect2dFactory);
			SafeRelease(&m_pRenderTarget);
			SafeRelease(&m_pLightSlateGrayBrush);
			SafeRelease(&m_pCornflowerBlueBrush);
			SafeRelease(&m_pDWriteFactory);
			SafeRelease(&m_pTextFormat);
		}
		Button::~Button()
		{
			SafeRelease(&m_pDirect2dFactory);
			SafeRelease(&m_pRenderTarget);
			SafeRelease(&m_pLightSlateGrayBrush);
			SafeRelease(&m_pCornflowerBlueBrush);
			SafeRelease(&m_pDWriteFactory);
			SafeRelease(&m_pTextFormat);
		}
		// Handles window messages.
		LRESULT CALLBACK Button::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			LRESULT result = 0;

			if (message == WM_CREATE)
			{
				LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
				Button *pView = (Button *)pcs->lpCreateParams;

				::SetWindowLongPtrW(
					hwnd,
					GWLP_USERDATA,
					PtrToUlong(pView)
					);

				result = 1;
			}
			else
			{
				Button *pView = reinterpret_cast<Button *>(static_cast<LONG_PTR>(
					::GetWindowLongPtrW(
					hwnd,
					GWLP_USERDATA
					)));

				bool wasHandled = false;

				if (pView)
				{
					switch (message)
					{
					case WM_SIZE:
					{
						UINT width = LOWORD(lParam);
						UINT height = HIWORD(lParam);
						pView->OnResize(width, height);
					}
					result = 0;
					wasHandled = true;
					break;
					case WM_LBUTTONDOWN:
					{
						Point point;
						point.x = LOWORD(lParam);//保存点的X坐标
						point.y = HIWORD(lParam);//保存点的Y坐标
						bool handled = false;
						pView->OnClick(pView, point, handled);
					}
					break;
					case WM_DISPLAYCHANGE:
					{
						InvalidateRect(hwnd, NULL, FALSE);
					}
					result = 0;
					wasHandled = true;
					break;
					case WM_PAINT:
					{
						pView->OnRender();
						ValidateRect(hwnd, NULL);
					}
					result = 0;
					wasHandled = true;
					break;

					case WM_DESTROY:
					{
						PostQuitMessage(0);
					}
					result = 1;
					wasHandled = true;
					break;
					}
				}

				if (!wasHandled)
				{
					result = DefWindowProc(hwnd, message, wParam, lParam);
				}
			}

			return result;
		}
	}
}