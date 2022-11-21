#include "SJScene.h"
#include "SJActor.h"
#include <SJWindow.h>
#include "SJRenderer.h"
#include "SJCollision.h"

// Static Var
bool SJScene::m_bDebugRender = false;
// Static Func

// member Var

SJScene::SJScene()
	: m_CurScene(nullptr)
{

}

SJScene::~SJScene()
{
	std::list<SJActor*>::iterator iter = m_Actors.begin();

	for (; iter != m_Actors.end(); ++iter)
	{
		delete *iter;
		*iter = nullptr;
	}
}

// member Func

void SJScene::Progress()
{
	CollisionProcess();

	SceneUpdate();

	{
		std::list<SJActor*>::iterator iter = m_Actors.begin();

		for (; iter != m_Actors.end(); ++iter)
		{
			if (false == (*iter)->IsOn())
			{
				continue;
			}

			(*iter)->Update();
		}
	}

	Render();

	if(true == m_bDebugRender)
	{
		std::list<SJActor*>::iterator iter = m_Actors.begin();

		for (; iter != m_Actors.end(); ++iter)
		{
			if (false == (*iter)->IsOn())
			{
				continue;
			}

			(*iter)->DebugRender();
		}

		SceneDebugRender();
	}

	SJWindow::BackBufferCopy();

	// 모든 로직이 돈 후에 삭제를 한다.
	OnOffCheck();
	Release();
}

///////////////////////////////////////////////////////////////////////////////			렌더링

void SJScene::PushRenderer(SJRenderer* _Renderer)
{
	if (m_RendererLists.end() == m_RendererLists.find(_Renderer->GetOrder()))
	{
		m_RendererLists.insert(std::map<int, std::list<SJRenderer*>>::value_type(_Renderer->GetOrder(), std::list<SJRenderer*>()));
	}

	m_RendererLists[_Renderer->GetOrder()].push_back(_Renderer);
}

void SJScene::Render()
{
	std::map<int, std::list<SJRenderer*>>::iterator Layeriter = m_RendererLists.begin();

	for (; Layeriter != m_RendererLists.end(); ++Layeriter)
	{
		std::list<SJRenderer*>& RenderLayer = Layeriter->second;

		std::list<SJRenderer*>::iterator Renderiter = RenderLayer.begin();

		for (; Renderiter != RenderLayer.end(); ++ Renderiter)
		{
			if (false == (*Renderiter)->IsOn())
			{
				continue;
			}
			(*Renderiter)->Render();
		}
	}
}

///////////////////////////////////////////////////////////////////////////////			충돌체

void SJScene::PushCollision(SJCollision* _Collision)
{
	if (m_CollisionLists.end() == m_CollisionLists.find(_Collision->GetOrder()))
	{
		// 이렇게도 만들수 있다.
		// m_RendererLists[_Renderer->GetOrder()];
		m_CollisionLists.insert(std::map<int, std::list<SJCollision*>>::value_type(_Collision->GetOrder(), std::list<SJCollision*>()));
	}

	m_CollisionLists[_Collision->GetOrder()].push_back(_Collision);
}

void SJScene::CollisionProcess()
{
	// 모든 충돌체가 자기 위치를 수정하고
	{
		std::map<int, std::list<SJCollision*>>::iterator iter = m_CollisionLists.begin();

		for (; iter != m_CollisionLists.end(); ++iter)
		{
			std::list<SJCollision*>::iterator iterCol = iter->second.begin();

			for (; iterCol != iter->second.end(); ++iterCol)
			{
				if (false == (*iterCol)->IsOn())
				{
					continue;
				}
				(*iterCol)->CollisionDataUpdate();
			}
		}
	}

	// 충돌에 들어간다.

	std::map<int, std::set<int>>::iterator LeftGroupIter = m_LinkCollisionGroup.begin();

	for (; LeftGroupIter != m_LinkCollisionGroup.end(); ++LeftGroupIter)
	{
		std::set<int>::iterator RightGroupIter = LeftGroupIter->second.begin();

		for (; RightGroupIter != LeftGroupIter->second.end(); ++RightGroupIter)
		{
			int LeftGroupIndex = LeftGroupIter->first;
			int RightGroupIndex = *RightGroupIter;

			// 각 그룹 간의 충돌을 체크한다

			if (LeftGroupIndex != RightGroupIndex)
			{
				CollisionGroupOtherCheck(LeftGroupIndex, RightGroupIndex);
			}
			else
			{
				CollisionGroupThisCheck(LeftGroupIndex);
			}
		}
	}
}

