// 控制台应用程序启动Windows程序也是可能的啊哈哈哈哈
// 汉皇寤寐思倾国 御宇多年求不得
// 隐藏控制台
// #pragma comment(linker, "/subsystem:\"windows\" /entry:\"wmainCRTStartup\"" )

#include <windows.h>  
#include "TCHAR.h" 
#include <stdio.h>

LRESULT CALLBACK WindowProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
	);

int _tmain(int argc, _TCHAR* argv[])
{
	HINSTANCE hInstance;
	hInstance = GetModuleHandle(NULL);//Key to Show Window
	WNDCLASS Draw;
	Draw.cbClsExtra = 0;
	Draw.cbWndExtra = 0;
	Draw.hCursor = LoadCursor(hInstance, IDC_ARROW);;
	Draw.hIcon = LoadIcon(hInstance, IDI_APPLICATION);;
	Draw.lpszMenuName = NULL;
	Draw.style = CS_HREDRAW | CS_VREDRAW;
	Draw.hbrBackground = (HBRUSH)COLOR_WINDOW;
	Draw.lpfnWndProc = WindowProc;
	Draw.lpszClassName = _T("DDraw");
	Draw.hInstance = NULL;


	RegisterClass(&Draw);

	HWND hwnd = CreateWindow(
		_T("DDraw"),           //上面注册的类名，要完全一致    
		L"由控制台创建的窗口",  //窗口标题文字    
		WS_OVERLAPPEDWINDOW, //窗口外观样式    
		100,             //窗口相对于父级的X坐标    
		100,             //窗口相对于父级的Y坐标    
		480,                //窗口的宽度    
		250,                //窗口的高度    
		NULL,               //没有父窗口，为NULL    
		NULL,               //没有菜单，为NULL    
		hInstance,          //当前应用程序的实例句柄    
		NULL);              //没有附加数据，为NULL    


	// 显示窗口    
	ShowWindow(hwnd, SW_SHOW);

	// 更新窗口    
	UpdateWindow(hwnd);
	// 消息循环    
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

// 消息处理函数的实现  
LRESULT CALLBACK WindowProc(
	_In_  HWND hwnd,
	_In_  UINT uMsg,
	_In_  WPARAM wParam,
	_In_  LPARAM lParam
	)
{
	switch (uMsg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}