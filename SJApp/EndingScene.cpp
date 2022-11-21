#include "EndingScene.h"
#include <SJSound.h>
#include <SJWindow.h>
#include <SJWindowResMgr.h>
#include "Ending.h"
#include "FadeActor.h"

// Static Var
// Static Func

// member Var

EndingScene::EndingScene()
{

}

EndingScene::~EndingScene()
{

}

// member Func

void EndingScene::Start()
{
	SJSound::Play(L"Ending.mp3");

	{
		SJActor* Object = CreateActor<Ending>();

		SJWinImage* Image = SJWindowResMgr::Inst().FindImage(L"Ending.bmp");

		Object->SetPos(SJWindow::GetSize().hfloat4());
	}

	{
		FadeActor* Object = CreateActor<FadeActor>();
		Object->SetPos(float4::ZERO);
		Object->SetCamAffect(false);

		Object->FadeTimer.CreateTimeEvent(2.0f, Object, &FadeActor::FadeOutEnd, &FadeActor::FadeOutStart, &FadeActor::FadeOut);
	}
}

void EndingScene::SceneUpdate()
{

}

void EndingScene::SceneDebugRender()
{

}