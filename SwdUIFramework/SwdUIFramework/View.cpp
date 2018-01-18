#include "View.h"
#include "UIMessageBox.h"
namespace swd
{
	namespace ui
	{
		// View constructor
		View::View() :
			m_parentHWND(NULL),
			m_hwnd(NULL),
			m_pDirect2dFactory(NULL),
			m_pRenderTarget(NULL),
			m_pLightSlateGrayBrush(NULL),
			m_pCornflowerBlueBrush(NULL)
		{
		}

		// View destructor
		// Releases the application's resources.
		View::~View()
		{
			SafeRelease(&m_pDirect2dFactory);
			SafeRelease(&m_pRenderTarget);
			SafeRelease(&m_pLightSlateGrayBrush);
			SafeRelease(&m_pCornflowerBlueBrush);
		}

		// Creates the application window and device-independent
		// resources.
		HRESULT View::Initialize()
		{
			HRESULT hr;

			// Initialize device-indpendent resources, such
			// as the Direct2D factory.
			hr = CreateDeviceIndependentResources();

			if (SUCCEEDED(hr))//看来创建WNDCLASS是windows上自定义控件的唯一正确的做法，即便要自绘！创建WNDCLASS则必创建WNDProc，看来每个控件都有自己的消息循环，除非自己接管消息循环
			{
				// Register the window class.
				WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
				wcex.style = CS_HREDRAW | CS_VREDRAW;
				wcex.lpfnWndProc = View::WndProc;
				wcex.cbClsExtra = 0;
				wcex.cbWndExtra = sizeof(LONG_PTR);
				wcex.hInstance = HINST_THISCOMPONENT;
				wcex.hbrBackground = (HBRUSH)COLOR_WINDOW;
				wcex.lpszMenuName = NULL;
				wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
				wcex.lpszClassName = L"D2DView";

				RegisterClassEx(&wcex);


				// Because the CreateWindow function takes its size in pixels,
				// obtain the system DPI and use it to scale the window size.
				FLOAT dpiX, dpiY;

				// The factory returns the current system DPI. This is also the value it will use
				// to create its own windows.
				m_pDirect2dFactory->GetDesktopDpi(&dpiX, &dpiY);


				// Create the window.
				m_hwnd = CreateWindow(
					L"D2DView",
					L"Direct2D Demo App",
					WS_OVERLAPPEDWINDOW,
					CW_USEDEFAULT,
					CW_USEDEFAULT,
					static_cast<UINT>(ceil(640.f * dpiX / 96.f)),
					static_cast<UINT>(ceil(480.f * dpiY / 96.f)),
					NULL,
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
				GetClientRect(m_hwnd, &this->rect);
			}

			return hr;
		}

		// Creates resources that are not bound to a particular device.
		// Their lifetime effectively extends for the duration of the
		// application.
		HRESULT View::CreateDeviceIndependentResources()
		{
			HRESULT hr = S_OK;
			// Create a Direct2D factory.
			hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);
			m_pDirect2dFactory = GetWinDirect2DFactory();
			if (m_pDirect2dFactory)
			{
				return hr;
			}
			return S_FALSE;
		}

		void View::SetRect()
		{
			GetClientRect(m_hwnd, &(this->rect));
		}
		// Creates resources that are bound to a particular
		// Direct3D device. These resources need to be recreated
		// if the Direct3D device dissapears, such as when the display
		// changes, the window is remoted, etc.
		HRESULT View::CreateDeviceResources()
		{
			HRESULT hr = S_OK;

			if (!m_pRenderTarget)
			{
				SetRect();
				D2D1_SIZE_U size = D2D1::SizeU(
					rect.right - rect.left,
					rect.bottom - rect.top
					);

				// Create a Direct2D render target.
				hr = m_pDirect2dFactory->CreateHwndRenderTarget(
					D2D1::RenderTargetProperties(),
					D2D1::HwndRenderTargetProperties(m_hwnd, size),
					&m_pRenderTarget
					);
			}

			return hr;
		}

		// Discards device-dependent resources. These resources must be
		// recreated when the Direct3D device is lost.
		void View::DiscardDeviceResources()
		{
			SafeRelease(&m_pRenderTarget);
			SafeRelease(&m_pLightSlateGrayBrush);
			SafeRelease(&m_pCornflowerBlueBrush);
		}

