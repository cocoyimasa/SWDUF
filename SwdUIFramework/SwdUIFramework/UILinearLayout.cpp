#include "UILinearLayout.h"
#include "View.h"
namespace swd
{
	namespace ui
	{
		LinearLayout::LinearLayout()
		{
			this->baseMargin = { 10, 10, 10, 10 };
			this->basePadding = { 10, 10, 10, 10 };
		}
		LinearLayout::LinearLayout(RECT _rect)
			:rect(_rect)
		{
			this->baseMargin = { 10, 10, 10, 10 };
			this->basePadding = { 10, 10, 10, 10 };
		}
		void LinearLayout::addSubView(View* subview)
		{
			this->subviews.push_back(subview);
			//set origin point
			subview->m_parentHWND = m_hwnd;
			subview->Initialize();
			//set margin
			int width = subview->rect.right - subview->rect.left;
			int height = subview->rect.bottom - subview->rect.top;
			int basew = width * 0.1;
			int baseh = height * 0.1;
			this->subviewMargin = { baseh, basew, baseh, basew };//change view origin point
			
		}
		LinearLayout::~LinearLayout()
		{

		}
	}
}