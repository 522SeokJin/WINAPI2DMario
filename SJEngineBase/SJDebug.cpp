#include "SJDebug.h"
#include "assert.h"
#include <Windows.h>
#include <crtdbg.h>

// Static Var
// Static Func

void SJDebug::LeakCheck()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}

void SJDebug::AssertMsg(const SJString& _ErrorMsg)
{
#ifdef _DEBUG
	//OutputDebugStringW(_ErrorMsg.c_str());
	_wassert(_ErrorMsg.c_str(), __FILEW__, __LINE__);
#endif
}

void SJDebug::AssertMsg(const std::string& _ErrorMsg)
{
#ifdef _DEBUG
	//OutputDebugStringW(_ErrorMsg.c_str());
	assert(nullptr);
#endif
}

void SJDebug::OutPutMsg(const SJString& _ErrorMsg)
{
	OutputDebugStringW(_ErrorMsg.c_str());
}

// member Var


SJDebug::SJDebug()
{

}

SJDebug::~SJDebug()
{

}

// member Func