		// Runs the main window message loop.
		void View::RunMessageLoop()
		{
			MSG msg;

			while (GetMessage(&msg, NULL, 0, 0))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		ID2D1HwndRenderTarget* View::GetContext()//此两处可见三明治手法哈哈哈哈
		{
			HRESULT hr = CreateDeviceResources();

			if (SUCCEEDED(hr))
			{
				m_pRenderTarget->BeginDraw();

				m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

				m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
			}
			return m_pRenderTarget;
		}
		HRESULT View::ReleaseContext()//此两处可见三明治手法哈哈哈哈
		{
			HRESULT hr = m_pRenderTarget->EndDraw();
			if (hr == D2DERR_RECREATE_TARGET)
			{
				hr = S_OK;
				DiscardDeviceResources();
			}
			return hr;
		}
		// This method discards device-specific
		// resources if the Direct3D device dissapears during execution and
		// recreates the resources the next time it's invoked.
		HRESULT View::OnRender()
		{
			HRESULT hr = S_OK;
			
			GetContext();

			D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();
			//######Draw Code
			if (SUCCEEDED(hr))
			{
				// Create a gray brush.
				hr = m_pRenderTarget->CreateSolidColorBrush(
					D2D1::ColorF(D2D1::ColorF::LightSlateGray),
					&m_pLightSlateGrayBrush
					);
			}
			if (SUCCEEDED(hr))
			{
				// Create a blue brush.
				hr = m_pRenderTarget->CreateSolidColorBrush(
					D2D1::ColorF(D2D1::ColorF::CornflowerBlue),
					&m_pCornflowerBlueBrush
					);
			}
			hr = ReleaseContext();
			return hr;
		}
		void View::AddSubView(View* subview)
		{
			subviews.push_back(subview);
			subview->m_parentHWND = m_hwnd;
			subview->Initialize();
			//subview->OnRender();
			//InvalidateRect(m_hwnd, NULL, FALSE);
		}
		//  If the application receives a WM_SIZE message, this method
		//  resizes the render target appropriately.
		void View::OnResize(UINT width, UINT height)
		{
			CreateDeviceResources();
			if (m_pRenderTarget)
			{
				m_pRenderTarget->Resize(D2D1::SizeU(width, height));
				/*wchar_t* rectStr[20] = { 0 };
				wsprintf((LPWSTR)rectStr, L"%d - %d",
						 m_pRenderTarget->GetSize().width,
						 m_pRenderTarget->GetSize().height);
				UIMessageBox((LPWSTR)rectStr).Show();*/
				//CreateDeviceResources();
				//
			}
		}
		bool View::PointInside(Point point)
		{
			if (point.x > this->rect.left &&
				point.y > this->rect.top &&
				point.x < this->rect.right &&
				point.y < this->rect.bottom)
			{
				return true;
			}
			return false;
		}
		void View::SetOnClickListener(ListenerCallBack _callback)//注册监听callback
		{
			this->callback = _callback;
		}
		void View::OnClick(void* sender, Point point,bool &handled)
		{
			if (PointInside(point))
			{
				for (int i = 0; i < subviews.size(); i++)
				{
					if (subviews[i]->PointInside(point))
					{
						subviews[i]->OnClick(sender, point,handled);
						break;
					}
				}
				if (!handled && callback)
				{
					callback(sender);
					handled = true;
				}
			}
		}
		// Handles window messages.
		LRESULT CALLBACK View::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			LRESULT result = 0;

			if (message == WM_CREATE)
			{
				LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
				View *pView = (View *)pcs->lpCreateParams;

				::SetWindowLongPtrW(
					hwnd,
					GWLP_USERDATA,
					PtrToUlong(pView)
					);

				result = 1;
			}
			else
			{
				View *pView = reinterpret_cast<View *>(static_cast<LONG_PTR>(
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
					/*case WM_ERASEBKGND:
					{
						pView->GetContext();
						pView->ReleaseContext();
					}
						break;*/
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
//########Draw Code
// Draw a grid background.
/*int width = static_cast<int>(rtSize.width);
int height = static_cast<int>(rtSize.height);*/

/*for (int x = 0; x < width; x += 10)
{
m_pRenderTarget->DrawLine(
D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
D2D1::Point2F(static_cast<FLOAT>(x), rtSize.height),
m_pLightSlateGrayBrush,
0.5f
);
}

for (int y = 0; y < height; y += 10)
{
m_pRenderTarget->DrawLine(
D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
D2D1::Point2F(rtSize.width, static_cast<FLOAT>(y)),
m_pLightSlateGrayBrush,
0.5f
);
}*/

// Draw two rectangles.
//D2D1_RECT_F rectangle1 = D2D1::RectF(
//	rtSize.width / 2 - 50.0f,
//	rtSize.height / 2 - 50.0f,
//	rtSize.width / 2 + 50.0f,
//	rtSize.height / 2 + 50.0f
//	);

//D2D1_RECT_F rectangle2 = D2D1::RectF(
//	rtSize.width / 2 - 100.0f,
//	rtSize.height / 2 - 100.0f,
//	rtSize.width / 2 + 100.0f,
//	rtSize.height / 2 + 100.0f
//	);


//// Draw a filled rectangle.
//m_pRenderTarget->FillRectangle(&rectangle1, m_pLightSlateGrayBrush);

//// Draw the outline of a rectangle.
//m_pRenderTarget->DrawRectangle(&rectangle2, m_pCornflowerBlueBrush);