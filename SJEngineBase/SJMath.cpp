#include "SJMath.h"

// Static Var
const float4 float4::LEFT = { -1, 0 };
const float4 float4::RIGHT = { 1, 0 };
const float4 float4::UP = { 0 , -1 };
const float4 float4::DOWN = { 0 , 1 };
const float4 float4::ZERO = { 0, 0 };
const float4 float4::X = { 1, 0 };
const float4 float4::Y = { 0, 1 };

// 알아서 소숫점 한계치까지 짤립니다.
float SJMath::FPI = 3.141592653589793238462643383279502884197169399375105820974944f;
double SJMath::DPI = 3.141592653589793238462643383279502884197169399375105820974944;

// 180
// / 180 * 3.14
// 3.14 => 180
// 3.14 => 180

// 라디안은 180 == 3.14
float SJMath::FD2R = FPI / 180;
float SJMath::FR2D = 180 / FPI;

// Static Func

// member Var

SJMath::SJMath()
{

}

SJMath::~SJMath()
{

}

// member Func

Collision2DCheck::StaticInst Collision2DCheck::Inst;

bool (*Collision2DCheck::ColFunc[(int)COLTYPE::MAX][(int)COLTYPE::MAX])(const Col2DData&, const Col2DData&);


void Collision2DCheck::Init()
{
	ColFunc[(int)COLTYPE::RECT][(int)COLTYPE::RECT] = RectToRect;
	ColFunc[(int)COLTYPE::RECT][(int)COLTYPE::CIRCLE] = RectToCirCle;
	ColFunc[(int)COLTYPE::RECT][(int)COLTYPE::POINT] = RectToPoint;

	ColFunc[(int)COLTYPE::CIRCLE][(int)COLTYPE::RECT] = CircleToRect;
	ColFunc[(int)COLTYPE::CIRCLE][(int)COLTYPE::CIRCLE] = CircleToCirCle;
	ColFunc[(int)COLTYPE::CIRCLE][(int)COLTYPE::POINT] = CircleToPoint;

	ColFunc[(int)COLTYPE::POINT][(int)COLTYPE::RECT] = PointToRect;
	ColFunc[(int)COLTYPE::POINT][(int)COLTYPE::CIRCLE] = PointToCirCle;
	ColFunc[(int)COLTYPE::POINT][(int)COLTYPE::POINT] = PointToPoint;

}

bool Collision2DCheck::RectToRect(const Col2DData& _Left, const Col2DData& _Right)
{
	
	if (_Left.Left() < _Right.Right() &&
		_Left.Top() < _Right.Bottom() &&
		_Left.Right() > _Right.Left() &&
		_Left.Bottom() > _Right.Top())
	{
		return true;
	}

	return false;

}


bool Collision2DCheck::RectToCirCle(const Col2DData& _Left, const Col2DData& _Right) { return true; }
bool Collision2DCheck::RectToPoint(const Col2DData& _Left, const Col2DData& _Right) { return true; }

bool Collision2DCheck::CircleToRect(const Col2DData& _Left, const Col2DData& _Right) { return true; }
bool Collision2DCheck::CircleToCirCle(const Col2DData& _Left, const Col2DData& _Right) { return true; }
bool Collision2DCheck::CircleToPoint(const Col2DData& _Left, const Col2DData& _Right) { return true; }

bool Collision2DCheck::PointToRect(const Col2DData& _Left, const Col2DData& _Right) { return true; }
bool Collision2DCheck::PointToCirCle(const Col2DData& _Left, const Col2DData& _Right) { return true; }
bool Collision2DCheck::PointToPoint(const Col2DData& _Left, const Col2DData& _Right) { return true; }