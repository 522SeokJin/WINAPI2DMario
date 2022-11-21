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
	// ���ϰ�
	//EACCES	�׼��� �źε� : ������ ���� ������ ������ �׼����� ������� �ʽ��ϴ�.
	//ENOENT	���� �̸� �Ǵ� ��θ� ã�� �� �����ϴ�.
	//EINVAL	�߸��� �Ű� �����Դϴ�.

	// � ��ο� �����̳�
	// ���丮�� �����ϴ��� �������� �ʴ��� �˾Ƴ��� �Լ� ������� �������?

	// ������ ��忡��
	//00	���縸
	//02	���� ����
	//04	�б� ����
	//06	�б� �� ����

	return IsExist(m_Str.c_str());
}
