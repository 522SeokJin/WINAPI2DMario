#include "SJDirectory.h"
#include <Windows.h>
#include "SJDebug.h"
#include "SJFile.h"
#include "io.h"

// Static Var
// Static Func

SJString SJDirectory::GetCurrentDirectoryPath()
{
	wchar_t Arr[_MAX_PATH] = { 0 };

	GetCurrentDirectoryW(_MAX_PATH, Arr);

	SJString ReturnPath = Arr;
	ReturnPath += L"\\";

	return ReturnPath;
}

void SJDirectory::GetCurrentDirectoryPath(SJString& _String)
{
	_String = GetCurrentDirectoryPath();
}

// member Var
SJDirectory::SJDirectory() : SJPath(GetCurrentDirectoryPath())
{

}

SJDirectory::~SJDirectory()
{

}

// member Func

SJString SJDirectory::DirectoryName()
{
	return IOName();
}

void SJDirectory::MoveParent()
{
	size_t LastIndex = find_last_index(L"\\", size() - 2);
	SJString::operator=(CutIndex(0, LastIndex + 1));
}

void SJDirectory::MoveParent(const SJString& _DirName)
{
	while (DirectoryName() != _DirName)
	{
		MoveParent();
	}
}

void SJDirectory::MoveChild(const SJString& _Path)
{
	SJString::operator+=(_Path + L"\\");

	if (false == IsExist())
	{
		SJDebug::AssertMsg(_Path + L"if (false == IsExist())");
	}
}

std::vector<SJFile> SJDirectory::DirectoryAllFileToVector(const SJString& _CheckPath)
{
	std::vector<SJFile> ReturnVector;

	_wfinddata64i32_t fd;

	SJString Path = c_str();

	Path += _CheckPath;

	// Path.EraseLast(L"\\");

	// 열람권한 획득
	// 얻어오는 함수
	intptr_t FindHandle = _wfindfirst(Path.c_str(), &fd);

	if (-1 == FindHandle)
	{
		SJDebug::AssertMsg(L"if (-1 == FindHandle)");
	}

	// . 나자신 폴더 // <- FindHandle 열람권한
	// .. 나의 부모 폴더
	// Test0\\
	// Test1\\
	// aaa.bmp
	// bbb.bmp
	// ccc.bmp

	do
	{
		if (fd.attrib & _A_SUBDIR)
		{
			// 사용하는 함수
			_wfindnext(FindHandle, &fd);
			continue;
			// 디렉토리라는 겁니다.
		}

		SJString FileName = fd.name;

		SJFile NewFile = operator+(FileName);

		ReturnVector.push_back(NewFile);
	} while (0 == _wfindnext(FindHandle, &fd));

	_findclose(FindHandle);

	return ReturnVector;
}