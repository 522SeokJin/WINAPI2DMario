#pragma once
#include <math.h>

// 분류 :
// 용도 : 
// 설명 : 

class float4;

typedef float4 Vector;
typedef float4 Position;
typedef float4 Scale;
typedef float4 FRect;
typedef float4 Color;

class SJMath
{
public: // Static Var
    static float        FPI;
    static double       DPI;

    static float        FD2R;
    static float        FR2D;

public: // Static Func
private: // member Var

public: // constructer destructer
	SJMath();
	~SJMath();

public: // delete constructer 
    SJMath(const SJMath& _Other) = delete;
    SJMath(const SJMath&& _Other) = delete;

public: // delete operator
    SJMath& operator=(const SJMath& _Other) = delete;
    SJMath& operator=(const SJMath&& _Other) = delete;

public: // member Func
};

class float4
{
public:
    static const float4 LEFT;
    static const float4 RIGHT;
    static const float4 UP;
    static const float4 DOWN;
    static const float4 ZERO;
    static const float4 X;
    static const float4 Y;
    // 4차원을 나타내는 수, API에서는 x, y  2차원만 다룸

public:
    static float4 AngleToDir2DDeg(float _Deg)
    {
        return AngleToDir2DRad(_Deg * SJMath::FD2R);
    }

    static float4 AngleToDir2DRad(float _Rad)
    {
        // sinf => 높이 / 빗변
        // cosf => 밑변 / 빗변
        // tan  => 높이 / 밑변

        float4 Return;

        // 빗변의 길이가 1짜리인 직각 삼각형의?

        Return.x = cosf(_Rad); // 밑변 x
        Return.y = sinf(_Rad); // 높이 y

        return Return;
    }

    // 어떤 점을 넣어주면 0,0 기준으로 회전시켜주는 녀석입니다.
    static float4 AngleTo2DDeg(const float4& _Ori, float _Deg)
    {
        return AngleTo2DRad(_Ori, _Deg * SJMath::FD2R);
    }

    static float4 AngleTo2DRad(const float4& _Ori, float _Rad)
    {
        float4 Return;

        Return.x = (cosf(_Rad) * _Ori.x) - (sinf(_Rad) * _Ori.y);
        Return.y = (sinf(_Rad) * _Ori.x) + (cosf(_Rad) * _Ori.y);
        return Return;
    }

    static float Len3D(const float4& _Value)
    {
        return sqrtf((_Value.x * _Value.x) + (_Value.y * _Value.y) + (_Value.z * _Value.z));
    }

    static float Len2D(const float4& _Value)
    {
        return sqrtf((_Value.x * _Value.x) + (_Value.y * _Value.y));
    }

    static float4 Normalize2D(const float4& _Value)
    {
        float4 ReturnValue = _Value;
        float Len = Len2D(_Value);

        ReturnValue.x = _Value.x / Len;
        ReturnValue.y = _Value.y / Len;
        ReturnValue.z = 0.0f;

        return ReturnValue;

    }

public:
    static float4 Lerp2DMax(float4 _Start, float4 _End, float _Ratio)
    {
        if (0 >= _Ratio)
        {
            _Ratio = 0.0f;
        }

        if (1.0f <= _Ratio)
        {
            _Ratio = 1.0f;
        }

        return Lerp2D(_Start, _End, _Ratio);
    }

    static float4 Lerp2D(float4 _Start, float4 _End, float _Ratio)
    {
        float4 ReturnValue;
        // p1 _Start
        // p2 _End
        // d1 _Ratio
        ReturnValue.x = (1 - _Ratio) * _Start.x + _Ratio * _End.x;
        ReturnValue.y = (1 - _Ratio) * _Start.y + _Ratio * _End.y;

        return ReturnValue;
    }

public:
    union
    {
        struct
        {
            float x;
            float y;
            float z;
            float w;
        };

        struct
        {
            float r;
            float g;
            float b;
            float a;
        };
    };

public:
    float4 operator * (float _Other)
    {
        return float4(x * _Other, y * _Other, z * _Other, w * _Other);
    }

public:
    float4() : x(0.0f), y(0.0f), z(0.0f), w(1.0f)
    {
    }

    float4(float _Value)
        : x(_Value), y(_Value), z(_Value), w(_Value)
    {
    }

    float4(float _x, float _y)
        : x(_x), y(_y), z(0.0f), w(1.0f)
    {
    }

    float4(
        float _x,
        float _y,
        float _z
    ) : x(_x), y(_y), z(_z), w(1.0f)
    {
    }

    float4(
        float _x,
        float _y,
        float _z,
        float _w
    ) : x(_x), y(_y), z(_z), w(_w)
    {
    }

    float4(
        int _value
    ) : x(static_cast<float>(_value)), y(static_cast<float>(_value)), z(static_cast<float>(_value)), w(static_cast<float>(_value))
    {
    }

    float4(
        int _x,
        int _y
    ) : x(static_cast<float>(_x)), y(static_cast<float>(_y)), z(0.0f), w(1.0f)
    {
    }

    float4(
        int _x,
        int _y,
        int _z
    ) : x(static_cast<float>(_x)), y(static_cast<float>(_y)), z(static_cast<float>(_z)), w(1.0f)
    {
    }

    float4(
        int _x,
        int _y,
        int _z,
        int _w
    ) : x(static_cast<float>(_x)), y(static_cast<float>(_y)), z(static_cast<float>(_z)), w(static_cast<float>(_w))
    {
    }

public:
    // 속성중 하나라도 0이 있으면
    // 리턴 true
    // const MyClass;
    // 가 있다면
    // MyClass의 함수중 const가 뒤에붙어있는 함수만 호출할수 있고
    // 핵심은 this가 const MyClass* const가 되어야 하기 때문이다.

