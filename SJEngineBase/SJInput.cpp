#include "SJInput.h"
#include <Windows.h>

std::map<SJString, SJInput::SJKey> SJInput::m_KeyMap;

SJInput::SJKey::SJKey()
	: Down(false), Press(false), Up(false), Free(true)
{

}

SJInput::SJKey::~SJKey()
{

}

bool SJInput::SJKey::KeyCheck()
{
	for (size_t i = 0; i < m_Key.size(); i++)
	{
		// �ϳ��� �ȴ��ȴٸ� �� Ű�� �ȴ����ſ���.
		if (0 == GetAsyncKeyState(m_Key[i]))
		{
			return false;
		}
	}

	// �� ���ȴٸ� �� Ű�� �����̴ϴ�.
	return true;
}

// �ڽ��� Ű�� ���¸� üũ�ϴ� �Լ�
void SJInput::SJKey::Update()
{
	if (true == KeyCheck())
	{
		if (true == Free)
		{
			Down = true;
			Press = true;
			Up = false;
			Free = false;
		}
		else
		{
			Down = false;
			Press = true;
			Up = false;
			Free = false;
		}
	}
	else
	{
		if (true == Press)
		{
			Down = false;
			Press = false;
			Up = true;
			Free = true;
		}
		else
		{
			Down = false;
			Press = false;
			Up = false;
			Free = true;
		}
	}
}

// Static Var
// Static Func

// member Var

SJInput::SJInput()
{

}

SJInput::~SJInput()
{

}

// member Func

SJInput::SJKey& SJInput::FindKey(const SJString& _Name)
{
	if (m_KeyMap.end() == m_KeyMap.find(_Name))
	{
		SJDebug::AssertMsg("if (m_KeyMap.end() == m_KeyMap.find(_Name))");
		return m_KeyMap[_Name];
	}

	return m_KeyMap[_Name];
}

void SJInput::Update()
{
	std::map<SJString, SJKey>::iterator iter = m_KeyMap.begin();

	for (; iter != m_KeyMap.end(); ++iter)
	{
		iter->second.Update();
	}
}

bool SJInput::IsFree(const SJString& _Name)
{
	return FindKey(_Name).Free;
}
bool SJInput::IsUp(const SJString& _Name)
{
	return FindKey(_Name).Up;
}
bool SJInput::IsPress(const SJString& _Name)
{
	return FindKey(_Name).Press;
}
bool SJInput::IsDown(const SJString& _Name)
{
	return FindKey(_Name).Down;
}