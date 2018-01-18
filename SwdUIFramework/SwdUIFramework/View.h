#ifndef _VIEW_H
#define _VIEW_H
#include "Stdafx.h"
namespace swd
{
	namespace ui
	{
		class View : public Object
		{
		public:
			View();
			virtual ~View();

			// Register the window class and call methods for instantiating drawing resources
			virtual HRESULT Initialize();

			// Process and dispatch messages
			virtual void RunMessageLoop();

			virtual void SetOnClickListener(ListenerCallBack _callback);//×¢²á¼àÌýcallback
			virtual void AddSubView(View *subview);
			// Draw content.
			virtual HRESULT OnRender();
			virtual void OnClick(void* sender, swd::Point point, bool &handled);
			virtual ID2D1HwndRenderTarget* GetContext();
			virtual HRESULT ReleaseContext();
		protected:
			// Initialize device-independent resources.
			virtual HRESULT CreateDeviceIndependentResources();

			// Initialize device-dependent resources.
			virtual HRESULT CreateDeviceResources();

			// Release device-dependent resource.
			virtual void DiscardDeviceResources();

			virtual void SetRect();

			// Resize the render target.
			virtual void OnResize(
				UINT width,
				UINT height
				);

			//void btnClicked(void* sender);
			// The windows procedure.
			static LRESULT CALLBACK WndProc(
				HWND hWnd,
				UINT message,
				WPARAM wParam,
				LPARAM lParam
				);
			virtual void hitTest()
			{

			}
			virtual bool PointInside(Point point);
		protected:
			ID2D1Factory* m_pDirect2dFactory;
			ID2D1HwndRenderTarget* m_pRenderTarget;
			ID2D1SolidColorBrush* m_pLightSlateGrayBrush;
			ID2D1SolidColorBrush* m_pCornflowerBlueBrush;

			ListenerCallBack callback;
		public:
			HWND m_parentHWND;
			HWND m_hwnd;
			std::vector<View*> subviews;
			RECT rect;
		};
	}
}

#endif