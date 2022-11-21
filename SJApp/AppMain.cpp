#include <SJEngineBasePublic.h>
#include <SJEnginePlatformPublic.h>
#include <SJEngineClientPublic.h>
#include <SJWindow.h>

#include <Windows.h>
#include "SJCore.h"
#include <SJDebug.h>

int __stdcall wWinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR    lpCmdLine,
    int       nCmdShow)
{
    // ������â ����
    SJWindow::CreateSJWindow(hInstance, L"Super Mario Bros 3", { 100, 100 }, { 768, 672 });

    // ������ ������.
    SJWindow::Loop<SJCore>();
    
	return 0;
}