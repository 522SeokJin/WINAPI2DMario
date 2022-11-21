#pragma once
#include <Windows.h>
#include <SJMath.h>
#include <SJString.h>
#include <vector>

// 분류 :
// 용도 : 
// 설명 : 

class CutData
{
public:
    float4 m_Pos;
    float4 m_Size;
};

class SJWinImage
{
private: // Static Var
public: // Static Func
private: // member Var
    HDC             m_DC;

    HBITMAP         m_BitMap;
    HBITMAP         m_OldBitMap;
    BITMAP          m_BitMapInfo;

    float4          m_Size;
    int             TransColor;
    BLENDFUNCTION   m_Blend;

public:
    void SetTransColor(int _Color)
    {
        TransColor = _Color;
    }

    unsigned long GetPixelColor(int _X, int _Y)
    {
        return GetPixel(m_DC, _X, _Y);
    }

private: // 잘려진 이미지의 집합
    std::vector<CutData> m_CutData;

public:
    int GetCutSize()
    {
        return (int)m_CutData.size();
    }

    const CutData& GetCutData(int _Index);
    void ImageCut(int _X, int _Y);

public:
    HDC ImageDC()
    {
        return m_DC;
    }
    float4 GetImageSize()
    {
        return m_Size;
    }

public: // constructer destructer
	SJWinImage();
	~SJWinImage();

public: // delete constructer 
    SJWinImage(const SJWinImage& _Other) = delete;
    SJWinImage(const SJWinImage&& _Other) = delete;

public: // delete operator
    SJWinImage& operator=(const SJWinImage& _Other) = delete;
    SJWinImage& operator=(const SJWinImage&& _Other) = delete;

private:
    void ImageSizeCheck();

public: // member Func
    void Create(const Scale& _ImageScale);
    
    // 이미 존재하는 dc를 받아서 WinImage로 만들어주는 함수
    void Create(HDC _DC);
    void Load(const SJString& _LoadPath);

public:
    // 크기조절 안됨, 투명 안됨, 일부 복사는 되지만 세세하게 되지는 않는다.
    void BitBlt(SJWinImage& _OtherImage);
    void BitBlt(float4 _Pos, SJWinImage& _OtherImage);
    void BitBltCenter(float4 _Pos, SJWinImage& _OtherImage);

public:
    // 크기조절 됨, 특정 색깔 제거가능, 일부 복사 가능
    void TransparentBltCenter(const float4& _Pos, const float4& _Size, SJWinImage& _OtherImage, const float4& _CutPos, const float4& _CutSize);
    void TransparentBlt(const float4& _Pos, const float4& _Size, SJWinImage& _OtherImage, const float4& _CutPos, const float4& _CutSize);

    void AlphaBltCenter(const float4& _Pos, const float4& _Size, SJWinImage& _OtherImage, const float4& _CutPos, const float4& _CutSize, BYTE _Alpha);

};

