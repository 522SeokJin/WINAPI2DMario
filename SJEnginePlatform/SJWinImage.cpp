#include "SJWinImage.h"
#include <SJDebug.h>
#include "SJWindow.h"

// TransparentBlt �� �������� �Լ��� ���� ������ ������ �ִ� ���̺귯��
#pragma comment(lib, "msimg32.lib")

// Static Var
// Static Func

// member Var

SJWinImage::SJWinImage()
	: m_DC(0)
	, m_BitMapInfo()
	, m_BitMap(0)
	, m_OldBitMap(0)
	, TransColor(RGB(255, 0, 255))
{
	m_Blend.AlphaFormat = AC_SRC_ALPHA; // 0 �� �Ϲݺ�Ʈ��, AC_SRC_ALPHA �� 32��Ʈ ��Ʈ��
	m_Blend.BlendFlags = 0;
	m_Blend.BlendOp = AC_SRC_OVER;
	m_Blend.SourceConstantAlpha = 255;
}

SJWinImage::~SJWinImage()
{
	// �� �ڵ����� ���ְ� ���ϰ� �׷� �������� ����
	// os���� ���°� ������ ���� ó�����ּ���

	if (nullptr != m_DC)
	{
		// 
		// m_OldBitMap;

		DeleteObject(m_BitMap);

		DeleteObject(m_OldBitMap);

		DeleteDC(m_DC);
	}
}

// member Func


void SJWinImage::Create(const Scale& _ImageScale)
{
	if (true == _ImageScale.IsZero2D())
	{
		SJDebug::AssertMsg(L"if (true == _ImageScale.IsZero2D())");
	}

	m_BitMap = CreateCompatibleBitmap(SJWindow::GetWindowDC(), _ImageScale.ix(), _ImageScale.iy());

	m_DC = CreateCompatibleDC(nullptr);

	if (nullptr == m_DC)
	{
		SJDebug::AssertMsg(L"if (nullptr == m_DC)");
	}
	else
	{
		m_OldBitMap = (HBITMAP)SelectObject(m_DC, m_BitMap);
	}

	ImageSizeCheck();
}

void SJWinImage::Create(HDC _DC)
{
	if (nullptr == _DC)
	{
		SJDebug::AssertMsg(L"if (nullptr == _DC)");
	}

	m_DC = _DC;

	ImageSizeCheck();
}



void SJWinImage::ImageSizeCheck()
{
	// GetCurrentObject �������� Ư�� �ڵ鿡�� �ٸ� �ڵ��� ������ �༮
	// �翬�� �� Ÿ���� �ڵ��� ������ ���� ������ ���ü� ����.
	// DC�� ���ο� BITMAP������ ������ �־ ������� �ִ�. 

	// �Լ� ���ο� �ִ� OBJECT�� ����ü���� �ִµ�
	// �װ� ������ �Լ� ���ó� �ƹ��͵� �Ȱ����� ������
	// ���ü� �����.
	// DC���� ��Ʈ�� ���� ������ ���.
	// �̷��� BITMAP �� ���ü� �ְ� ���� �����ȿ� ũ�������� ����ִ�.
	// GetObjectW(CheckBitMap, sizeof(BitMapInfo), &BitMapInfo);

	HBITMAP CheckBitMap = (HBITMAP)GetCurrentObject(m_DC, OBJ_BITMAP);
	GetObjectW(CheckBitMap, sizeof(m_BitMapInfo), &m_BitMapInfo);

	m_Size.x = static_cast<float>(m_BitMapInfo.bmWidth);
	m_Size.y = static_cast<float>(m_BitMapInfo.bmHeight);
}

void SJWinImage::Load(const SJString& _LoadPath)
{
	m_BitMap = (HBITMAP)LoadImageW(nullptr,
		_LoadPath.c_str(),	// ���
		IMAGE_BITMAP,		// ��Ʈ����
		0,					// 0,0 ��ġ����
		0,
		LR_LOADFROMFILE);	// ���� �������

	if (nullptr == m_BitMap)
	{
		SJDebug::AssertMsg(L"if (nullptr == m_BitMap)");
	}

	m_DC = CreateCompatibleDC(nullptr);

	if (nullptr == m_DC)
	{
		SJDebug::AssertMsg(L"if (nullptr == m_DC)");
	}

	m_OldBitMap = (HBITMAP)SelectObject(m_DC, m_BitMap);

	ImageSizeCheck();
}

void SJWinImage::BitBlt(SJWinImage& _OtherImage)
{
	// _OtherImage�̹����� �����ϴ� �׸��� 
	// this�̹����� �״�� (������)�������ִ� �Լ�

	BitBlt({ 0, 0 }, _OtherImage);
}

void SJWinImage::BitBlt(float4 _Pos, SJWinImage& _OtherImage)
{
	::BitBlt(m_DC,// ���� �̹����� �����ض�
		_Pos.ix(), // ���� �̹����� X0��������
		_Pos.iy(), // ���� �̹����� Y0��������
		_OtherImage.m_BitMapInfo.bmWidth,  // �̹����� �ʺ��
		_OtherImage.m_BitMapInfo.bmHeight, // �̹����� ���̸�ŭ
		_OtherImage.m_DC,
		0, // ���� �̹����� X0����
		0, // ���� �̹����� Y0����
		SRCCOPY); // ��� �����ض�
}

