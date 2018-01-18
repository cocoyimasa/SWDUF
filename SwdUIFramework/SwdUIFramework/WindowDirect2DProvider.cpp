#include "WindowDirect2DProvider.h"
#include "View.h"
namespace swd
{
	namespace ui
	{
		class WindowDirect2DProvider : Object
		{
		protected:
			View *view;
			ID2D1Factory* pDirect2dFactory;
		public:

			WindowDirect2DProvider(View *_view)
				:view(_view)
			{
			}
			ID2D1Factory* GetWinDirect2DFactory()
			{
				ID2D1Factory* _pDirect2dFactory;
				HRESULT hr = D2D1CreateFactory(
					D2D1_FACTORY_TYPE_SINGLE_THREADED, 
					&_pDirect2dFactory);
				if (SUCCEEDED(hr))
				{
					this->pDirect2dFactory = _pDirect2dFactory;
					return _pDirect2dFactory;
				}
				else
				{
					return NULL;
				}
			}
			ID2D1HwndRenderTarget* GetWinDirect2DRenderTarget(Size size)
			{
				HRESULT hr = S_OK;
				ID2D1HwndRenderTarget* pRenderTarget = NULL;

				if (!pRenderTarget)
				{
					D2D1_SIZE_U d2dSize = D2D1::SizeU(
						size.x,
						size.y
						);

					// Create a Direct2D render target.
					// 派生类的m_hwnd获取有bug
					hr = pDirect2dFactory->CreateHwndRenderTarget(
						D2D1::RenderTargetProperties(),
						D2D1::HwndRenderTargetProperties(view->m_hwnd, d2dSize),
						&pRenderTarget
						);
					if (SUCCEEDED(hr))
					{
						return pRenderTarget;
					}
				}
				return NULL;
			}
			IDWriteFactory* GetWinDWriteFactory()
			{
				IDWriteFactory* pDWriteFactory;
				HRESULT hr = DWriteCreateFactory(
					DWRITE_FACTORY_TYPE_SHARED,
					__uuidof(IDWriteFactory),
					reinterpret_cast<IUnknown**>(&pDWriteFactory)
					);
				return pDWriteFactory;
			}
		};

		WindowDirect2DProvider* d2dProvider = 0;

		ID2D1Factory* GetWinDirect2DFactory()
		{
			return d2dProvider->GetWinDirect2DFactory();
		}
		ID2D1HwndRenderTarget* GetWinDirect2DRenderTarget(Size size)
		{
			return d2dProvider->GetWinDirect2DRenderTarget(size);
		}
		IDWriteFactory* GetWinDWriteFactory()
		{
			return d2dProvider->GetWinDWriteFactory();
		}
		
	}
}
using namespace swd;
using namespace swd::ui;
void SetupDirect2DEnv(swd::ui::View *_view)
{
	WindowDirect2DProvider provider(_view);
	d2dProvider = &provider;
}