    bool IsZero2D() const
    {
        return x == 0 || y == 0;
    }

    bool IsZero() const
    {
        // this가 const니까.
        return x == 0 || y == 0 || z == 0;
    }

public:
    int ix() const
    {
        return static_cast<int>(x);
    }
    int iy()const
    {
        return static_cast<int>(y);
    }
    int iz() const
    {
        return static_cast<int>(z);
    }
    int iw() const
    {
        return static_cast<int>(w);
    }

    int ihx() const
    {
        return static_cast<int>(x * 0.5f);
    }
    int ihy()const
    {
        return static_cast<int>(y * 0.5f);
    }
    int ihz() const
    {
        return static_cast<int>(z * 0.5f);
    }
    int ihw() const
    {
        return static_cast<int>(w * 0.5f);
    }

    float hx()const
    {
        return x * 0.5f;
    }
    float hy()const
    {
        return y * 0.5f;
    }
    float hz()const
    {
        return z * 0.5f;
    }
    float hw()const
    {
        return w * 0.5f;
    }

    float4 hfloat4()const
    {
        return { hx(), hy() };
    }

    float4 operator+(const float4& _Other)
    {
        float4 ReturnVector;
        ReturnVector.x = x + _Other.x;
        ReturnVector.y = y + _Other.y;
        ReturnVector.z = z + _Other.z;
        ReturnVector.w = w + _Other.w;
        return ReturnVector;
    }

    float4 operator*(const float& _Value) const
    {
        float4 ReturnVector;
        ReturnVector.x = x * _Value;
        ReturnVector.y = y * _Value;
        ReturnVector.z = z * _Value;
        ReturnVector.w = w * _Value;
        return ReturnVector;
    }

    float4 operator-(const float4& _Other) const
    {
        float4 ReturnVector;
        ReturnVector.x = x - _Other.x;
        ReturnVector.y = y - _Other.y;
        ReturnVector.z = z - _Other.z;
        ReturnVector.w = w - _Other.w;
        return ReturnVector;
    }

    float4& operator+=(const float4& _Other)
    {
        x += _Other.x;
        y += _Other.y;
        z += _Other.z;
        w += _Other.w;
        return *this;
    }

    float4& operator-=(const float4& _Other)
    {
        x -= _Other.x;
        y -= _Other.y;
        z -= _Other.z;
        w -= _Other.w;
        return *this;
    }

    float4& operator*=(const float4& _Other)
    {
        x *= _Other.x;
        y *= _Other.y;
        z *= _Other.z;
        w *= _Other.w;
        return *this;
    }

    bool operator==(const float4& _Other) const
    {
        if (x == _Other.x &&
            y == _Other.y &&
            z == _Other.z &&
            w == _Other.w)
        {
            return true;
        }
        
        return false;
    }

    float GetLen()
    {
        return Len2D(*this);
    }

    float4 GetNormalize2D() const
    {
        return Normalize2D(*this);
    }

    void Normalize()
    {
        *this = Normalize2D(*this);
    }
};

//////////////////////////////////////////////      2D Collision

enum class COLTYPE
{
    RECT,
    CIRCLE,
    POINT,
    MAX,
};

class Col2DData
{
public:
    float4 Pos;
    float4 Size;

public:
    float Left() const
    {
        return Pos.x - Size.hx();
    }
    float Right() const
    {
        return Pos.x + Size.hx();
    }
    float Top() const
    {
        return Pos.y - Size.hy();
    }
    float Bottom() const
    {
        return Pos.y + Size.hy();
    }

    int iLeft() const
    {
        return static_cast<int>(Left());
    }
    int iRight() const
    {
        return static_cast<int>(Right());
    }
    int iTop() const
    {
        return static_cast<int>(Top());
    }
    int iBottom() const
    {
        return static_cast<int>(Bottom());
    }
    
    float4 LeftPoint() const
    {
        return { Left(), Pos.y };
    }
    float4 RightPoint() const
    {
        return { Right(), Pos.y };
    }
    float4 TopPoint() const
    {
        return { Pos.x, Top() };
    }
    float4 BottomPoint() const
    {
        return { Pos.x, Bottom() };
    }

};

class Collision2DCheck
{
public:
    static bool (*ColFunc[(int)COLTYPE::MAX][(int)COLTYPE::MAX])(const Col2DData&, const Col2DData&);

    // Init 을 생성자에서 자동으로 실행한다.
    // 실행순서를 제어할 수 없다.
public:
    class StaticInst
    {
        friend Collision2DCheck;
    private:
        StaticInst()
        {
            Collision2DCheck::Init();
        }

        ~StaticInst()
        {

        }
    };

    friend StaticInst;
    static StaticInst Inst;

private:
    static void Init();

public:
    static bool RectToRect              (const Col2DData& _Left, const Col2DData& _Right);
    static bool RectToCirCle            (const Col2DData& _Left, const Col2DData& _Right);
    static bool RectToPoint             (const Col2DData& _Left, const Col2DData& _Right);

    static bool CircleToRect            (const Col2DData& _Left, const Col2DData& _Right);
    static bool CircleToCirCle          (const Col2DData& _Left, const Col2DData& _Right);
    static bool CircleToPoint           (const Col2DData& _Left, const Col2DData& _Right);

    static bool PointToRect             (const Col2DData& _Left, const Col2DData& _Right);
    static bool PointToCirCle           (const Col2DData& _Left, const Col2DData& _Right);
    static bool PointToPoint            (const Col2DData& _Left, const Col2DData& _Right);

private:
    //virtual ~Collision2DCheck();
};