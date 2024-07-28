#include "pch.h"
#include "CA.h"
#include <algorithm>
//std::vector<std::string> m_certificates;
//std::vector<std::string> m_revokedCertificates;


CA::CA() {}

std::string CA::GenerateCertificate(const std::string& name)
{
	std::string cert = CERTI_PREFIX + name;
	
	if (find(m_certificates.begin(), m_certificates.end(), cert) == m_certificates.end())
		m_certificates.push_back(cert);

	return cert;
}

bool CA::RevokeCertificate(const std::string& cert)
{
	for (auto it = m_certificates.begin(); it != m_certificates.end(); it++)
	{
		if (*it == cert)
		{
			m_revokedCertificates.push_back(cert);
			m_certificates.erase(it);
			return true;
		}
	}

	return false;
}

std::vector<std::string> CA::GetCRLList()
{
	return m_revokedCertificates;
}

std::vector<std::string> CA::GetCAList()
{
	return m_certificates;
}


