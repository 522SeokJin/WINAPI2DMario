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
	// ������ �̺�Ʈ ó�� �Լ�
	switch (_EventType)
	{
	case WM_KILLFOCUS:
	{
		// ų��Ŀ�� ȭ�� �ٱ������� ��Ʈ���� ��������
		break;
	}
	case WM_DESTROY:
	{
		m_bWindowProgress = false;
		break;
	}
	default:
		// �⺻ �޼����� ó�����ִ� �Լ�
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
		// �����찡 �䱸�ϴ� ������������ ��
		// ���⿡�ٰ� ���� ä���� �־��ָ�
		// �̷� �����츦 ����� �ִ��� Os�� �츮���� �˷��ݴϴ�.
		WNDCLASSEXW WCEX;

		WCEX.cbSize = sizeof(WNDCLASSEXW);
		// ������ ũ�Ⱑ �ٲ�� ���� ���� ���� �ٲ�� ȭ���� �����ش޶�.
		WCEX.style = CS_HREDRAW | CS_VREDRAW;

		// Ŭ������ ���� �����
		// �� Ŭ������ �����Ҷ� ���� ���� �Լ��� ��� �������ַ��� ����� ��찡 �ִµ�
		// �̷��� ����� callback�̶�� �ϰ�
		// ��ǥ���� ���� UI(BUTTON) �̴�.
		WCEX.lpfnWndProc = &SJWindow::WINDOWEVENT;

		// ���ɾ���� 0�־��ָ� �˴ϴ�.
		WCEX.cbClsExtra = 0;
		WCEX.cbWndExtra = 0;

		// �����츦 �������ϴ� ���α׷��� �������� �˷��ش�.
		WCEX.hInstance = _ProcessHandle;

		// ������ ������ �ڵ� (���� ����� ���µ� �������� ���ɵ� �����ϴ�.)
		WCEX.hIcon = nullptr;
		WCEX.hIconSm = nullptr;

		// ������ Ŀ�� �ڵ� (���� ����Ŵϱ��.)
		WCEX.hCursor = nullptr;

		// �⺻ ������ ��׶��� �� �ڵ�
		// ��� ������
		WCEX.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

		// �޴�
		WCEX.lpszMenuName = nullptr;

		// C++�� �����ڸ�
		// Ŭ������ ���� ���� �ǰ���?
		// Ŭ������ �̸��̾�.
		// 
		// �̷� ������������ �̸��� 
		// XXX��� �Ҳ� ���߿� XXX�� ������ �ϸ�
		// ���� ���� ������ ���·� ����������.
		WCEX.lpszClassName = L"DEFWINDOW";

		// ������ ���¸� ����ϴ� �Լ��� �����ϸ�
		// 0�ϰſ���
		if (0 == RegisterClassExW(&WCEX))
		{
			unsigned int ErrorCode = GetLastError();

			SJDebug::AssertMsg(L"if (0 == RegisterClassExW(&WCEX))");
		}
	}

	// ���� �� �������� �����츦 ����޶�� �ϸ� �˴ϴ�.
	{
		//WS_OVERLAPPEDWINDOW (WS_OVERLAPPED     | \
		//                     WS_CAPTION        | \
		//					   WS_SYSMENU        | \
		//		               WS_THICKFRAME     | \
		//		               WS_MINIMIZEBOX    | \
		//		               WS_MAXIMIZEBOX)

		// WS_CAPTION ������ �����ϰ�
		// WS_SYSMENU �޴��� �����ϰ�
		// WS_THICKFRAME ���� �ܰ����� �ְ�
		// WS_MINIMIZEBOX �ּ�ȭ ��ư�� �ְ�
		// WS_MAXIMIZEBOX �ִ�ȭ ��ư�� �ִ�
		// WS_OVERLAPPED �ٸ� �������������ų� �Ʒ��� �ü� �ִ�
		// �����츦 ������ּ���

		// ������� �������� ���մϴ�.
		// L"DEFWINDOW" ����� �����츦 ������ּ���.

		// Ȥ�ó� ���� ����� �θ� �����찡 �ִ�?

		// �����Ҷ� 8����Ʈ �־��ټ� �ִµ�.
		m_WindowHWnd = CreateWindowW(L"DEFWINDOW", _Name.c_str(), WS_OVERLAPPEDWINDOW, _Pos.ix(), _Pos.iy(), _Size.ix(), _Size.iy(), nullptr, nullptr, _ProcessHandle, 0);

		if (nullptr == m_WindowHWnd)
		{
			SJDebug::AssertMsg(L"if (nullptr == m_WindowHWnd)");
			return;
		}

		// �������� ���̴� ���¸� �������ִ� �Լ�
		// ���� �̾߱��ߴ����
		// ���ϱ�?
		ShowWindow(m_WindowHWnd, SW_SHOW);

		SetSizeAndPos(_Pos, _Size);
		// �����츦 �ѹ� ������ �ּ���.
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

	// &rt ���� ���� rect�� ����ü
	// WS_OVERLAPPEDWINDOW �� �������� ����
	// false �޴��� �ִ��� ������.
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);

	// �������� ũ��� ��ġ�� ���ÿ� �ٲܼ� �ִ� �Լ��Դϴ�.

	// OS�� �� WINDOW�� �����Ҽ� �ִ� HANDLE�� �츮���� ���.
	// �츮�� ��û�Ҷ� 
	// SWP_NOZORDER ���� �ְ��� ���� ��Ծ����.
	// SWP_NOMOVE �������� �����Ѵٴ� ���ڿ��׿�.
	//  nullptr ���� ��.
	SetWindowPos(m_WindowHWnd, HWND_BOTTOM, _Pos.ix(), _Pos.iy(), rt.right - rt.left, rt.bottom - rt.top, SWP_NOZORDER);
}

