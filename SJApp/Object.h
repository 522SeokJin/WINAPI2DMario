#pragma once
#include <SJActor.h>
#include <SJWindow.h>

// 분류 :
// 용도 : 
// 설명 : 

enum class eDIR
{
    LEFT,
    RIGHT,
};

enum class PIXELCHECK
{
    LEFT,
    LEFT_TOP,
    LEFT_BOTTOM,
    RIGHT,
    RIGHT_TOP,
    RIGHT_BOTTOM,
    TOP,
    BOTTOM,
    MAX,
};

enum class PIXELCOLOR
{
    FREE = RGB(255, 255, 255),
    GROUND = RGB(0, 255, 0),
    FLOATING = RGB(0, 0, 255),
    DEATH = RGB(255, 0, 0),
    OUT_OF_IMAGE = -1,
};

enum class COLLISIONDATA
{
    NORMAL,
    TERRAIN,
    SIDE,
    TOP,
    BOTTOM,
    EVENT,
};

class SJRendererAnimation;

class Object : public SJActor
{
public: // Static Var
    static float    m_Gravity;

public: // Static Func
    static void SetGravity(float _Value)
    {
        m_Gravity = _Value;
    }
public: // member Var
    float4                  m_PixelCheck[(int)PIXELCHECK::MAX];

public:
    float4                  m_Move;

    eDIR                    m_Dir;
    eDIR                    m_PrevDir;
    float4                  m_fDir;

    SJRendererAnimation*    m_AniRenderer;

    SJString                m_CurAniName;

    bool                    m_bDelay;
    float                   m_fDelay;

public:
    void CollisionView(SJCollision* _Data);
    void PixelView();
    
    void SetPixelPos(float4 _PivotPos = float4{});

    bool PixelCheck(float4 _PixelPos, float4 _MovePos, int _CheckColor);

    bool PixelCheckAllLeft(float4 _MovePos, int _CheckColor);
    bool PixelCheckAllRight(float4 _MovePos, int _CheckColor);
    bool PixelCheckAllTop(float4 _MovePos, int _CheckColor);
    bool PixelCheckAllBottom(float4 _MovePos, int _CheckColor);

    bool PixelCheckAllLeft(int _CheckColor);
    bool PixelCheckAllRight(int _CheckColor);
    bool PixelCheckAllTop(int _CheckColor);
    bool PixelCheckAllBottom(int _CheckColor);

    bool PixelCheck(float4 _PixelPos, int _CheckColor);

    void SetDir(eDIR _Dir);

    virtual void ChangeAnimation(const SJString& _Name);

    void SetDelay();

public: // constructer destructer
	Object();
	~Object();

public: // delete constructer 
    Object(const Object& _Other) = delete;
    Object(const Object&& _Other) = delete;

public: // delete operator
    Object& operator=(const Object& _Other) = delete;
    Object& operator=(const Object&& _Other) = delete;

public: // member Func
};

