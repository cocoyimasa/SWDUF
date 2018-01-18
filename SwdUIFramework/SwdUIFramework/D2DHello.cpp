#include "D2DHello.h"
#include "UIMessageBox.h"
#include "UIButton.h"
using namespace swd;
using namespace swd::ui;

void btnClicked(void* sender)
{
	UIMessageBox(L"btn was clicked").ShowWarn();
}

void btn1Clicked(void* sender)
{
	UIMessageBox(L"Hello World").ShowWarn();
}
// DemoApp constructor
DemoApp::DemoApp()
{
	SetupDirect2DEnv((View*)this);
	if (SUCCEEDED(this->Initialize()))
	{
		button = new Button();
		button->SetFrame(20, 20, 80, 40);
		this->AddSubView(button);
		button->SetOnClickListener(btnClicked);
		Button *button1 = new Button(L"BUTTON", Button::UIButtonStyleNormal);
		button1->SetFrame(100, 100, 60, 30);
		this->AddSubView(button1);
		button1->SetOnClickListener(btn1Clicked);
	}
}

HRESULT DemoApp::OnRender()
{
	for (int i = 0; i < subviews.size(); i++)
	{
		subviews[i]->OnRender();
	}
	return S_OK;
}

// DemoApp destructor
// Releases the application's resources.
DemoApp::~DemoApp()
{
}