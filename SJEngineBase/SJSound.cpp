#include "SJSound.h"
#include "SJDebug.h"
#include "SJString.h"
#include <atlstr.h>
#include "SJPath.h"

// Static Var
// Static Func
FMOD::System* SJSound::m_pFmodSystem = nullptr;
SJSound::StaticInst SJSound::Inst;
std::map<SJString, SJSound*> SJSound::m_SoundMap;

SJSound::StaticInst::StaticInst()
{
	SJSound::Init();
}

SJSound::StaticInst::~StaticInst()
{
	//Release();
}

void SJSound::Release()
{
	{
		std::map<SJString, SJSound*>::iterator iter = m_SoundMap.begin();
		for (; iter != m_SoundMap.end(); ++iter)
		{
			delete iter->second;
		}
		m_SoundMap.clear();
	}

	m_pFmodSystem->release();
}

// member Var

SJSound::SJSound()
	: m_pSound(nullptr)
{

}

SJSound::~SJSound()
{
	if (nullptr != m_pSound)
	{
		m_pSound->release();
		m_pSound = nullptr;
	}
}

// member Func

void SJSound::Init()
{
	// FMOD::System의 핸들을 주고
	// 이 핸들을 통해서 사운드를 로드하고 재생할 수 있다.
	// C++식으로 준다
	FMOD::System_Create(&m_pFmodSystem);

	if (nullptr == m_pFmodSystem)
	{
		SJDebug::AssertMsg(L"if (nullptr == m_pFmodSystem)");
	}

	if (FMOD_OK != m_pFmodSystem->init(32, FMOD_DEFAULT, nullptr))
	{
		SJDebug::AssertMsg(L"if (FMOD_OK != m_pFmodSystem->init(32, FMOD_DEFAULT, nullptr))");
	}
}

void SJSound::Load(const SJString& _Path)
{
	SJSound* NewSound = new SJSound();
	NewSound->Create(_Path);

	SJString FileName = SJPath::IOName(_Path);

	std::pair<std::map<SJString, SJSound*>::iterator, bool> Result =
		m_SoundMap.insert(std::map<SJString, SJSound*>::value_type(FileName, NewSound));

	if (false == Result.second)
	{
		SJDebug::AssertMsg(L"if (false == Result.second)");
	}

	//NewSound->Play();
}

void SJSound::Update()
{
	// m_pFmodSystem을 프레임마다 체크
	if (nullptr != m_pFmodSystem)
	{
		m_pFmodSystem->update();
	}
}

SJSound::SJSoundPlayer SJSound::Play(const SJString& _Name, int _LoopCount)
{
	if (m_SoundMap.end() == m_SoundMap.find(_Name))
	{
		SJDebug::AssertMsg(L"if (m_SoundMap.end() == m_SoundMap.find(_Name))");
	}

	return m_SoundMap[_Name]->Play(_LoopCount);
}

////////////////////////////////////////////////		Member

void SJSound::Create(const SJString& _Path)
{
	std::string Path = _Path.wStringToString(CP_UTF8);

	if (FMOD_OK != m_pFmodSystem->createSound(Path.c_str(), FMOD_LOOP_NORMAL, nullptr, &m_pSound))
	{
		SJDebug::AssertMsg(L"if (FMOD_OK != m_pFmodSystem->createSound(Path.c_str(), FMOD_DEFAULT, nullptr, &m_pSound))");
	}
}

FMOD::Channel* SJSound::Play(int _LoopCount)
{
	FMOD::Channel* Ch = nullptr;


	if (FMOD_OK != m_pFmodSystem->playSound(m_pSound, nullptr, false, &Ch))
	{
		SJDebug::AssertMsg(L"if (FMOD_OK != m_pFmodSystem->playSound(m_pSound, nullptr, false, &Ch))");
	}

	Ch->setVolume(0.15f);
	Ch->setLoopCount(_LoopCount);

	return Ch;
}