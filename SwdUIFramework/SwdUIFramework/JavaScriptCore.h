#include "Stdafx.h"

//compile resource define file
class JavaScriptCore
{
public:
	JavaScriptCore(std::wstring& fileName)
	{
		wchar_t* commandLine = (wchar_t*)fileName.c_str();//LPWSTR 是指针，应该创建unicode数组
		wchar_t applicationName[] = L"C:\\Program Files\\nodejs\\node.exe";
		PROCESS_INFORMATION pi;
		STARTUPINFO si = { sizeof(si) };
		BOOL status = ::CreateProcess(applicationName, (LPWSTR)commandLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
		if (!status)
		{
			printf("Error\n");
		}
		//拿到输出流，输出流重定向-- to be implement
		
		CloseHandle(pi.hThread);
		WaitForSingleObject(pi.hProcess, INFINITE);
		DWORD dwExitCode;
		GetExitCodeProcess(pi.hProcess, &dwExitCode);
		CloseHandle(pi.hProcess);
	}
};