void SJWinImage::BitBltCenter(float4 _Pos, SJWinImage& _OtherImage)
{
	::BitBlt(m_DC,// ���� �̹����� �����ض�
		_Pos.ix() - _OtherImage.m_Size.ihx(), // ���� �̹����� X0��������
		_Pos.iy() - _OtherImage.m_Size.ihy(), // ���� �̹����� Y0��������
		_OtherImage.m_BitMapInfo.bmWidth,  // �̹����� �ʺ��
		_OtherImage.m_BitMapInfo.bmHeight, // �̹����� ���̸�ŭ
		_OtherImage.m_DC,
		0, // ���� �̹����� X0����
		0, // ���� �̹����� Y0����
		SRCCOPY); // ��� �����ض�
}

void SJWinImage::TransparentBltCenter(const float4& _Pos, const float4& _Size, SJWinImage& _OtherImage, const float4& _CutPos, const float4& _CutSize)
{
	float4 CutSize = _CutSize;

	if (-1 == _CutSize.ix())
	{
		CutSize.x = static_cast<float>(_OtherImage.m_Size.x);
	}

	if (-1 == _CutSize.iy())
	{
		CutSize.y = static_cast<float>(_OtherImage.m_Size.y);
	}

	::TransparentBlt(m_DC,
		_Pos.ix() - _Size.ihx(), // ���� �̹����� �׸����� �ϴ� ��ġ�� x
		_Pos.iy() - _Size.ihy(), // ���� �̹����� �׸����� �ϴ� ��ġ�� y
		_Size.ix(), // �׸����� �ϴ� ������ x
		_Size.iy(), // �׸����� �ϴ� ������ y
		_OtherImage.m_DC,
		_CutPos.ix(),
		_CutPos.iy(),
		CutSize.ix(),
		CutSize.iy(),
		_OtherImage.TransColor);
}

void SJWinImage::TransparentBlt(const float4& _Pos, const float4& _Size, SJWinImage& _OtherImage, const float4& _CutPos, const float4& _CutSize)
{
	float4 CutSize = _CutSize;

	if (-1 == _CutSize.ix())
	{
		CutSize.x = static_cast<float>(_OtherImage.m_Size.x);
	}

	if (-1 == _CutSize.iy())
	{
		CutSize.y = static_cast<float>(_OtherImage.m_Size.y);
	}

	::TransparentBlt(m_DC,
		_Pos.ix(), // ���� �̹����� �׸����� �ϴ� ��ġ�� x
		_Pos.iy(), // ���� �̹����� �׸����� �ϴ� ��ġ�� y
		_Size.ix(), // �׸����� �ϴ� ������ x
		_Size.iy(), // �׸����� �ϴ� ������ y
		_OtherImage.m_DC,
		_CutPos.ix(),
		_CutPos.iy(),
		CutSize.ix(),
		CutSize.iy(),
		_OtherImage.TransColor);
}

void SJWinImage::ImageCut(int _X, int _Y)
{
	if (_X == 0 || _Y == 0)
	{
		SJDebug::AssertMsg("if (_X == 0 || _Y == 0)");
	}

	float4 ImageSize = float4{ m_Size.ix() / _X, m_Size.iy() / _Y };
	float4 CurPos = float4{ 0, 0 };

	for (int y = 0; y < _Y; y++)
	{
		for (int x = 0; x < _X; x++)
		{
			m_CutData.push_back({ CurPos, ImageSize });
			CurPos.x += ImageSize.x;
		}

		CurPos.x = 0;
		CurPos.y += ImageSize.y;
	}
}

const CutData& SJWinImage::GetCutData(int _Index)
{
	if (0 > _Index || m_CutData.size() <= _Index)
	{
		SJDebug::AssertMsg("if (0 > _Index || m_CutData.size() <= _Index)");
	}

	return m_CutData[_Index];
}

void SJWinImage::AlphaBltCenter(const float4& _Pos, const float4& _Size, SJWinImage& _OtherImage, const float4& _CutPos, const float4& _CutSize, BYTE _Alpha)
{
	m_Blend.SourceConstantAlpha = _Alpha;

	float4 CutSize = _CutSize;

	if (-1 == _CutSize.ix())
	{
		CutSize.x = static_cast<float>(_OtherImage.m_Size.x);
	}

	if (-1 == _CutSize.iy())
	{
		CutSize.y = static_cast<float>(_OtherImage.m_Size.y);
	}

	::AlphaBlend(m_DC,
		_Pos.ix() - _Size.ihx(), // ���� �̹����� �׸����� �ϴ� ��ġ�� x
		_Pos.iy() - _Size.ihy(), // ���� �̹����� �׸����� �ϴ� ��ġ�� y
		_Size.ix(), // �׸����� �ϴ� ������ x
		_Size.iy(), // �׸����� �ϴ� ������ y
		_OtherImage.m_DC,
		_CutPos.ix(),
		_CutPos.iy(),
		CutSize.ix(),
		CutSize.iy(),
		m_Blend);
}