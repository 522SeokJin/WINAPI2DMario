#include "SJObjectBase.h"

// Static Var
// Static Func

// member Var

SJObjectBase::SJObjectBase()
	: m_IsOn(true)
	, m_IsDeath(false)
	, m_Parent(nullptr)
	, m_IsOnTask(false)
	, m_IsOffTask(false)
{

}

SJObjectBase::~SJObjectBase()
{
	DeathTask();
}

// member Func