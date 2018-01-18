// ����̨Ӧ�ó�������Windows����Ҳ�ǿ��ܵİ���������
// �������˼��� ��������󲻵�
// ���ؿ���̨
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
		_T("DDraw"),           //����ע���������Ҫ��ȫһ��    
		L"�ɿ���̨�����Ĵ���",  //���ڱ�������    
		WS_OVERLAPPEDWINDOW, //���������ʽ    
		100,             //��������ڸ�����X����    
		100,             //��������ڸ�����Y����    
		480,                //���ڵĿ��    
		250,                //���ڵĸ߶�    
		NULL,               //û�и����ڣ�ΪNULL    
		NULL,               //û�в˵���ΪNULL    
		hInstance,          //��ǰӦ�ó����ʵ�����    
		NULL);              //û�и������ݣ�ΪNULL    


	// ��ʾ����    
	ShowWindow(hwnd, SW_SHOW);

	// ���´���    
	UpdateWindow(hwnd);
	// ��Ϣѭ��    
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

// ��Ϣ��������ʵ��  
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