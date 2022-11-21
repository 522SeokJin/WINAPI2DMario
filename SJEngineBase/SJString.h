#pragma once

#include <string>
#include <vector>

// 분류 : 
// 용도 : 
// 설명 : 프레임워크에서 문자열을 다루는 클래스
//		  문자열에 대한 기능들을
class SJString
{
private: // Static Var
public: // Static Func
public: // member Var
	std::wstring	m_Str;

public: // constructer destructer
	SJString();
	SJString(const wchar_t* _pStr);
	SJString(const std::wstring& _Str);
	~SJString();

public:
	template<typename Type>
	static SJString ToString(const Type& _Data)
	{
		SJString String;
		String += SJString(std::to_wstring(_Data));
		return String;
	}
	
	//template<typename Type>
	//SJString(Type& _Other) noexcept : m_Str()
	//{
	//	*this = ToString<Type>(_Other);
	//}

public: // delete constructer 
	SJString(const SJString& _Other) noexcept
		: m_Str(_Other.m_Str)
	{

	}
	SJString(const SJString&& _Other) noexcept
		: m_Str(_Other.m_Str)
	{

	}
	SJString(int _Other) noexcept : m_Str()
	{
		*this = ToString(_Other);
	}

public: // delete operator
	SJString& operator=(const SJString& _Other) noexcept
	{
		m_Str = _Other.m_Str;
		return *this;
	}
	SJString& operator=(const SJString&& _Other) noexcept
	{
		m_Str = _Other.m_Str;
		return *this;
	}
	SJString& operator=(int _Value)
	{
		m_Str = std::to_wstring(_Value);
		return *this;
	}

	SJString operator+(const SJString& _Other) const
	{
		std::wstring Str = m_Str;
		Str += _Other.m_Str;
		return Str;
	}

	SJString& operator+=(const SJString& _Other)
	{
		m_Str += _Other.m_Str;
		return *this;
	}

	bool operator==(const SJString& _Other) const
	{
		return m_Str == _Other.m_Str;
	}

	bool operator!=(const SJString& _Other) const
	{
		return m_Str != _Other.m_Str;
	}

	bool operator>(const SJString& _Other) const
	{
		return m_Str > _Other.m_Str;
	}

	bool operator<(const SJString& _Other) const
	{
		return m_Str < _Other.m_Str;
	}

	wchar_t& operator[](size_t _index)
	{
		return m_Str[_index];
	}

	size_t size() const
	{
		return m_Str.size();
	}

	void resize(size_t _Size) {
		return m_Str.resize(_Size);
	}

	void reserve(size_t _Size) {
		return m_Str.reserve(_Size);
	}

	const wchar_t* c_str() const
	{
		return m_Str.c_str();
	}

public: // member Func
	std::string wStringToString(int _encoding = 0) const;
	void StringTowString(const std::string& _Str);

	bool is_find(const wchar_t* _Text, size_t _StartIndex = 0);

	size_t find_first_index(const wchar_t* _Text, size_t _index = 0) const;
	size_t find_last_index(const wchar_t* _Text, size_t _index = -1) const;

	SJString Cut(size_t _StartIndex, size_t _Count) const;
	SJString CutIndex(size_t _StartIndex, size_t _EndIndex) const;

	std::vector<SJString> StringCutVector(const wchar_t* _Pivot);
	std::vector<SJString> StringCenterCutVector(const wchar_t* _Start, const wchar_t* _End);

	bool EraseFirst(const SJString& _Str);
	bool EraseLast(const SJString& _Str);
	void EraseAll(const SJString& _Str);
};

