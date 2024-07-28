#include "pch.h"
#include "RA.h"
#include <algorithm>

RA::RA() {}

bool RA::RegisterUser(const std::string& username) {
	auto it = find(m_registeredUsers.begin(), m_registeredUsers.end(), username);

	if (it == m_registeredUsers.end())
	{
		m_registeredUsers.push_back(username);
		return true;
	}

	return false;
}
bool RA::UnregisterUser(const std::string& username) {
	auto it = find(m_registeredUsers.begin(), m_registeredUsers.end(), username);

	if (it != m_registeredUsers.end())
	{
		m_registeredUsers.erase(it);
		return true;
	}
	return false;
}
