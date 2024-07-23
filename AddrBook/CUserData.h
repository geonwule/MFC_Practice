#pragma once
#include <afx.h>
class CUserData :
	public CObject
{
public:
	CUserData(CString name, CString phone) : m_strName(name), m_strPhone(phone) {

	}

	CUserData(const CUserData& other) : m_strName(other.m_strName), m_strPhone(other.m_strPhone) {
	}

	CString GetName() { return m_strName; }
	CString GetPhone() { return m_strPhone; }

private:
	CString m_strName, m_strPhone;
};

