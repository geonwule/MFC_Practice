#pragma once
#include <string>
#include <vector>

#define CERTI_PREFIX "Certificate for "

class CA
{
public:
	CA();
	std::string GenerateCertificate(const std::string& name);
	bool RevokeCertificate(const std::string& name);
	std::vector<std::string> GetCRLList();
	std::vector<std::string> GetCAList();

private:
	std::vector<std::string> m_certificates;
	std::vector<std::string> m_revokedCertificates;
};

