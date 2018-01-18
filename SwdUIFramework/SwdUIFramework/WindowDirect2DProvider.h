#ifndef _WINDOW_DIRECT2D_PROVIDER_H
#define _WINDOW_DIRECT2D_PROVIDER_H
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include "Basic.h"
namespace swd
{
	namespace ui
	{
		extern ID2D1Factory* GetWinDirect2DFactory();
		extern ID2D1HwndRenderTarget* GetWinDirect2DRenderTarget(Size size);
		extern IDWriteFactory* GetWinDWriteFactory();
		class View;
	}
}
extern void SetupDirect2DEnv(swd::ui::View *_view);
#endif