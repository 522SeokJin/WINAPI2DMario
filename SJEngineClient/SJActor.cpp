#include "SJActor.h"
#include "SJRenderer.h"
#include "SJCollision.h"

// Static Var

// Static Func

// member Var

SJActor::SJActor()
	: m_Pos(0.f)
	, m_Size(0.f)
	, m_CamAffect(true)
	, m_Scene(nullptr)
{

}

SJActor::~SJActor()
{
	{
		std::list<SJRenderer*>::iterator iter = m_Renderer.begin();

		for (; iter != m_Renderer.end(); ++iter)
		{
			delete* iter;
			*iter = nullptr;
		}

		m_Renderer.clear();
	}

	{
		std::list<SJCollision*>::iterator iter = m_Collision.begin();

		for (; iter != m_Collision.end(); ++iter)
		{
			delete* iter;
			*iter = nullptr;
		}

		m_Collision.clear();
	}
}

// member Func

void SJActor::DeathTask()
{
	{
		std::list<SJRenderer*>::iterator iter = m_Renderer.begin();

		for (; iter != m_Renderer.end(); ++iter)
		{
			(*iter)->DeathTask();
		}
	}

	{
		std::list<SJCollision*>::iterator iter = m_Collision.begin();

		for (; iter != m_Collision.end(); ++iter)
		{
			(*iter)->DeathTask();
		}
	}
}

void SJActor::Release()
{
	// Actor�� �츰ä�� �������� �浹ü�� Death�Ҷ� üũ�ϴ� �Լ�
	{
		std::list<SJRenderer*>::iterator iter = m_Renderer.begin();

		for (; iter != m_Renderer.end(); )
		{
			if (false == (*iter)->IsDeath())
			{
				++iter;
				continue;
			}
			(*iter)->DeathTask();
			delete (*iter);
			iter = m_Renderer.erase(iter);
		}
	}

	{
		std::list<SJCollision*>::iterator iter = m_Collision.begin();

		for (; iter != m_Collision.end(); )
		{
			if (false == (*iter)->IsDeath())
			{
				++iter;
				continue;
			}
			(*iter)->DeathTask();
			delete (*iter);
			iter = m_Collision.erase(iter);
		}
	}
}