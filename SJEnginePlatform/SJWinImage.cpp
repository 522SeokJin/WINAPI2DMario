#include "SJWinImage.h"
#include <SJDebug.h>
#include "SJWindow.h"

// TransparentBlt 및 여러가지 함수에 대한 내용을 가지고 있는 라이브러리
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
	m_Blend.AlphaFormat = AC_SRC_ALPHA; // 0 은 일반비트맵, AC_SRC_ALPHA 는 32비트 비트맵
	m_Blend.BlendFlags = 0;
	m_Blend.BlendOp = AC_SRC_OVER;
	m_Blend.SourceConstantAlpha = 255;
}

SJWinImage::~SJWinImage()
{
	// 뭐 자동으로 해주건 뭐하건 그런 생각하지 말고
	// os에게 얻어온건 무조건 직접 처리해주세요

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
	// GetCurrentObject 윈도우의 특정 핸들에서 다른 핸들을 빼오는 녀석
	// 당연히 그 타입의 핸들을 가지고 있지 않으면 빼올수 없다.
	// DC가 내부에 BITMAP정보를 가지고 있어서 빼울수가 있다. 

	// 함수 내부에 있는 OBJECT의 정보체들이 있는데
	// 그걸 빼오는 함수 역시나 아무것도 안가지고 있으면
	// 빼올수 없어요.
	// DC에서 비트맵 정보 빼오는 방법.
	// 이러면 BITMAP 를 빼올수 있고 빼온 정보안에 크기정보도 들어있다.
	// GetObjectW(CheckBitMap, sizeof(BitMapInfo), &BitMapInfo);

	HBITMAP CheckBitMap = (HBITMAP)GetCurrentObject(m_DC, OBJ_BITMAP);
	GetObjectW(CheckBitMap, sizeof(m_BitMapInfo), &m_BitMapInfo);

	m_Size.x = static_cast<float>(m_BitMapInfo.bmWidth);
	m_Size.y = static_cast<float>(m_BitMapInfo.bmHeight);
}

void SJWinImage::Load(const SJString& _LoadPath)
{
	m_BitMap = (HBITMAP)LoadImageW(nullptr,
		_LoadPath.c_str(),	// 경로
		IMAGE_BITMAP,		// 비트맵을
		0,					// 0,0 위치부터
		0,
		LR_LOADFROMFILE);	// 파일 기반으로

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
	// _OtherImage이미지에 존재하는 그림을 
	// this이미지에 그대로 (빠르게)복사해주는 함수

	BitBlt({ 0, 0 }, _OtherImage);
}

void SJWinImage::BitBlt(float4 _Pos, SJWinImage& _OtherImage)
{
	::BitBlt(m_DC,// 나의 이미지에 복사해라
		_Pos.ix(), // 나의 이미지의 X0에서부터
		_Pos.iy(), // 나의 이미지의 Y0에서부터
		_OtherImage.m_BitMapInfo.bmWidth,  // 이미지의 너비와
		_OtherImage.m_BitMapInfo.bmHeight, // 이미지의 높이만큼
		_OtherImage.m_DC,
		0, // 위의 이미지의 X0부터
		0, // 위의 이미지의 Y0부터
		SRCCOPY); // 고속 복사해라
}

void SJWinImage::BitBltCenter(float4 _Pos, SJWinImage& _OtherImage)
{
	::BitBlt(m_DC,// 나의 이미지에 복사해라
		_Pos.ix() - _OtherImage.m_Size.ihx(), // 나의 이미지의 X0에서부터
		_Pos.iy() - _OtherImage.m_Size.ihy(), // 나의 이미지의 Y0에서부터
		_OtherImage.m_BitMapInfo.bmWidth,  // 이미지의 너비와
		_OtherImage.m_BitMapInfo.bmHeight, // 이미지의 높이만큼
		_OtherImage.m_DC,
		0, // 위의 이미지의 X0부터
		0, // 위의 이미지의 Y0부터
		SRCCOPY); // 고속 복사해라
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
		_Pos.ix() - _Size.ihx(), // 위의 이미지에 그리려고 하는 위치의 x
		_Pos.iy() - _Size.ihy(), // 위의 이미지에 그리려고 하는 위치의 y
		_Size.ix(), // 그리려고 하는 사이즈 x
		_Size.iy(), // 그리려고 하는 사이즈 y
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
		_Pos.ix(), // 위의 이미지에 그리려고 하는 위치의 x
		_Pos.iy(), // 위의 이미지에 그리려고 하는 위치의 y
		_Size.ix(), // 그리려고 하는 사이즈 x
		_Size.iy(), // 그리려고 하는 사이즈 y
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
		_Pos.ix() - _Size.ihx(), // 위의 이미지에 그리려고 하는 위치의 x
		_Pos.iy() - _Size.ihy(), // 위의 이미지에 그리려고 하는 위치의 y
		_Size.ix(), // 그리려고 하는 사이즈 x
		_Size.iy(), // 그리려고 하는 사이즈 y
		_OtherImage.m_DC,
		_CutPos.ix(),
		_CutPos.iy(),
		CutSize.ix(),
		CutSize.iy(),
		m_Blend);
}