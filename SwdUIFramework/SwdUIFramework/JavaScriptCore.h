#include "Stdafx.h"

//compile resource define file
class JavaScriptCore
{
public:
	JavaScriptCore(std::wstring& fileName)
	{
		wchar_t* commandLine = (wchar_t*)fileName.c_str();//LPWSTR ��ָ�룬Ӧ�ô���unicode����
		wchar_t applicationName[] = L"C:\\Program Files\\nodejs\\node.exe";
		PROCESS_INFORMATION pi;
		STARTUPINFO si = { sizeof(si) };
		BOOL status = ::CreateProcess(applicationName, (LPWSTR)commandLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
		if (!status)
		{
			printf("Error\n");
		}
		//�õ��������������ض���-- to be implement
		
		CloseHandle(pi.hThread);
		WaitForSingleObject(pi.hProcess, INFINITE);
		DWORD dwExitCode;
		GetExitCodeProcess(pi.hProcess, &dwExitCode);
		CloseHandle(pi.hProcess);
	}
};