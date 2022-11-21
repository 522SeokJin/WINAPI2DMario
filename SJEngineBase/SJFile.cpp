#include "SJFile.h"

// Static Var
// Static Func

// member Var

SJFile::SJFile() : m_Handle(nullptr), m_CurMemoryPostion(0), m_FileSize(0)
{

}

SJFile::SJFile(const SJString& _Path) : SJPath(_Path), m_Handle(nullptr), m_CurMemoryPostion(0), m_FileSize(0)
{
}

SJFile::~SJFile()
{
	Close();
}


// member Func

void SJFile::Close()
{
	if (nullptr != m_Handle)
	{
		fclose(m_Handle);
		m_Handle = nullptr;
	}
}

void SJFile::Open(const wchar_t* _Mode)
{
	// 이미 열려져있다면 닫는다.
	Close();

	m_CurMemoryPostion = 0;
	m_Mode = _Mode;

	_wfopen_s(&m_Handle, c_str(), m_Mode.c_str());

	if (nullptr == m_Handle)
	{
		// 여는데 실패했다.
		SJDebug::AssertMsg(L"if (nullptr == m_Handle)");
	}

	fseek(m_Handle, 0, SEEK_END);
	m_FileSize = ftell(m_Handle);
	fseek(m_Handle, 0, SEEK_SET);
}

void SJFile::Write(void* _Ptr, size_t _Size, size_t _Count)
{
	if (nullptr == m_Handle)
	{
		SJDebug::AssertMsg(L"if (nullptr == m_Handle)");
	}

#ifdef _DEBUG
	if (true == IsReadOpen())
	{
		SJDebug::AssertMsg(L"if (nullptr == m_Handle)");
	}
#endif
	fwrite(_Ptr, _Size, _Count, m_Handle);
}

void SJFile::Read(void* _Ptr, size_t _BufferSize, size_t _ReadSize, size_t _Count)
{
	fread_s(_Ptr, _BufferSize, _ReadSize, _Count, m_Handle);
}

size_t SJFile::FileSize()
{
	if (nullptr == m_Handle)
	{
		return m_FileSize;
	}

	return m_FileSize;
}