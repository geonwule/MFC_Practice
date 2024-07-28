#pragma once
#include <string>

class CA;

enum e_CertificateStatus
{
	GOOD,
	REVOKED,
	UNKNOWN,
};

class OCSP
{
public:
	OCSP();
	e_CertificateStatus CheckCertificateStatus(const std::string& name, const CA& ca);
};

