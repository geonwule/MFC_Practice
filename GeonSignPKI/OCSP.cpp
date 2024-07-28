#include "pch.h"
#include "OCSP.h"
#include "CA.h"
#include <algorithm>

OCSP::OCSP() {}

e_CertificateStatus OCSP::CheckCertificateStatus(const std::string& name, const CA& ca)
{
	auto ca_list = const_cast<CA&>(ca).GetCAList();
	if (find(ca_list.begin(), ca_list.end(), CERTI_PREFIX +  name) != ca_list.end())
		return GOOD;

	auto crl_list = const_cast<CA&>(ca).GetCRLList();
	if (find(crl_list.begin(), crl_list.end(), CERTI_PREFIX + name) != crl_list.end())
		return REVOKED;
	
	return UNKNOWN;
}