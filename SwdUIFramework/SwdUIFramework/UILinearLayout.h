#ifndef _UILINEARLAYOUT_H
#define _UILINEARLAYOUT_H
#include "View.h"
namespace swd
{
	namespace ui
	{
		class LinearLayout : public View
		{
			struct Distance
			{
				int Top;
				int Right;
				int Bottom;
				int Left;
			};
		public:
			LinearLayout();
			LinearLayout(RECT _rect);
			void addSubView(View* subview);
			~LinearLayout();
		public:
			RECT rect;
			Distance margin;
			Distance padding;
			std::vector<View*> subviews;
		protected:
			Distance baseMargin; // Layout margin
			Distance basePadding; // Layout padding
			Distance subviewMargin;
			Distance subviewPadding;
		};
	}
}
#endif