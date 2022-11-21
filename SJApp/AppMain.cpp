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
    // 윈도우창 생성
    SJWindow::CreateSJWindow(hInstance, L"Super Mario Bros 3", { 100, 100 }, { 768, 672 });

    // 게임을 돌린다.
    SJWindow::Loop<SJCore>();
    
	return 0;
}