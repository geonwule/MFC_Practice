#pragma once

#include <vector>
#include <string>

class RA
{
public:

	RA();
	bool RegisterUser(const std::string& username);
	bool UnregisterUser(const std::string& username);

private:
	std::vector<std::string> m_registeredUsers;
};

