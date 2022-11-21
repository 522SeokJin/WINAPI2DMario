#include "SJCore.h"

#include <SJDirectory.h>
#include <SJFile.h>
#include <SJWindowResMgr.h>
#include <SJInput.h>
#include <SJSound.h>

#include "TitleScene.h"
#include "Stage1Scene.h"
#include "BossStageScene.h"
#include "EndingScene.h"

// Static Var
// Static Func

SJSceneManager SJCore::SceneManager;

// member Var

SJCore::SJCore()
{

}

SJCore::~SJCore()
{

}

// member Func

void SJCore::Start()
{
	SJInput::CreateKey(L"Start", VK_RETURN);	// Enter Key

	SJInput::CreateKey(L"LEFT", VK_LEFT);
	SJInput::CreateKey(L"RIGHT", VK_RIGHT);
	SJInput::CreateKey(L"UP", VK_UP);
	SJInput::CreateKey(L"DOWN", VK_DOWN);

	SJInput::CreateKey(L"Z", 'Z');	// ���� Ű
	SJInput::CreateKey(L"X", 'X');	// ����, ��ȣ�ۿ� Ű
	SJInput::CreateKey(L"M", 'M');	// ���� Ű�� ����

	SJInput::CreateKey(L"DebugMode", VK_OEM_3);	// ` = DebugMode
	SJInput::CreateKey(L"Test", 'T');			// Test Key

	SJInput::CreateKey(L"SmallMario", 'Q');
	SJInput::CreateKey(L"SuperMario", 'W');
	SJInput::CreateKey(L"RacoonMario", 'E');
	SJInput::CreateKey(L"R", 'R');	// ����

	{
		SJDirectory Dir;

		Dir.MoveParent();
		Dir.MoveChild(L"Res");

		std::vector<SJFile> AllImageFile = Dir.DirectoryAllFileToVector(L"*.bmp");

		for (size_t i = 0; i < AllImageFile.size(); i++)
		{
			SJWindowResMgr::Inst().ImageLoad(AllImageFile[i].GetPath());
		}
	}

	{
		SJDirectory Dir;

		Dir.MoveParent();
		Dir.MoveChild(L"Res");
		Dir.MoveChild(L"Sound");

		std::vector<SJFile> AllSoundFile = Dir.DirectoryAllFileToVector(L"*.*");

		for (size_t i = 0; i < AllSoundFile.size(); i++)
		{
			SJSound::Load(AllSoundFile[i].GetPath());
		}
	}

	SceneManager.CreateScene<TitleScene>(L"Title");
	SceneManager.CreateScene<Stage1Scene>(L"Stage1");
	SceneManager.CreateScene<BossStageScene>(L"BossStage");
	SceneManager.CreateScene<EndingScene>(L"Ending");

	// ���� ���� ����
	SceneManager.ChangeScene(L"Title");
}

void SJCore::Update()
{
	SceneManager.ChangeCheck();

	SceneManager.GetCurScene()->Progress();
}

void SJCore::End()
{
	SJSound::Release();
}