void SJScene::CollisionGroupOtherCheck(int _Left, int _Right)
{
	std::list<SJCollision*>& LeftGroup = m_CollisionLists[_Left];
	std::list<SJCollision*>& RightGroup = m_CollisionLists[_Right];

	std::list<SJCollision*>::iterator LeftIter = LeftGroup.begin();

	for (; LeftIter != LeftGroup.end(); ++LeftIter)
	{
		if (false == (*LeftIter)->IsOn())
		{
			continue;
		}

		std::list<SJCollision*>::iterator RightIter = RightGroup.begin();

		for (; RightIter != RightGroup.end(); ++RightIter)
		{
			if (false == (*RightIter)->IsOn())
			{
				continue;
			}
			// 두 그룹의 각 오브젝트간 충돌체크
			(*LeftIter)->CollisionCheck(*RightIter);
		}
	}
}

void SJScene::CollisionGroupThisCheck(int _Value)
{

	// 나와 상대가 같은 그룹일때 충돌
	std::list<SJCollision*>& LeftGroup = m_CollisionLists[_Value];
	std::list<SJCollision*>::iterator LeftIter = LeftGroup.begin();
	std::list<SJCollision*>::iterator EndIter = LeftGroup.end();

	for (; LeftIter != EndIter; ++LeftIter)
	{
		if (false == (*LeftIter)->IsOn())
		{
			continue;
		}

		std::list<SJCollision*>::iterator RightIter = LeftIter;
		++RightIter;

		if (RightIter == EndIter)
		{
			return;
		}
		

		for (; RightIter != EndIter; ++RightIter)
		{
			if (false == (*RightIter)->IsOn())
			{
				continue;
			}
			// 두 그룹의 각 오브젝트간 충돌체크
			(*LeftIter)->CollisionCheck(*RightIter);
		}
	}

}

void SJScene::OnOffCheck() {
	// 랜더러 정리
	{
		std::map<int, std::list<SJRenderer*>>::iterator Layeriter = m_RendererLists.begin();

		for (; Layeriter != m_RendererLists.end(); ++Layeriter)
		{
			std::list<SJRenderer*>& RenderLayer = Layeriter->second;
			std::list<SJRenderer*>::iterator Rendereriter = RenderLayer.begin();

			for (; Rendereriter != RenderLayer.end(); ++Rendereriter)
			{
				(*Rendereriter)->CallOnTask();
				(*Rendereriter)->CallOffTask();
			}

		}
	}

	// 충돌체 정리
	{
		std::map<int, std::list<SJCollision*>>::iterator iter = m_CollisionLists.begin();

		for (; iter != m_CollisionLists.end(); ++iter)
		{
			std::list<SJCollision*>::iterator Coliter = iter->second.begin();

			for (; Coliter != iter->second.end(); ++Coliter)
			{
				(*Coliter)->CallOnTask();
				(*Coliter)->CallOffTask();
			}
		}
	}



	// 여기서 Release(메모리 정리) 단계를 실행합니다.
	{
		std::list<SJActor*>::iterator iter = m_Actors.begin();

		for (; iter != m_Actors.end(); ++iter)
		{
			(*iter)->CallOnTask();
			(*iter)->CallOffTask();
		}
	}
}

void SJScene::Release()
{
	// 렌더러 정리
	{
		std::map<int, std::list<SJRenderer*>>::iterator Layeriter = m_RendererLists.begin();

		for (; Layeriter != m_RendererLists.end(); ++Layeriter)
		{
			std::list<SJRenderer*>& RenderLayer = Layeriter->second;

			std::list<SJRenderer*>::iterator Renderiter = RenderLayer.begin();

			for (; Renderiter != RenderLayer.end(); )
			{
				if (false == (*Renderiter)->IsDeath())
				{
					++Renderiter;
					continue;
				}

				// Actor에서 실행
				/*(*Renderiter)->DeathTask();
				delete (*Renderiter);*/
				Renderiter = RenderLayer.erase(Renderiter);
			}
		}
	}

	// 충돌체 정리
	{
		std::map<int, std::list<SJCollision*>>::iterator Layeriter = m_CollisionLists.begin();

		for (; Layeriter != m_CollisionLists.end(); ++Layeriter)
		{
			std::list<SJCollision*>::iterator Collisioniter = Layeriter->second.begin();

			for (; Collisioniter != Layeriter->second.end(); )
			{
				if (false == (*Collisioniter)->IsDeath())
				{
					++Collisioniter;
					continue;
				}

				Collisioniter = Layeriter->second.erase(Collisioniter);
			}
		}
	}

	// Release (메모리 정리) 단계
	{
		std::list<SJActor*>::iterator Layeriter = m_Actors.begin();

		for (; Layeriter != m_Actors.end();)
		{
			if (false == (*Layeriter)->IsDeath())
			{
				(*Layeriter)->Release();
				++Layeriter;
				continue;
			}

			(*Layeriter)->DeathTask();
			delete (*Layeriter);

			Layeriter = m_Actors.erase(Layeriter);
		}
	}
}

void SJScene::SceneChangeStart()
{ 
	m_CurScene->Start(); 
};

void SJScene::SceneChangeEnd() {};