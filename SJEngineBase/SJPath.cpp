#include "SJPath.h"

// Static Var
bool SJPath::IsExist(const SJString& _Path)
{
	return 0 == _waccess(_Path.c_str(), 00);
}
// Static Func

// member Var

SJPath::SJPath()
{

}

SJPath::SJPath(const SJString& _Path) : SJString(_Path)
{

}

SJPath::~SJPath()
{

}

// member Func

bool SJPath::IsExist()
{
	// 리턴값
	//EACCES	액세스 거부됨 : 파일의 권한 설정이 지정된 액세스를 허용하지 않습니다.
	//ENOENT	파일 이름 또는 경로를 찾을 수 없습니다.
	//EINVAL	잘못된 매개 변수입니다.

	// 어떤 경로에 파일이나
	// 디렉토리가 존재하는지 존재하지 않는지 알아내는 함수 있을까요 없을까요?

	// 파일의 모드에는
	//00	존재만
	//02	쓰기 전용
	//04	읽기 전용
	//06	읽기 및 쓰기

	return IsExist(m_Str.c_str());
}
