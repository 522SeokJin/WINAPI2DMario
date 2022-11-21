#include "SJWindow.h"
#include <SJDebug.h>

#include <Windows.h>

// Static Var
float4 SJWindow::m_Size;
float4 SJWindow::m_Pos;
HWND SJWindow::m_WindowHWnd = nullptr;
bool SJWindow::m_bWindowProgress = true;

HDC SJWindow::m_WindowDC;
SJWinImage SJWindow::m_WindowMainImage;
SJWinImage SJWindow::m_DoubleBufferImage;

// member Var
SJWindow::SJWindow()
{

}

SJWindow::~SJWindow()
{

}


// Static Func

__int64 SJWindow::WINDOWEVENT(HWND _hWnd, unsigned int _EventType, unsigned __int64 _LValue, __int64 _SubValue)
{
	// 윈도우 이벤트 처리 함수
	switch (_EventType)
	{
	case WM_KILLFOCUS:
	{
		// 킬포커스 화면 바깥에서는 컨트롤이 되지않음
		break;
	}
	case WM_DESTROY:
	{
		m_bWindowProgress = false;
		break;
	}
	default:
		// 기본 메세지를 처리해주는 함수
		return DefWindowProcW(_hWnd, _EventType, _LValue, _SubValue);
	}

	return DefWindowProcW(_hWnd, _EventType, _LValue, _SubValue);
}

void SJWindow::BackBufferCopy()
{
	m_WindowMainImage.BitBlt(m_DoubleBufferImage);
}

void SJWindow::CreateSJWindow(HINSTANCE _ProcessHandle, const SJString& _Name, float4 _Pos, float4 _Size)
{
	
	{
		// 윈도우가 요구하는 윈도우형식의 명세
		// 여기에다가 정보 채워서 넣어주면
		// 이런 윈도우를 만들수 있는지 Os가 우리에게 알려줍니다.
		WNDCLASSEXW WCEX;

		WCEX.cbSize = sizeof(WNDCLASSEXW);
		// 윈도우 크기가 바뀌면 가로 세로 어디로 바뀌든 화면을 갱신해달라.
		WCEX.style = CS_HREDRAW | CS_VREDRAW;

		// 클래스를 만든 사람이
		// 그 클래스를 설계할때 남이 만든 함수를 대신 실행해주려고 만드는 경우가 있는데
		// 이러한 방식을 callback이라고 하고
		// 대표적인 예가 UI(BUTTON) 이다.
		WCEX.lpfnWndProc = &SJWindow::WINDOWEVENT;

		// 관심없어요 0넣어주면 됩니다.
		WCEX.cbClsExtra = 0;
		WCEX.cbWndExtra = 0;

		// 윈도우를 띄우고자하는 프로그램이 누구인지 알려준다.
		WCEX.hInstance = _ProcessHandle;

		// 윈도우 아이콘 핸들 (직접 만들수 없는데 선생님은 관심도 없습니다.)
		WCEX.hIcon = nullptr;
		WCEX.hIconSm = nullptr;

		// 윈도우 커서 핸들 (직접 만들거니까요.)
		WCEX.hCursor = nullptr;

		// 기본 윈도우 백그라운드 색 핸들
		// 흰색 윈도우
		WCEX.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

		// 메뉴
		WCEX.lpszMenuName = nullptr;

		// C++로 비교하자면
		// 클래스의 뭐과 같은 건가요?
		// 클래스의 이름이야.
		// 
		// 이런 윈도우형태의 이름을 
		// XXX라고 할께 나중에 XXX로 만들라고 하면
		// 지금 내가 세팅한 형태로 만들어줘야해.
		WCEX.lpszClassName = L"DEFWINDOW";

		// 윈도우 형태를 등록하는 함수고 실패하면
		// 0일거에요
		if (0 == RegisterClassExW(&WCEX))
		{
			unsigned int ErrorCode = GetLastError();

			SJDebug::AssertMsg(L"if (0 == RegisterClassExW(&WCEX))");
		}
	}

	// 이제 이 형식으로 윈도우를 띄워달라고 하면 됩니다.
	{
		//WS_OVERLAPPEDWINDOW (WS_OVERLAPPED     | \
		//                     WS_CAPTION        | \
		//					   WS_SYSMENU        | \
		//		               WS_THICKFRAME     | \
		//		               WS_MINIMIZEBOX    | \
		//		               WS_MAXIMIZEBOX)

		// WS_CAPTION 제목이 존재하고
		// WS_SYSMENU 메뉴가 존재하고
		// WS_THICKFRAME 얇은 외각선이 있고
		// WS_MINIMIZEBOX 최소화 버튼이 있고
		// WS_MAXIMIZEBOX 최대화 버튼이 있는
		// WS_OVERLAPPED 다른 윈도우위에오거나 아래에 올수 있는
		// 윈도우를 만들어주세요

		// 만들어진 윈도우의 권합니다.
		// L"DEFWINDOW" 모양의 윈도우를 만들어주세요.

		// 혹시나 나와 연결된 부모 윈도우가 있니?

		// 시작할때 8바이트 넣어줄수 있는데.
		m_WindowHWnd = CreateWindowW(L"DEFWINDOW", _Name.c_str(), WS_OVERLAPPEDWINDOW, _Pos.ix(), _Pos.iy(), _Size.ix(), _Size.iy(), nullptr, nullptr, _ProcessHandle, 0);

		if (nullptr == m_WindowHWnd)
		{
			SJDebug::AssertMsg(L"if (nullptr == m_WindowHWnd)");
			return;
		}

		// 윈도우의 보이는 상태를 조절해주는 함수
		// 전에 이야기했던대로
		// 뭡니까?
		ShowWindow(m_WindowHWnd, SW_SHOW);

		SetSizeAndPos(_Pos, _Size);
		// 윈도우를 한번 갱신해 주세요.
		UpdateWindow(m_WindowHWnd);

		m_WindowDC = GetDC(m_WindowHWnd);

		m_WindowMainImage.Create(m_WindowDC);
		m_DoubleBufferImage.Create(_Size);
	}
}

float4 SJWindow::GetSize()
{
	return m_Size;
}

void SJWindow::SetSize(float4 _Size)
{
	SetSizeAndPos(m_Pos, _Size);
}

void SJWindow::SetPos(float4 _Pos)
{
	SetSizeAndPos(_Pos, m_Size);
}

void SJWindow::SetSizeAndPos(float4 _Pos, float4 _Size)
{
	m_Size = _Size;
	m_Pos = _Pos;

	RECT rt = { 0, 0, m_Size.ix(), m_Size.iy() };

	// &rt 값을 얻어올 rect의 구조체
	// WS_OVERLAPPEDWINDOW 이 윈도우의 형태
	// false 메뉴가 있는지 없는지.
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);

	// 윈도우의 크기와 위치를 동시에 바꿀수 있는 함수입니다.

	// OS는 그 WINDOW를 제어할수 있는 HANDLE을 우리에게 줬다.
	// 우리는 요청할때 
	// SWP_NOZORDER 뜻이 있겠죠 이제 까먹어버림.
	// SWP_NOMOVE 포지션은 무시한다는 인자였네요.
	//  nullptr 전혀 모름.
	SetWindowPos(m_WindowHWnd, HWND_BOTTOM, _Pos.ix(), _Pos.iy(), rt.right - rt.left, rt.bottom - rt.top, SWP_NOZORDER);
}

