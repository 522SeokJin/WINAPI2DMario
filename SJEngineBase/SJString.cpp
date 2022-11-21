#include "SJString.h"
#include <atlstr.h>

// Static Var
// Static Func

// member Var

SJString::SJString()
{
}

SJString::SJString(const wchar_t* _pStr)
	: m_Str(_pStr)
{
}

SJString::SJString(const std::wstring& _Str)
	:m_Str(_Str)
{
}

SJString::~SJString()
{
}

std::string SJString::wStringToString(int _encoding/* = CP_ACP*/) const
{
	// wstring => string
	return std::string(CW2A(m_Str.c_str(), _encoding).m_psz);
}

void SJString::StringTowString(const std::string& _Str)
{
	// 역변환
	// string => wstring

	m_Str = CA2W(_Str.c_str()).m_psz;
}

bool SJString::is_find(const wchar_t* _Text, size_t _StartIndex)
{
	return std::wstring::npos != m_Str.find(_Text, _StartIndex);
}

size_t SJString::find_first_index(const wchar_t* _Text, size_t _index) const
{
	return m_Str.find(_Text, _index);
}

size_t SJString::find_last_index(const wchar_t* _Text, size_t _index) const
{
	return m_Str.rfind(_Text, _index);
}

SJString SJString::Cut(size_t _StartIndex, size_t _Count) const
{
	return m_Str.substr(_StartIndex, _Count);
}

SJString SJString::CutIndex(size_t _StartIndex, size_t _EndIndex) const
{
	return m_Str.substr(_StartIndex, _EndIndex - _StartIndex);
}

std::vector<SJString> SJString::StringCutVector(const wchar_t* _Pivot)
{
	std::vector<SJString> Return;

	SJString PivotStr = _Pivot;

	size_t Start = 0;
	size_t End = find_first_index(_Pivot, Start);

	if (End == std::string::npos)	// npos 문자열을 찾지못하면 npos를 반환 == -1
	{
		return Return;
	}

	while (true)
	{
		SJString Text;

		if (End == std::string::npos)
		{
			Text = Cut(Start, m_Str.size() - Start);
			Return.push_back(Text);

			break;
		}

		Text = Cut(Start, End - Start);

		Return.push_back(Text);

		Start = End + PivotStr.size();
		End = find_first_index(_Pivot, Start);
	}

	return Return;
}

std::vector<SJString> SJString::StringCenterCutVector(const wchar_t* _Start, const wchar_t* _End)
{
	std::vector<SJString> Return;

	SJString StartStr = _Start;
	SJString EndStr = _End;

	size_t Start = find_first_index(StartStr.c_str(), 0);
	size_t End = find_first_index(EndStr.c_str(), Start + StartStr.size());

	if (Start == std::string::npos)
	{
		return Return;
	}

	while (true)
	{
		SJString Text = CutIndex(Start + StartStr.size(), End);

		Return.push_back(Text);

		Start = find_first_index(StartStr.c_str(), End + EndStr.size());
		End = find_first_index(EndStr.c_str(), Start);

		if (Start == std::string::npos)
		{
			// 맨 마지막까지
			break;
		}
	}


	return Return;
}

bool SJString::EraseFirst(const SJString& _Str)
{
	size_t Index = find_first_index(_Str.c_str());

	if (Index == std::wstring::npos)
	{
		return false;
	}

	m_Str.erase(Index, _Str.size());

	return true;
}

bool SJString::EraseLast(const SJString& _Str)
{
	size_t Index = find_last_index(_Str.c_str());

	if (Index == std::wstring::npos)
	{
		return false;
	}

	m_Str.erase(Index, _Str.size());

	return true;
}

void SJString::EraseAll(const SJString& _Str)
{
	while (EraseFirst(_Str));
}
